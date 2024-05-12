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

// prompt.cc
std::string get_prompt();

int do_ulimit(int argc, char* argv[]);
int do_cat(int argc, char* argv[]);
int do_about(int argc, char* argv[]);
int do_exit(int argc, char* argv[]);
int do_cd(int argc, char* argv[]);
int do_jobs(int argc, char* argv[]);
int do_bg(int argc, char* argv[]);
int do_fg(int argc, char* argv[]);

// builtin.cc
void init_builtin();
bool is_builtin(const cmd_t& cmd);
bool run_builtin(int argc, char* argv[]);

#endif
