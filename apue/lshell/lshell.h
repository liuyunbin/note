
#ifndef LSHELL_
#define LSHELL_ 1

#include <string>
#include <vector>

struct cmd_t {
    std::vector<std::string> vec;
    std::string              str;
    std::string              in;
    std::string              out;
    std::string              add;
};

std::string uid_to_name(uid_t uid);  // uid => 用户名称
std::string gid_to_name(gid_t gid);  // gid => 组名称

uid_t       get_user_id();    // 获取 uid
std::string get_user_name();  // 获取 用户名称
std::string get_user_home();  // 获取 用户主目录

int is_directory(const char* name);  // 判断是否是目录

void init_cmd_builtin();  // 初始化内置命令
void init_cmd_test();     // 初始化测试命令
void init_job();          // 初始化作业

bool is_cmd_builtin(const cmd_t& cmd);  // 是否是内置命令
bool is_cmd_test(const cmd_t& cmd);     // 是否是测试命令

int run_cmd_builtin(int argc, char* argv[]);  // 运行内置命令
int run_cmd_test(int argc, char* argv[]);     // 运行测试命令
int run_cmd(const cmd_t& cmd);                // 运行所有命令

void get_input(std::string& input);  // 获取用户输入
// 解析用户输入
void parse_input(std::string& input, std::vector<cmd_t>& cmds, bool& fg);
void handle_job(const std::vector<cmd_t>& cmds, bool fg);  // 处理作业
void check_job();  // 检查已完成的作业

// 内置命令
int do_about(int argc, char* argv[]);
int do_exit(int argc, char* argv[]);
int do_cd(int argc, char* argv[]);
int do_ulimit(int argc, char* argv[]);
int do_jobs(int argc, char* argv[]);
int do_bg(int argc, char* argv[]);
int do_fg(int argc, char* argv[]);

// 测试命令
int do_ls(int argc, char* argv[]);
int do_cp(int argc, char* argv[]);
int do_bc(int argc, char* argv[]);
int do_more(int argc, char* argv[]);

#endif
