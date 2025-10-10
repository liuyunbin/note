#ifndef LSHELL_H_
#define LSHELL_H_

#include <dirent.h>
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
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

struct cmd_t {
    std::vector<std::string> vec;
    std::string              str;
    std::string              in;
    std::string              out;
    std::string              add;
};

// input.cc
std::string get_prompt();
std::string get_input();

int  parse_input(std::vector<cmd_t>& cmds, std::string& str);
void handle_input(std::vector<cmd_t>& cmds, bool& fg, std::string& input);

// builtin.cc
int do_about(int argc, char* argv[]);
int do_bg(int argc, char* argv[]);
int do_cd(int argc, char* argv[]);
int do_exit(int argc, char* argv[]);
int do_fg(int argc, char* argv[]);
int do_jobs(int argc, char* argv[]);
int do_ls(int argc, char* argv[]);

int do_bc(int argc, char* argv[]);
int do_cat(int argc, char* argv[]);
int do_cp(int argc, char* argv[]);
int do_more(int argc, char* argv[]);
int do_ulimit(int argc, char* argv[]);

void init_builtin();
bool is_builtin(const cmd_t& cmd);
bool run_builtin(int argc, char* argv[]);

void init_test_cmd();
bool is_test_cmd(const cmd_t& cmd);
bool run_test_cmd(int argc, char* argv[]);

// signal.cc
void init_signal();
void handle_signal(int sig);

// cmd.cc
int handle_redirection(const std::string& filename, int flag, int fd_new);
int handle_redirection(const cmd_t& cmd);
int run_cmd(const cmd_t& cmd);

// job.cc
int  list_jobs(int jid, bool no_status = false);
void init_jobs();
void handle_jobs(std::vector<cmd_t>& cmds, bool& fg);
void update_jobs(int fd, int status);
void check_jobs();

#endif
