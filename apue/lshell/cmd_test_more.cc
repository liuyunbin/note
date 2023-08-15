
#include <error.h>      // error
#include <signal.h>     // signal
#include <stdio.h>      // snprintf
#include <string.h>     // strlen
#include <sys/ioctl.h>  // ioctl
#include <sys/stat.h>   // stat
#include <termios.h>    // tcgetattr
#include <unistd.h>     // isatty

#include <atomic>
#include <iostream>
#include <map>

#include "lshell.h"

// 由于信号处理函数会修改下面两个变量的值
// 为避免程序拿到一半的值，所以采用原子变量
// 以下两个变量分别表示终端的行数和列数
std::atomic<int> row_size;
std::atomic<int> col_size;

// 指向终端的文件的读指针
FILE *fp_read_tty;

// 保存终端初始属性
struct termios old_termios;

// 当前屏幕的输出行数
int num_of_lines;

static void usage() {
    fputs("use more ...\n", stderr);
    exit(-1);
}

// 传递数据
void handle_use_cat(FILE *fp) {
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != NULL)
        fputs(buf, stdout);
}

void process_argv_use_cat(int argc, char *argv[]) {
    bool handle_stdin = isatty(0) ? false : true;
    if (handle_stdin) {
        handle_use_cat(stdin);
    } else if (argc == 1) {
        usage();
        return;
    }
    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("more");
            continue;
        }
        handle_use_cat(fp);
        fclose(fp);
    }
}

// 设置终端属性
void set_tty() {
    // 将终端配置读入结构体 old_termios 中
    if (tcgetattr(fileno(fp_read_tty), &old_termios) == -1)
        error(EXIT_FAILURE, errno, "tcgetattr");

    struct termios new_termios = old_termios;
    // 设置字符不回显和无缓冲
    new_termios.c_lflag &= ~(ICANON | ECHO);
    // 重新配置终端，参数 TCSANOW 表示配置立即更新
    if (tcsetattr(fileno(fp_read_tty), TCSANOW, &new_termios) == -1)
        error(EXIT_FAILURE, errno, "tcsetattr");
}

// 重置终端属性
void reset_tty() {
    if (tcsetattr(fileno(fp_read_tty), TCSANOW, &old_termios) == -1)
        error(EXIT_FAILURE, errno, "tcsetattr");
}

// 获取终端的大小，信号处理函数可能会调用
void get_tty_row_col() {
    struct winsize wbuf;
    if (ioctl(fileno(fp_read_tty), TIOCGWINSZ, &wbuf) == -1) {
        reset_tty();  // 重置终端
        error(EXIT_FAILURE, errno, "ioctl");
    }
    row_size = wbuf.ws_row;
    col_size = wbuf.ws_col;
}

// 输出提示信息，反白输出
void output_prompt(const char *str) {
    if (str == NULL || *str == '\0')
        printf("\033[7m--more--\033[m");
    else
        printf("\033[7m--more--(%s)\033[m", str);
}

// 读入并处理用户输入
// 忽略非 q，空格，回车 以外的其它字符
void get_user_input_and_handle() {
    for (;;) {
        int ch = fgetc(fp_read_tty);
        switch (ch) {
        case 'q':
            reset_tty();  // 重置终端
            exit(EXIT_SUCCESS);
        case '\n':
            // 获取下一行
            // 避免窗口大小变化
            num_of_lines = row_size - 1;
            return;
        case ' ':
            // 获取下一页
            num_of_lines = 0;
            return;
        default:
            // 忽略其它值
            break;
        }
    }
}

// 输出提示并处理用户输入
void handle_user_input(const char *str = NULL) {
    printf("\033[s");  // 记录光标的位置

    output_prompt(str);
    get_user_input_and_handle();

    printf("\033[1K");  // 删除已输出的 "more?"
    printf("\033[u");   // 恢复光标的位置
}

void handle_user_input(int read_size, int file_size) {
    int  percent = int(1.0 * read_size / file_size * 100);
    char buf[10];
    snprintf(buf, sizeof(buf), "%d%%", percent);
    handle_user_input(buf);
}

static void signal_handle(int sig) {
    if (sig == SIGWINCH) {
        // 窗口大小改变
        get_tty_row_col();
    }
}

static void set_signal() {
    struct sigaction act;
    act.sa_handler = signal_handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &act, NULL);
}

void process_argv_use_more(int argc, char *argv[]) {
    bool handle_stdin = isatty(0) ? false : true;
    if (handle_stdin == false && argc == 1) {
        usage();
        return;
    }

    // 得到指向终端的文件的读指针
    if (handle_stdin) {
        fp_read_tty = fopen("/dev/tty", "r");
        if (fp_read_tty == NULL)
            error(EXIT_FAILURE, errno, "cannot open /dev/tty");
    } else {
        fp_read_tty = stdin;
    }

    set_tty();
    get_tty_row_col();
    set_signal();

    char buf[1024];
    num_of_lines = 0;

    // 为求简单，并未处理，终端列数大于等于 1024 的情况
    if (handle_stdin) {
        while (fgets(buf, col_size + 1, stdin) != NULL) {
            ++num_of_lines;
            fputs(buf, stdout);
            if (num_of_lines >= row_size)
                handle_user_input();
        }
    }

    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            snprintf(buf,
                     sizeof(buf),
                     "cannot open %s：%s",
                     argv[i],
                     strerror(errno));
            goto failure;
        }

        // 判断是否是目录
        struct stat info;
        if (stat(argv[i], &info) == -1) {
            snprintf(buf,
                     sizeof(buf),
                     "cannot open %s：%s",
                     argv[i],
                     strerror(errno));
            goto failure;
        }

        if (S_ISDIR(info.st_mode)) {
            snprintf(buf, sizeof(buf), "%s directory", argv[i]);
            goto failure;
        }

        goto success;

    failure:

        if (i + 1 < argc) {
            handle_user_input(buf);
        } else {
            fputs(buf, stderr);
            fputs("\n", stderr);
        }
        continue;

    success:

        int current_read_size = 0;  // 当前读入的大小
        int file_size         = info.st_size;

        if (i > 1 || handle_stdin) {
            snprintf(buf, sizeof(buf), "next file %s", argv[i]);
            handle_user_input(buf);
        }

        if (argc > 2 || handle_stdin) {
            fputs(":::::::::::::::::::::::::::::::::\n", stdout);
            ++num_of_lines;
            fputs(argv[i], stdout);
            fputs("\n", stdout);
            ++num_of_lines;
            fputs(":::::::::::::::::::::::::::::::::\n", stdout);
            ++num_of_lines;
            if (i > 1 || handle_stdin)
                handle_user_input(current_read_size, file_size);
        }

        while (fgets(buf, sizeof(buf), fp) != NULL) {
            current_read_size += strlen(buf);
            ++num_of_lines;
            fputs(buf, stdout);
            if (num_of_lines >= row_size)
                handle_user_input(current_read_size, file_size);
        }
        fclose(fp);
    }
    // 重置终端属性
    reset_tty();
}

int do_more(int argc, char *argv[]) {
    if (isatty(1)) {
        // 标准输出是终端
        process_argv_use_more(argc, argv);
    } else {
        // 标准输出被重定向到文件 或 管道
        // 仅仅当 cat 使用
        process_argv_use_cat(argc, argv);
    }

    return 0;
}
