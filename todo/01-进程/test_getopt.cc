/*
int getopt(int argc, char * const argv[], const char *optstring);

遍历完返回 -1
报错返回 ?

optarg: 参数
optind: 下一参数的索引

a  ---- 无参数, 支持 -a
a: ---- 有参数, 支持 -a 123 或 -a123
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "nt:")) != -1) {
        switch (opt) {
        case 'n':
            printf("opt: %c\n", opt);
            break;
        case 't':
            printf("opt: %c, arg: %s\n", opt, optarg);
            break;
        default: /* '?' */
            return -1;
        }
    }

    for (int i = optind; i < argc; ++i) {
        if (i == optind) {
            printf("args:");
        }
        printf(" %s", argv[i]);
        if (i + 1 == argc) {
            printf("\n");
        }
    }

    return 0;
}
