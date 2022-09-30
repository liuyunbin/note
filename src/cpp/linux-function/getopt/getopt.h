#ifndef GETOPT_H_
#define GETOPT_H_

extern char *optarg; // 存储参数
extern int   optind; // 存储下一个在 argv 中, 将要解析的参数, 初始值为 1
extern int   opterr; // 是否输出错误信息, 0 表示不输出, 其他情况表示输出
extern int   optopt; // 存储错误的可选项

int getopt(          int argc, char * const argv[], const char *optstring);
int getopt_long(     int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);
int getopt_long_only(int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);

#endif
