
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

std::string uid_to_name(uid_t uid);
std::string gid_to_name(gid_t gid);

uid_t       get_user_id();
std::string get_user_name();
std::string get_user_home();

std::string get_input();

int parse_input(std::string input, std::vector<cmd_t>& cmds, bool& fg);

int run_cmd(const cmd_t& cmd);

void init_cmd_builtin();
bool is_cmd_builtin(const cmd& cmd);
int  run_cmd_builtin(const cmd& cmd);

void init_cmd_test();
bool is_cmd_test(const cmd& cmd);
int  run_cmd_test(const cmd& cmd);

void init_signal_handle();

void init_job();
void run_job(std::vector<cmd_t>& cmds, bool& fg);

#endif
