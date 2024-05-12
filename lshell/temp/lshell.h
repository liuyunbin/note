#ifndef LSHELL_H_
#define LSHELL_H_

#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <map>
#include <string>
#include <vector>

struct cmd_t {
    std::vector<std::string> vec;
    std::string              str;
    std::string              in;
    std::string              out;
    std::string              add;
};

// signal.cc
void init_signal();
void handle_signal(int sig);

// prompt.cc
std::string get_prompt();

// input.cc
std::string get_input(const std::string& prompt);
int         parse_input(std::vector<cmd_t>& cmds, std::string& str);
void handle_input(std::vector<cmd_t>& cmds, bool& fg, std::string& input);

// builtin.cc
void init_builtin();
bool is_builtin(const cmd_t& cmd);
bool run_builtin(int argc, char* argv[]);

// cmd.cc
int handle_redirection(const std::string& filename, int flag, int fd_new);
int handle_redirection(const cmd_t& cmd);
int run_cmd(const cmd_t& cmd);

// job.cc
void handle_jobs(std::vector<cmd_t>& cmds, bool& fg);
void update_jobs(int fd, int status);
void check_jobs();

int list_jobs(int jid, bool no_status = false);

int do_bg(int argc, char* argv[]);
int do_fg(int argc, char* argv[]);

#endif
