
#include "lshell.h"

bool number          = false;  // 行号包括空行
bool number_nonblank = false;  // 行号不包括空行
bool squeeze_blank   = false;  // 折叠空行
bool handle_tab      = false;  // TAB 转换

int usage() {
    fputs("usage: cat [OPTION]... [FILE]... \n", stdout);
    fputs("                                 \n", stdout);
    fputs("  -b    显示行号(不包括空行)     \n", stdout);
    fputs("  -h    帮助信息                 \n", stdout);
    fputs("  -n    显示行号(包括空行)       \n", stdout);
    fputs("  -s    压缩连续的空行           \n", stdout);
    fputs("  -T    TAB => ^I                \n", stdout);
    return 0;
}

void handle_cat(FILE* fp) {
    int  line           = 0;
    bool pre_line_blank = false;

    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (buf[0] != '\n') {
            // 当前行不是空行
            pre_line_blank = false;
            if (number || number_nonblank)
                printf("%6d ", ++line);  // 输出行号
        } else {
            // 当前行是空行
            if (pre_line_blank && squeeze_blank)
                continue;  // 连续的空行需要折叠
            pre_line_blank = true;
            if (number && not number_nonblank)
                printf("%6d ", ++line);  // 输出行号
        }

        for (int i = 0; buf[i] != '\0'; ++i)
            if (handle_tab && buf[i] == '\t')
                fputs("^I", stdout);
            else
                fputc(buf[i], stdout);
    }
}

int do_cat(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "bhnsT")) != -1) {
        switch (opt) {
        case 'b':
            number_nonblank = true;
            break;
        case 'h':
            return usage();
            break;
        case 'n':
            number = true;
            break;
        case 's':
            squeeze_blank = true;
            break;
        case 'T':
            handle_tab = true;
            break;
        default:
            return -1;
        }
    }

    if (optind == argc)
        handle_cat(stdin);

    for (int i = optind; i < argc; ++i) {
        FILE* fp;
        if (strcmp(argv[i], "-") == 0) {
            fp = stdin;
        } else {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror("cat");
                continue;
            }
        }
        handle_cat(fp);
        fclose(fp);
    }

    return 0;
}
