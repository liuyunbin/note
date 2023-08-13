
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// 用户信息
uid_t       user_id;    // 用户 ID
std::string user_name;  // 用户名称
std::string user_home;  // 用户主目录

void init_user_info() {
    user_id            = getuid();
    struct passwd *pwd = getpwuid(user_id);
    user_name          = pwd->pw_name;
    user_home          = pwd->pw_dir;
}

// 获取命令行提示符
std::string prompt;

void get_prompt() {
    char       *p        = get_current_dir_name();
    std::string curr_dir = p;
    free(p);

    prompt = user_name + ":";
    if (curr_dir == user_home) {
        prompt += "~";
    } else if (curr_dir < user_home) {
        prompt += curr_dir;
    } else if (curr_dir.compare(0, user_home.size(), user_home) != 0) {
        prompt += curr_dir;
    } else if (curr_dir[user_home.size()] != '/') {
        prompt += curr_dir;
    } else {
        prompt += '~';
        prompt += curr_dir.data() + user_home.size();
    }

    if (user_id == 0)
        prompt += "# ";
    else
        prompt += "$ ";
}

// 获取用户的输入, 处理掉 ~ 代表目录的位置
std::string input;

void get_input() {
    // 读取一行，不包括 '\n'
    char *p = readline(prompt.data());
    if (p == NULL) {
        // printf("read EOF, exit\n");
        exit(0);
    }
    input.clear();
    for (size_t i = 0; p[i] != '\0' && p[i] != '\n'; ++i)
        if (p[i] != '~')
            input += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            input += user_home;
        else
            input += p[i];
    free(p);
}

// 命令

struct cmd_t {
    std::vector<std::string> cmd_vec;
    std::string              cmd_str;
    std::string              in;
    std::string              out;
    std::string              add;
};

std::vector<cmd_t> cmds;
bool               fg;  // 此轮作业是否是前台作业

// 解析单个命令
int parse_cmd(std::string str) {
    while (!str.empty() && str.back() == ' ')
        str.pop_back();
    cmd_t cmd;
    cmd.cmd_str = str;
    size_t i    = 0;
    for (;;) {
        while (i < str.size() && str[i] == ' ')
            ++i;
        if (i == str.size())
            break;
        if (str[i] == '<') {
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.cmd_vec.empty() || i == str.size()) {
                printf("please use: cmd <  file_name\n");
                return -1;
            }
            std::string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            cmd.in = name;
            continue;
        }
        if (str[i] == '>') {
            bool add = false;
            if (i + 1 < str.size() && str[i + 1] == '>') {
                ++i;
                add = true;
            }
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.cmd_vec.empty() || i == str.size()) {
                if (add)
                    printf("please use: cmd >> file_name\n");
                else
                    printf("please use: cmd >  file_name\n");
                return -1;
            }
            std::string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            if (add)
                cmd.add = name;
            else
                cmd.out = name;
            continue;
        }
        std::string name;
        while (i < str.size() && str[i] != ' ')
            name.push_back(str[i++]);
        cmd.cmd_vec.push_back(name);
    }
    cmds.push_back(cmd);
    return 0;
}

// 解析用户的输入
void parse_input() {
    // 去掉末尾的空白
    while (!input.empty() && input.back() == ' ')
        input.pop_back();
    // 加入历史命令
    if (!input.empty())
        add_history(input.data());
    // 判断是否后台运行
    if (!input.empty() && input.back() == '&') {
        input.pop_back();
        fg = false;
    } else {
        fg = true;
    }
    // 处理管道并存储其参数
    cmds.clear();
    size_t i = 0;
    for (;;) {
        while (i < input.size() && input[i] == ' ')
            ++i;
        if (i == input.size())
            break;
        if (input[i] == '|') {
            printf("invalid cmd!\n");
            cmds.clear();
            return;
        }
        std::string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i++]);
        if (parse_cmd(str) != 0) {  // 解析每一个命令
            cmds.clear();
            return;
        }
        if (i < input.size())
            ++i;
    }
}

// 处理重定向
int handle_redirection(const std::string &filename, int flag, int fd_new) {
    if (filename.empty())
        return 0;
    int fd = open(filename.data(), flag, 0644);
    if (fd < 0) {
        printf("can't open %s for: %s\n", filename.data(), strerror(errno));
        return -1;
    }
    dup2(fd, fd_new);
    close(fd);
    return 0;
}

