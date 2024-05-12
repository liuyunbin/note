#ifndef LSHELL_H_
#define LSHELL_H_

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

// input.cc
std::string get_input(const std::string& prompt);
int         parse_input(std::vector<cmd_t>& cmds, std::string& str);
void handle_input(std::vector<cmd_t>& cmds, bool& fg, std::string& input);

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
