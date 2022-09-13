
#ifndef CP_CP_H_
#define CP_CP_H_

#include <string>

// 如果 name 是目录，返回 1
// 如果 name 是文件，返回 0
// 如果 name 不存在，返回 -1
int is_directory(const std::string &name);

// 获取绝对路径，去掉 .. . 和 多余的 '/'
std::string get_absolute_name(const char *name);

// 比较参数的绝对路径是否相同
bool argument_is_same(const char *from, const char *to);

// 获取文件名，name 必须是一个文件
const char *get_file_name(const char *name);

// 拷贝文件
void cp_file(const std::string &from, const std::string &to);

// 拷贝目录
void cp_directory(const std::string &from, const std::string &to);

// 拷贝 文件 --> 文件，且 文件存在
void cp_file_to_file(const char *from, const char *to);

// 拷贝 文件 --> 目录，且 目录存在
void cp_file_to_directory(const char *from, const char *to);

// 拷贝 文件 --> 文件 或 目录，且 文件 或 目录 不存在
void cp_file_to_file_or_directory(const char *from, const char *to);

// 拷贝 目录 --> 文件，且 文件存在，直接失败
void cp_directory_to_file(const char *from, const char *to);

// 拷贝 目录 --> 目录，且 目录存在
void cp_directory_to_directory(const char *from, const char *to);

// 拷贝 目录 --> 文件 或 目录，且 文件 或 目录 不存在
void cp_directory_to_file_or_directory(const char *from, const char *to);

#endif