int handle_redirection(const cmd_t &cmd) {
    // 输入重定向
    if (handle_redirection(cmd.in, O_RDONLY, STDIN_FILENO) != 0)
        return -1;
    // 输出重定向
    if (handle_redirection(
            cmd.out, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO) != 0)
        return -1;
    // 添加重定向
    if (handle_redirection(
            cmd.add, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO) != 0)
        return -1;
    return 0;
}

// 作业
enum status_t {
    RUN,   // 运行
    STOP,  // 暂停
    KILL,  // 被杀死
    DONE   // 完成
};

struct task_t {
    std::string cmd;     // 进程命令
    status_t    status;  // 进程状态
};

struct job_t {
    pid_t                   pgid;        // 进程组 ID
    int                     count_run;   // 进程数 -- 运行
    int                     count_stop;  // 进程数 -- 暂停
    int                     count_kill;  // 进程数 -- 被杀死
    int                     count_done;  // 进程数 -- 退出
    std::map<pid_t, task_t> tasks;       // 任务的进程信息
};

std::map<int, job_t> jobs;          // 作业
std::map<pid_t, int> pids;          // 进程号 -> 作业号
int                  next_jid = 1;  // 下一个可用的作业号
int                  curr_jid;      // 当前的作业号

sigset_t mask_child;
sigset_t mask_empty;

void init_job() {
    sigaddset(&mask_child, SIGCHLD);
    sigemptyset(&mask_empty);
}

// 调用此函数前需要阻塞 SIGCHLD
// 此时, 主进程一定是前台进程组
int list_job(int jid, bool no_status = false) {
    if (jid == -1) {
        for (auto &it : jobs)
            list_job(it.first);
        return 0;
    }
    if (jobs.find(jid) == jobs.end()) {
        printf("can't find job %d\n", jid);
        return -1;
    }
    bool first = true;
    for (auto it : jobs[jid].tasks) {
        const char *p;
        if (no_status)
            p = "";
        else if (it.second.status == RUN)
            p = "run ";
        else if (it.second.status == STOP)
            p = "stop";
        else if (it.second.status == KILL)
            p = "killed";
        else
            p = "done";
        const char *cmd = no_status ? "" : it.second.cmd.data();
        if (first) {
            first = false;
            printf("[%d] %d %s %s\n", jid, it.first, p, cmd);
        } else {
            printf("[%c] %d %s %s\n", ' ', it.first, p, cmd);
        }
    }
    return 0;
}

