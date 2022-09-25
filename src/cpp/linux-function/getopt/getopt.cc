
#include "getopt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <vector>

#define no_argument 0
#define required_argument 1
#define optional_argument 2

char *optarg;    // 指向可选参数
int optind = 1;  // 表示下一个将要解析的参数
int opterr =
    1;  // 是否输出错误信息，0 表示不输出错误信息，其它值表示要输出错误信息
int optopt = '?';  // 表示未被识别的可选项

struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

enum __ord {
    REQUIRE_ORDER,  // optstring 以 '+' 开头 或 POSIXLY_CORRECT 设置 的情况
    PERMUTE,
    RETURN_IN_ORDER  // optstring 以 '-' 开头的情况
};

struct getopt_data {
    int optind;
    int opterr;
    int optopt;
    char *optarg;

    int initialized;  // 是否已初始化
    char *nextchar;

    enum __ord ordering;

    int first_nonopt;
    int last_nonopt;
};

// 拷贝所有的全局变量
static struct getopt_data g_getopt_data;

static void exchange(char **argv, struct getopt_data *d) {
    int left = d->first_nonopt;
    int mid = d->last_nonopt;
    int right = d->optind;

    if (d->first_nonopt != d->last_nonopt && d->last_nonopt != d->optind) {
        std::rotate(argv + left, argv + mid, argv + right);
        d->first_nonopt += (d->optind - d->last_nonopt);
        d->last_nonopt = d->optind;
    } else if (d->first_nonopt == d->last_nonopt) {
        d->first_nonopt = d->optind;
        d->last_nonopt = d->optind;
    }
}

static int process_long_option(int argc, char **argv, const char *optstring,
                               const struct option *longopts, int *longind,
                               int long_only, struct getopt_data *d,
                               int print_errors, const char *prefix) {
    char *name_end = d->nextchar;
    while (*name_end != '\0' && *name_end != '=') ++name_end;
    size_t name_len = name_end - d->nextchar;

    std::vector<const struct option *> found;
    for (const struct option *p = longopts; p->name != NULL; ++p)
        if (strncmp(p->name, d->nextchar, name_len) == 0 &&
            name_len == strlen(p->name))
            found.push_back(p);

    if (found.empty()) {
        // 查看是否前缀匹配
        for (const struct option *p = longopts; p->name; p++)
            if (strncmp(p->name, d->nextchar, name_len) == 0)
                found.push_back(p);

        if (found.size() >= 2) {
            if (print_errors) {
                fprintf(stderr,
                        "%s: option '%s%s' is ambiguous; possibilities:",
                        argv[0], prefix, d->nextchar);

                for (auto p : found)
                    fprintf(stderr, " '%s%s'", prefix, p->name);
                fprintf(stderr, "\n");
            }
            d->nextchar = NULL;
            d->optind++;
            d->optopt = 0;
            return '?';
        }
    }

    if (found.empty()) {
        if (long_only == 0                // getopt_long
            || argv[d->optind][1] == '-'  // 可选项以 "--" 开头
            || strchr(optstring, *d->nextchar) == NULL) {  // 在短选项中找不到
            // 解析失败
            if (print_errors)
                fprintf(stderr, "%s: unrecognized option '%s%s'\n", argv[0],
                        prefix, d->nextchar);

            d->nextchar = NULL;
            d->optind++;
            d->optopt = 0;
            return '?';
        }

        // get_long_only 且 可选项以 "-" 而不是 "--" 开头，将作为短选项解析
        return -1;
    }

    d->optind++;
    d->nextchar = NULL;
    if (*name_end == '=') {
        // 有参数
        if (found.back()->has_arg) {  // 要求参数 或 可选参数
            d->optarg = name_end + 1;
        } else {
            if (print_errors)
                fprintf(stderr, "%s: option '%s%s' doesn't allow an argument\n",
                        argv[0], prefix, found.back()->name);

            d->optopt = found.back()->val;
            return '?';
        }
    } else if (found.back()->has_arg == 1) {
        if (d->optind < argc) {
            d->optarg = argv[d->optind++];
        } else {
            if (print_errors)
                fprintf(stderr, "%s: option '%s%s' requires an argument\n",
                        argv[0], prefix, found.back()->name);

            d->optopt = found.back()->val;
            return optstring[0] == ':' ? ':' : '?';
        }
    }

    if (longind != NULL) *longind = found.back() - longopts;
    if (found.back()->flag != NULL) {
        *(found.back()->flag) = found.back()->val;
        return 0;
    }
    return found.back()->val;
}

// 初始化 getopt_data
static const char *getopt_initialize(int argc, char **argv,
                                     const char *optstring,
                                     struct getopt_data *d) {
    if (d->optind == 0) d->optind = 1;

    d->first_nonopt = d->last_nonopt = d->optind;
    d->nextchar = NULL;

    if (optstring[0] == '-') {
        // 重排序时，需要保证相对顺序不变
        d->ordering = RETURN_IN_ORDER;
        ++optstring;
    } else if (optstring[0] == '+') {
        // 只要遇到 非可选项就停止解析
        d->ordering = REQUIRE_ORDER;
        ++optstring;
    } else if (getenv("POSIXLY_CORRECT") != NULL) {
        // 只要遇到 非可选项就停止解析
        d->ordering = REQUIRE_ORDER;
    } else {
        d->ordering = PERMUTE;
    }

    d->initialized = 1;
    return optstring;
}