// 检测并删除已经完成的作业, 此时主进程一定是前台进程组
void check_job() {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    for (auto it = jobs.begin(); it != jobs.end();) {
        if (it->second.count_run != 0 || it->second.count_stop != 0) {
            // 当前作业还没做完
            ++it;
            continue;
        }
        // 当前作业已经做完
        if (it->first != curr_jid)
            list_job(it->first);
        // 删除进程号到作业号的映射
        for (auto &v : it->second.tasks)
            pids.erase(v.first);
        // 删除此作业
        it = jobs.erase(it);
        // 修正下一个可以使用的作业号
        next_jid = 0;
        for (auto &v : jobs)
            next_jid = std::max(v.first, next_jid);
        ++next_jid;
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

// 内置命令
int do_about(cmd_t &cmd) {
    printf("write by liuyunbin\n");
    return 0;
}

int do_exit(cmd_t &cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_quit(cmd_t &cmd) {
    exit(EXIT_SUCCESS);
    return 0;
}

int do_cd(cmd_t &cmd) {
    const char *p;

    if (cmd.cmd_vec.size() == 1) {
        p = user_home.data();
    } else if (cmd.cmd_vec.size() > 2) {
        printf("cd: too many arguments\n");
        return 0;
    } else {
        p = cmd.cmd_vec[1].data();
    }
    if (chdir(p) == -1) {
        printf("cd %s : %s\n", p, strerror(errno));
        return -1;
    }
    return 0;
}

#define LIMIT(name, X)                                                       \
    {                                                                        \
        struct rlimit rlim;                                                  \
        getrlimit(X, &rlim);                                                 \
        std::string s_cur;                                                   \
        if (rlim.rlim_cur == RLIM_INFINITY)                                  \
            s_cur = "unlimited";                                             \
        else                                                                 \
            s_cur = std::to_string(rlim.rlim_cur);                           \
        std::string s_max;                                                   \
        if (rlim.rlim_max == RLIM_INFINITY)                                  \
            s_max = "unlimited";                                             \
        else                                                                 \
            s_max = std::to_string(rlim.rlim_max);                           \
        printf("%20s %10s %10s %s\n", #X, s_cur.data(), s_max.data(), name); \
    }

int do_ulimit(cmd_t &cmd) {
    LIMIT("虚拟内存大小", RLIMIT_AS);
    LIMIT("core 文件大小", RLIMIT_CORE);
    LIMIT("CPU 总的时间大小", RLIMIT_CPU);
    LIMIT("数据段(初始化数据, 未初始化数据, 堆)", RLIMIT_DATA);
    LIMIT("文件大小", RLIMIT_FSIZE);
    LIMIT("文件锁的个数", RLIMIT_LOCKS);
    LIMIT("内存中可以锁定的大小", RLIMIT_MEMLOCK);
    LIMIT("消息队列的大小", RLIMIT_MSGQUEUE);
    LIMIT("进程优先级的上限", RLIMIT_NICE);
    LIMIT("文件描述符的最大限制", RLIMIT_NOFILE);
    LIMIT("用户的进程线程数", RLIMIT_NPROC);
    LIMIT("物理内存大小", RLIMIT_RSS);
    LIMIT("调度的优先级", RLIMIT_RTPRIO);
    LIMIT("调度时 CPU 的最大耗时 毫秒", RLIMIT_RTTIME);
    LIMIT("信号队列的长度", RLIMIT_SIGPENDING);
    LIMIT("栈大小", RLIMIT_STACK);
    return 0;
}

// do_ls
std::string uid_to_name(uid_t uid) {
    struct passwd *pw_ptr = getpwuid(uid);

    if (pw_ptr == NULL) {  // 无该 uid 对应的用户
        return std::to_string(uid);
    } else {
        return std::string(pw_ptr->pw_name);
    }
}

std::string gid_to_name(gid_t gid) {
    struct group *grp_ptr = getgrgid(gid);

    if (grp_ptr == NULL) {  // 无该 gid 对应的组
        return std::to_string(gid);
    } else {
        return std::string(grp_ptr->gr_name);
    }
}

std::string mode_to_str(int mode) {
    std::string result = "----------";

    // 文件类型
    if (S_ISDIR(mode))
        result[0] = 'd';  // 目录
    if (S_ISCHR(mode))
        result[0] = 'c';  // 设备文件
    if (S_ISBLK(mode))
        result[0] = 'b';  // 块文件

    // 用户权限
    if (mode & S_IRUSR)
        result[1] = 'r';
    if (mode & S_IWUSR)
        result[2] = 'w';
    if (mode & S_IXUSR)
        result[3] = 'x';

    // 组权限
    if (mode & S_IRGRP)
        result[4] = 'r';
    if (mode & S_IWGRP)
        result[5] = 'w';
    if (mode & S_IXGRP)
        result[6] = 'x';

    // 其他人权限
    if (mode & S_IROTH)
        result[7] = 'r';
    if (mode & S_IWOTH)
        result[8] = 'w';
    if (mode & S_IXOTH)
        result[9] = 'x';
    return result;
}

void show_file_info(const std::string &file_name, const struct stat *stat_ptr) {
    printf("%s", mode_to_str(stat_ptr->st_mode).data());
    printf("%4d ", (int)stat_ptr->st_nlink);
    printf("%-8s ", uid_to_name(stat_ptr->st_uid).data());
    printf("%-8s ", gid_to_name(stat_ptr->st_gid).data());
    printf("%8ld ", (long)stat_ptr->st_size);
    printf("%.12s ", 4 + ctime(&stat_ptr->st_mtime));
    printf("%s\n", file_name.data());
}

int do_stat(const std::string &file_name, int dir_fd) {
    struct stat info;

    if (fstatat(dir_fd, file_name.data(), &info, 0) == -1) {
        perror(file_name.data());
        return -1;
    }
    show_file_info(file_name, &info);
    return 0;
}

int is_directory(const std::string &name) {
    struct stat info;
    if (stat(name.data(), &info) == -1)
        return -1;
    if (S_ISDIR(info.st_mode))
        return 1;
    else
        return 0;
}

int do_ls(cmd_t &cmd) {
    std::string name;
    if (cmd.cmd_vec.size() == 1)
        name = ".";
    else
        name = cmd.cmd_vec[1];
    int ret = is_directory(name);
    if (ret == -1)
        return -1;
    if (ret == 1) {  // 目录
        DIR *dir_ptr = opendir(name.data());
        if (dir_ptr == NULL) {
            // 无法打开目录
            perror(name.data());
            return -1;
        }
        struct dirent *dirent_ptr;
        while ((dirent_ptr = readdir(dir_ptr)) != NULL)
            if (do_stat(dirent_ptr->d_name, dirfd(dir_ptr)) == -1)
                return -1;
        closedir(dir_ptr);
        return 0;
    } else {  // 普通文件
        return do_stat(name, AT_FDCWD);
    }
}

// do_cp
int get_absolute_name(const std::string &from, std::string &to) {
    std::string str;
    if (from.front() != '/') {
        // 获取绝对路径
        char *p = get_current_dir_name();
        str     = std::string(p) + "/" + from;
        free(p);
    } else {
        str = from;
    }
    std::vector<std::string> ve;
    size_t                   pos_begin = 0;
    while (pos_begin != std::string::npos) {
        size_t      pos_end = str.find("/", pos_begin);
        std::string current_str;
        if (pos_end == std::string::npos) {
            current_str = str.substr(pos_begin);
            pos_begin   = std::string::npos;
        } else {
            current_str = str.substr(pos_begin, pos_end - pos_begin);
            pos_begin   = pos_end + 1;
        }
        if (current_str == "" || current_str == ".") {
            // 跳过
        } else if (current_str == "..") {
            if (ve.empty()) {
                printf("invalid filename\n");
                return -1;
            }
            ve.pop_back();
        } else {
            ve.push_back(current_str);
        }
    }
    to = "/";
    for (auto &data : ve)
        to += "/" + data;
    if (to.size() > 1)
        to += "/";
    return 0;
}

int argument_is_same(const std::string &left, const std::string &right) {
    std::string to_left;
    std::string to_right;
    if (get_absolute_name(left, to_left) == -1)
        return -1;
    if (get_absolute_name(right, to_right) == -1)
        return -1;
    return to_left == to_right ? 1 : 0;
}

std::string get_file_name(const std::string &name) {
    size_t pos = name.find_last_of('/');
    if (pos == std::string::npos)
        return name;
    return name.substr(pos + 1);
}

int cp_file(const std::string &from, const std::string &to) {
    int in_fd = open(from.data(), O_RDONLY);
    if (in_fd == -1) {
        perror(from.data());
        return -1;
    }

    int out_fd = open(to.data(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd == -1) {
        perror(to.data());
        return -1;
    }

    char buf[1024];

    for (;;) {
        int buf_len = read(in_fd, buf, sizeof(buf));
        if (buf_len < 0)
            return -1;
        if (buf_len == 0)
            break;
        write(out_fd, buf, buf_len);
    }

    close(in_fd);
    close(out_fd);
    return 0;
}

int cp_directory(const std::string &from, const std::string &to) {
    std::queue<std::pair<std::string, std::string>> qu;
    qu.push(std::make_pair(from, to));

    for (;;) {
        if (qu.empty())
            break;
        auto data = qu.front();
        qu.pop();

        if (is_directory(data.second) == 0) {
            // data.second 存在且是文件，失败
            printf("无法拷贝从目录到文件 且 文件存在的情况\n");
            return -1;
        }

        if (is_directory(data.second) == -1) {
            // data.second 不存在
            if (mkdir(data.second.data(), 0755) == -1) {
                perror("");
                return -1;
            }
        }

        // data.first 存在且是目录
        DIR *dir_ptr = opendir(data.first.data());
        if (dir_ptr == NULL) {
            perror(data.first.data());
            return -1;
        }

        struct dirent *dirent_ptr;
        while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
            if (is_directory(data.first + "/" + dirent_ptr->d_name) == 0) {
                // 文件
                int ret = cp_file(data.first + "/" + dirent_ptr->d_name,
                                  data.second + "/" + dirent_ptr->d_name);
                if (ret == -1)
                    return -1;
            } else {
                // 目录
                if (strcmp(dirent_ptr->d_name, ".") == 0)
                    continue;
                if (strcmp(dirent_ptr->d_name, "..") == 0)
                    continue;
                qu.push(std::make_pair(data.first + "/" + dirent_ptr->d_name,
                                       data.second + "/" + dirent_ptr->d_name));
            }
        }

        closedir(dir_ptr);
    }
    return 0;
}

// 拷贝 文件 --> 文件，且 文件存在
int cp_file_to_file(const std::string &from, const std::string &to) {
    return cp_file(from, to);
}

// 拷贝 文件 --> 目录，且 目录存在
int cp_file_to_directory(const std::string &from, const std::string &to) {
    return cp_file(from, to + "/" + get_file_name(from));
}

// 拷贝 文件 --> 文件 或 目录，且 文件 或 目录 不存在
int cp_file_to_file_or_directory(const std::string &from,
                                 const std::string &to) {
    if (to.size() > 0 && to.back() == '/') {
        // to 是目录，失败
        printf("无法拷贝 文件 --> 目录，且 目录不存在的情况\n");
        return -1;
    } else {
        // to 是文件
        cp_file(from, to);
        return 0;
    }
}

// 拷贝 目录 --> 文件，且 文件存在，直接失败
int cp_directory_to_file(const std::string &from, const std::string &to) {
    printf("无法拷贝 目录 --> 文件，且 文件存在的情况\n");
    return -1;
}

// 拷贝 目录 --> 目录，且 目录存在
int cp_directory_to_directory(const std::string &from, const std::string &to) {
    std::string str = from;
    if (str.size() > 0 && str.back() == '/')
        str.pop_back();
    size_t pos = str.find_last_of('/');
    if (pos != std::string::npos)
        str = str.substr(pos + 1);
    return cp_directory(from, to + "/" + str);
}

// 拷贝 目录 --> 文件 或 目录，且 文件 或 目录 不存在
int cp_directory_to_file_or_directory(const std::string &from,
                                      const std::string &to) {
    return cp_directory(from, to);
}

int do_cp(cmd_t &cmd) {
    if (cmd.cmd_vec.size() != 3) {
        printf("please use : cp ... ...\n");
        return -1;
    }

    if (is_directory(cmd.cmd_vec[1]) == -1) {
        // 第一个文件参数不存在
        perror(cmd.cmd_vec[1].data());
        return -1;
    }

    int ret = argument_is_same(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    if (ret == -1)
        return -1;
    if (ret == 1) {
        // 源文件或目录 和 目的文件或目录相同
        printf(" %s and %s is same\n",
               cmd.cmd_vec[1].data(),
               cmd.cmd_vec[2].data());
        return -1;
    }

    if (is_directory(cmd.cmd_vec[1]) == 0 &&
        is_directory(cmd.cmd_vec[2]) == 0) {
        // 文件 --> 文件，且 文件存在
        return cp_file_to_file(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    }

    if (is_directory(cmd.cmd_vec[1]) == 0 &&
        is_directory(cmd.cmd_vec[2]) == 1) {
        // 文件 --> 目录，且 目录存在
        return cp_file_to_directory(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    }

    if (is_directory(cmd.cmd_vec[1]) == 0 &&
        is_directory(cmd.cmd_vec[2]) == -1) {
        // 文件 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
        return cp_file_to_file_or_directory(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    }

    if (is_directory(cmd.cmd_vec[1]) == 1 &&
        is_directory(cmd.cmd_vec[2]) == 0) {
        // 目录 --> 文件，且 文件存在
        return cp_directory_to_file(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    }

    if (is_directory(cmd.cmd_vec[1]) == 1 &&
        is_directory(cmd.cmd_vec[2]) == 1) {
        // 目录 --> 目录，且 目录存在
        return cp_directory_to_directory(cmd.cmd_vec[1], cmd.cmd_vec[2]);
    }

    if (is_directory(cmd.cmd_vec[1]) == 1 &&
        is_directory(cmd.cmd_vec[2]) == -1) {
        // 目录 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
        return cp_directory_to_file_or_directory(cmd.cmd_vec[1],
                                                 cmd.cmd_vec[2]);
    }

    return 0;
}

// do_bc

char            *data = NULL;  // 存储输入字符串
std::stack<char> stack_char;   // 存储运算符
std::stack<long> stack_long;   // 存储运算数

void input_bc() {
    data = readline("> ");

    if (data == NULL)  // 读入 EOF
        exit(EXIT_SUCCESS);

    if (data[0] != '\0')
        add_history(data);

    // 移除多余的空格
    int k = 0;
    for (size_t i = 0; data[i] != '\0'; ++i)
        if (data[i] != ' ')
            data[k++] = data[i];
    if (k > 0 && data[k - 1] == '=')
        data[k - 1] = '\0';
    else
        data[k] = '\0';
}

bool count_one_char(char ch) {
    if (stack_long.size() < 2)
        return false;

    long rhs = stack_long.top();
    stack_long.pop();
    long lhs = stack_long.top();
    stack_long.pop();
    long data;
    switch (ch) {
    case '+':
        data = lhs + rhs;
        break;
    case '-':
        data = lhs - rhs;
        break;
    case '*':
        data = lhs * rhs;
        break;
    case '/':
        if (rhs == 0)
            return false;
        data = lhs / rhs;
        break;
    default:
        return false;
    }
    stack_long.push(data);
    return true;
}

bool solve() {
    char *st = data;
    if (*st == '+') {  // 解决开头类似 +123 的情况
        ++st;
    } else if (*st == '-') {  // 解决开头类似 -123 的情况
        stack_long.push(0);
        stack_char.push(*st++);
    }

    while (*st != '\0') {
        if (isdigit(*st)) {  // 当前是数字
            long data = strtol(st, &st, 10);
            stack_long.push(data);
            continue;
        }

        if (*st == '(') {
            stack_char.push(*st++);
            if (*st == '+') {  // 解决 类似 (+123) 的问题
                ++st;
            } else if (*st == '-') {  // 解决 类似 (-123) 的问题
                stack_long.push(0);
                stack_char.push(*st++);
            }
            continue;
        }
        if (*st == ')') {
            for (;;) {
                if (stack_char.empty())
                    return false;
                char ch = stack_char.top();
                stack_char.pop();
                if (ch == '(')
                    break;
                if (count_one_char(ch) == false)
                    return false;
            }
            ++st;
            continue;
        }
        if (*st != '+' && *st != '-' && *st != '*' && *st != '/')
            return false;
        for (;;) {
            if (stack_char.empty() || stack_char.top() == '(') {
                stack_char.push(*st++);
                break;
            }
            char ch = stack_char.top();
            if ((ch == '+' || ch == '-') && (*st == '*' || *st == '/')) {
                stack_char.push(*st++);
                break;
            }
            if (count_one_char(ch) == false)
                return false;
            stack_char.pop();
        }
    }
    for (;;) {
        if (stack_char.empty())
            break;
        char ch = stack_char.top();
        if (count_one_char(ch) == false)
            return false;
        stack_char.pop();
    }
    if (stack_long.size() != 1)
        return false;
    std::cout << stack_long.top() << std::endl;
    return true;
}

void output() {
    if (data[0] == '\0')
        return;

    if (solve() == false)
        std::cout << "输入格式错误" << std::endl;

    if (data != NULL) {
        free(data);
        data = NULL;
    }
    // 清空栈，避免影响下次计算
    while (!stack_char.empty())
        stack_char.pop();
    while (!stack_long.empty())
        stack_long.pop();
}

int do_bc(cmd_t &cmd) {
    for (;;) {
        input_bc();
        output();
    }

    return 0;
}

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

void usage() {
    fputs("usage:\n", stderr);
    error(EXIT_SUCCESS, 0, " <file>...");
}

void bad_usage() {
    error(EXIT_SUCCESS, 0, "bad usage");
    fputs("\n", stderr);
    usage();
}

// 传递数据
void handle_use_cat(FILE *fp) {
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != NULL)
        fputs(buf, stdout);
}

void process_argv_use_cat(cmd_t &cmd) {
    bool handle_stdin = isatty(0) ? false : true;
    if (handle_stdin) {
        handle_use_cat(stdin);
    } else if (cmd.cmd_vec.size() == 1) {
        bad_usage();
        return;
    }
    for (size_t i = 1; i < cmd.cmd_vec.size(); ++i) {
        FILE *fp = fopen(cmd.cmd_vec[i].data(), "r");
        if (fp == NULL) {
            error(
                EXIT_SUCCESS, errno, "cannot open  %s", cmd.cmd_vec[i].data());
            continue;
        }

        if (cmd.cmd_vec.size() > 2 || handle_stdin) {
            printf("::::::::::::::::::::::::::::\n");
            printf("%s\n", cmd.cmd_vec[i].data());
            printf("::::::::::::::::::::::::::::\n");
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

void signal_handle(int sig) {
    if (sig == SIGWINCH) {
        // 窗口大小改变
        get_tty_row_col();
    }
}

void set_signal() {
    struct sigaction act;
    act.sa_handler = signal_handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &act, NULL);
}

void process_argv_use_more(cmd_t &cmd) {
    bool handle_stdin = isatty(0) ? false : true;
    if (handle_stdin == false && cmd.cmd_vec.size() == 1) {
        bad_usage();
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

    for (size_t i = 1; i < cmd.cmd_vec.size(); ++i) {
        FILE *fp = fopen(cmd.cmd_vec[i].data(), "r");
        if (fp == NULL) {
            snprintf(buf,
                     sizeof(buf),
                     "cannot open %s：%s",
                     cmd.cmd_vec[i].data(),
                     strerror(errno));
            goto failure;
        }

        // 判断是否是目录
        struct stat info;
        if (stat(cmd.cmd_vec[i].data(), &info) == -1) {
            snprintf(buf,
                     sizeof(buf),
                     "cannot open %s：%s",
                     cmd.cmd_vec[i].data(),
                     strerror(errno));
            goto failure;
        }

        if (S_ISDIR(info.st_mode)) {
            snprintf(buf, sizeof(buf), "%s directory", cmd.cmd_vec[i].data());
            goto failure;
        }

        goto success;

    failure:

        if (i + 1 < cmd.cmd_vec[i].size()) {
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
            snprintf(buf, sizeof(buf), "Next file %s", cmd.cmd_vec[i].data());
            handle_user_input(buf);
        }

        if (cmd.cmd_vec[i].size() > 2 || handle_stdin) {
            fputs(":::::::::::::::::::::::::::::::::\n", stdout);
            ++num_of_lines;
            fputs(cmd.cmd_vec[i].data(), stdout);
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

int do_more(cmd_t &cmd) {
    if (isatty(1)) {
        // 标准输出是终端
        process_argv_use_more(cmd);
    } else {
        // 标准输出被重定向到文件 或 管道
        // 仅仅当 cat 使用
        process_argv_use_cat(cmd);
    }

    return 0;
}

int do_jobs(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    list_job(-1);
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_bg(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    if (cmd.cmd_vec.size() != 2) {
        printf("please use bg jid\n");
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    int jid = atoi(cmd.cmd_vec[1].data());
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    kill(-jobs[jid].pgid, SIGCONT);
    list_job(jid);                                // 可能状态还没更新
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

int do_fg(cmd_t &cmd) {
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞信号
    if (cmd.cmd_vec.size() != 2) {
        printf("please use fg jid\n");
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    int jid = atoi(cmd.cmd_vec[1].data());
    if (jobs.find(jid) == jobs.end()) {
        printf("job not find: %d\n", jid);
        sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
        return -1;
    }
    tcsetpgrp(0, jobs[jid].pgid);
    kill(-jobs[jid].pgid, SIGCONT);
    curr_jid = jid;  // 为了避免作业控制打出前台任务
    while (tcgetpgrp(0) == jobs[jid].pgid)
        sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
    return 0;
}

std::map<std::string, int (*)(cmd_t &)> m;
std::map<std::string, int (*)(cmd_t &)> m_test;

void init_cmd_builtin() {
    m["about"]     = do_about;
    m["exit"]      = do_exit;
    m["quit"]      = do_quit;
    m["cd"]        = do_cd;
    m["ulimit"]    = do_ulimit;
    m["jobs"]      = do_jobs;
    m["bg"]        = do_bg;
    m["fg"]        = do_fg;
    m["ls"]        = do_ls;
    m["cp"]        = do_cp;
    m_test["bc"]   = do_bc;
    m_test["more"] = do_more;
}

void handle_signal(int sig) {
    for (;;) {
        int wstatus;
        int fd = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
        if (fd <= 0)
            break;
        // 进程号 -> 作业号
        if (pids.find(fd) == pids.end()) {
            printf("can't find fd: %d\n", fd);
            exit(-1);
            continue;
        }
        int jid = pids[fd];
        // 作业号 -> 作业
        if (jobs.find(jid) == jobs.end()) {
            list_job(-1);
            printf("can't find jid: %d \n", jid);
            exit(-1);
            continue;
        }
        // 作业中的进程
        if (jobs[jid].tasks.find(fd) == jobs[jid].tasks.end()) {
            printf("can't find fd(%d) in jid(%d)\n", fd, jid);
            exit(-1);
            continue;
        }
        if (WIFSTOPPED(wstatus)) {
            // 运行 -> 暂停
            ++jobs[jid].count_stop;
            --jobs[jid].count_run;
            jobs[jid].tasks[fd].status = STOP;
        } else if (WIFCONTINUED(wstatus)) {
            // 暂停 -> 运行
            --jobs[jid].count_stop;
            ++jobs[jid].count_run;
            jobs[jid].tasks[fd].status = RUN;
        } else {
            // 运行 或 暂停 -> 退出
            if (jobs[jid].tasks[fd].status == RUN)
                --jobs[jid].count_run;
            else
                --jobs[jid].count_stop;
            if (WIFSIGNALED(wstatus)) {
                ++jobs[jid].count_kill;
                jobs[jid].tasks[fd].status = KILL;
            } else {
                ++jobs[jid].count_done;
                jobs[jid].tasks[fd].status = DONE;
            }
        }
        if (tcgetpgrp(0) == jobs[jid].pgid && jobs[jid].count_run == 0) {
            // 当前的作业是前台作业, 而且要放弃前台进程组
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }
}

void init_signal_handle() {
    signal(SIGINT, SIG_IGN);         // ctrl+c
    signal(SIGQUIT, SIG_IGN);        // ctrl+/
    signal(SIGTSTP, SIG_IGN);        // ctrl+z
    signal(SIGCHLD, handle_signal);  // 子进程退出, 暂停, 继续
}

int run_cmd(cmd_t &cmd) {
    // 处理重定向
    if (handle_redirection(cmd) != 0)
        return -1;
    // 处理内置命令
    if (m.find(cmd.cmd_vec[0]) != m.end())
        return m[cmd.cmd_vec[0]](cmd);
    if (m_test.find(cmd.cmd_vec[0]) != m_test.end())
        return m_test[cmd.cmd_vec[0]](cmd);
    // 处理非内置命令
    char **argv;
    argv = (char **)malloc(sizeof(cmd.cmd_vec.size()) + 1);
    for (size_t i = 0; i < cmd.cmd_vec.size(); ++i)
        argv[i] = (char *)cmd.cmd_vec[i].data();
    argv[cmd.cmd_vec.size()] = NULL;
    execvp(argv[0], argv);
    perror(argv[0]);
    free(argv);
    return -1;
}

void run_cmd() {
    curr_jid = -1;     // 用于检测作业时, 输出不跳过当前作业
    if (cmds.empty())  // 命令为空, 直接跳过
        return;
    // 是否在当前进程处理
    if (fg && cmds.size() == 1 && cmds[0].in.empty() && cmds[0].out.empty() &&
        cmds[0].add.empty()) {
        // 非 管道 重定向 以及 后台命令, 才可能在当前进程中运行
        if (m.find(cmds[0].cmd_vec[0]) != m.end()) {
            m[cmds[0].cmd_vec[0]](cmds[0]);
            return;
        }
    }
    // 处理命令
    sigprocmask(SIG_SETMASK, &mask_child, NULL);  // 阻塞所有信号
    job_t job;
    for (size_t i = 0; i < cmds.size(); ++i) {
        int pipe_fd[2];
        if (i + 1 != cmds.size() && pipe(pipe_fd) < 0) {
            // 不是最后一个命令需要新建管道
            perror("");
            return;
        }
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            setpgid(0, i == 0 ? 0 : job.pgid);  // 设置新的进程组
            if (i + 1 != cmds.size()) {
                // 将标准输出重定向到管道
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                if (pipe_fd[1] != STDOUT_FILENO)
                    close(pipe_fd[1]);
            }
            // 恢复信号处理
            signal(SIGINT, SIG_DFL);   // ctrl+c
            signal(SIGQUIT, SIG_DFL);  // ctrl+/
            signal(SIGTSTP, SIG_DFL);  // ctrl+z
            signal(SIGCHLD, SIG_DFL);  // 子进程退出, 暂停, 继续
            sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
            exit(run_cmd(cmds[i]));
        } else {
            // 父进程
            if (i == 0) {
                job.pgid       = fd;
                job.count_run  = cmds.size();
                job.count_stop = 0;
                job.count_kill = 0;
                job.count_done = 0;
                curr_jid       = next_jid++;
            }
            task_t task;
            task.cmd      = cmds[i].cmd_str;
            task.status   = RUN;
            job.tasks[fd] = task;
            pids[fd]      = curr_jid;

            setpgid(fd, job.pgid);  // 设置新的进程组

            if (i + 1 != cmds.size()) {
                // 将标准输入重定向到管道
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                if (pipe_fd[0] != STDIN_FILENO)
                    close(pipe_fd[0]);
            } else {
                // 将标准输入重定向到 /dev/tty
                int shell_tty = open("/dev/tty", O_RDONLY);
                dup2(shell_tty, STDIN_FILENO);
                if (shell_tty != STDIN_FILENO)
                    close(shell_tty);
            }
        }
    }

    jobs[curr_jid] = job;

    if (fg) {
        // 前台作业
        tcsetpgrp(0, job.pgid);  // 设置前台进程组
        while (tcgetpgrp(0) == job.pgid)
            sigsuspend(&mask_empty);  // 解阻塞信号, 然后暂停
    } else {
        list_job(curr_jid, true);
        curr_jid = -1;  // 用于检测作业时, 输出不跳过当前作业
    }
    sigprocmask(SIG_UNBLOCK, &mask_child, NULL);  // 解除信号阻塞
}

int main() {
    init_user_info();
    init_cmd_builtin();
    init_job();
    init_signal_handle();

    for (;;) {
        get_prompt();   // 获取提示符
        get_input();    // 获取用户输入
        parse_input();  // 解析命令行
        run_cmd();      // 运行命令
        check_job();    // 检测作业
    }

    return 0;
}