static int getopt_internal_r(int argc, char **argv, const char *optstring,
                             const struct option *longopts, int *longind,
                             int long_only, struct getopt_data *d) {
    if (argc < 1) return -1;

    if (d->optind == 0 || d->initialized == 0)
        optstring = getopt_initialize(argc, argv, optstring, d);
    else if (optstring[0] == '-' || optstring[0] == '+')
        optstring++;

    int print_errors = optstring[0] == ':' ? 0 : d->opterr;

// 测试 argv[optind] 是否 不是可选项
#define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

    d->optarg = NULL;

    if (d->nextchar == NULL || *d->nextchar == '\0') {
        if (d->ordering == PERMUTE) {
            exchange(argv, d);
            // 跳过所有的非可选项
            while (d->optind < argc && NONOPTION_P) d->optind++;
            d->last_nonopt = d->optind;
        }

        // 处理 "--"
        if (d->optind < argc && strcmp(argv[d->optind], "--") == 0) {
            d->optind++;
            exchange(argv, d);
            d->last_nonopt = argc;
            d->optind = argc;
        }

        // 已遍历所有元素
        if (d->optind == argc) {
            if (d->first_nonopt != d->last_nonopt) d->optind = d->first_nonopt;
            return -1;
        }

        if (NONOPTION_P) {
            if (d->ordering == REQUIRE_ORDER)  // 只要遇到非可选项，停止解析
                return -1;
            // optstring 以 '-' 打头的情况
            d->optarg = argv[d->optind++];
            return 1;
        }

        // 处理 长选项
        if (longopts) {
            if (argv[d->optind][1] == '-') {
                // 处理 "--" 开头的情况
                d->nextchar = argv[d->optind] + 2;
                return process_long_option(argc, argv, optstring, longopts,
                                           longind, long_only, d, print_errors,
                                           "--");
            }

            // 处理 getopt_long_only 中以 "-" 开头的情况
            if (long_only && (argv[d->optind][2] != '\0' ||
                              strchr(optstring, argv[d->optind][1]) == NULL)) {
                d->nextchar = argv[d->optind] + 1;
                int code = process_long_option(argc, argv, optstring, longopts,
                                               longind, long_only, d,
                                               print_errors, "-");
                if (code != -1)  // 解析长选项成功
                    return code;
            }
        }

        // 之后，作为短选项解析
        d->nextchar = argv[d->optind] + 1;
    }

    char c = *d->nextchar++;
    const char *temp = strchr(optstring, c);

    if (*d->nextchar == '\0') ++d->optind;

    if (temp == NULL || c == ':' || c == ';') {
        if (print_errors)
            fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
        d->optopt = c;
        return '?';
    }

    // 处理 W, -W foo 将当作 --foo 处理
    if (temp[0] == 'W' && temp[1] == ';' && longopts != NULL) {
        // 获取 参数
        if (*d->nextchar != '\0') {
            d->optarg = d->nextchar;
        } else if (d->optind == argc) {
            if (print_errors)
                fprintf(stderr, "%s: option requires an argument -- '%c'\n",
                        argv[0], c);
            d->optopt = c;
            return optstring[0] == ':' ? ':' : '?';
        } else {
            d->optarg = argv[d->optind];
        }

        d->nextchar = d->optarg;
        d->optarg = NULL;
        return process_long_option(argc, argv, optstring, longopts, longind,
                                   0 /* long_only */, d, print_errors, "-W ");
    }
    if (temp[1] == ':') {
        if (temp[2] == ':') {
            // 可选参数
            if (*d->nextchar != '\0') {
                d->optarg = d->nextchar;
                d->optind++;
            } else {
                d->optarg = NULL;
            }
            d->nextchar = NULL;
        } else {
            // 要求参数
            if (*d->nextchar != '\0') {
                d->optarg = d->nextchar;
                d->optind++;
            } else if (d->optind == argc) {
                if (print_errors)
                    fprintf(stderr, "%s: option requires an argument -- '%c'\n",
                            argv[0], c);
                d->optopt = c;
                c = optstring[0] == ':' ? ':' : '?';
            } else {
                d->optarg = argv[d->optind++];
            }
            d->nextchar = NULL;
        }
    }
    return c;
}

static int getopt_internal(int argc, char **argv, const char *optstring,
                           const struct option *longopts, int *longind,
                           int long_only) {
    g_getopt_data.optind = optind;
    g_getopt_data.opterr = opterr;

    int result = getopt_internal_r(argc, argv, optstring, longopts, longind,
                                   long_only, &g_getopt_data);

    optind = g_getopt_data.optind;
    optarg = g_getopt_data.optarg;
    optopt = g_getopt_data.optopt;

    return result;
}

int getopt(int argc, char *const *argv, const char *optstring) {
    return getopt_internal(argc, (char **)argv, optstring, NULL, NULL, 0);
}

int getopt_long(int argc, char *const *argv, const char *optstring,
                const struct option *longopts, int *longindex) {
    return getopt_internal(argc, (char **)argv, optstring, longopts, longindex,
                           0);
}

int getopt_long_r(int argc, char **argv, const char *optstring,
                  const struct option *longopts, int *longindex,
                  struct getopt_data *d) {
    return getopt_internal_r(argc, argv, optstring, longopts, longindex, 0, d);
}

int getopt_long_only(int argc, char *const *argv, const char *optstring,
                     const struct option *longopts, int *longindex) {
    return getopt_internal(argc, (char **)argv, optstring, longopts, longindex,
                           1);
}

int getopt_long_only_r(int argc, char **argv, const char *optstring,
                       const struct option *longopts, int *longindex,
                       struct getopt_data *d) {
    return getopt_internal_r(argc, argv, optstring, longopts, longindex, 1, d);
}
