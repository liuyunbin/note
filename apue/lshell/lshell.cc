
#include "lshell.h"

#include <grp.h>                // getgrgid
#include <pwd.h>                // getpwuid
#include <readline/readline.h>  // readline
#include <sys/stat.h>           // stat
#include <sys/types.h>          // getuid
#include <unistd.h>             // getuid, get_current_dir_name

std::string uid_to_name(uid_t uid) {
    struct passwd *pw_ptr = getpwuid(uid);
    if (pw_ptr != NULL)
        return std::string(pw_ptr->pw_name);
    return std::to_string(uid);
}

std::string gid_to_name(gid_t gid) {
    struct group *grp_ptr = getgrgid(gid);
    if (grp_ptr != NULL)
        return std::string(grp_ptr->gr_name);
    return std::to_string(gid);
}

uid_t get_user_id() {
    return getuid();
}

std::string get_user_name() {
    return uid_to_name(getuid());
}

std::string get_user_home() {
    struct passwd *pw_ptr = getpwuid(getuid());
    if (pw_ptr != NULL)
        return std::string(pw_ptr->pw_dir);
    return "";
}

int is_directory(const char *name) {
    struct stat info;
    if (stat(name, &info) == -1)
        return -1;
    if (S_ISDIR(info.st_mode))
        return 1;
    else
        return 0;
}

std::string get_prompt() {
    char       *p        = get_current_dir_name();
    std::string curr_dir = p;
    free(p);

    uid_t       user_id   = get_user_id();
    std::string user_name = get_user_name();
    std::string user_home = get_user_home();

    std::string prompt = user_name + ":";
    if (curr_dir == user_home)
        prompt += "~";
    else if (curr_dir < user_home)
        prompt += curr_dir;
    else if (curr_dir.compare(0, user_home.size(), user_home) != 0)
        prompt += curr_dir;
    else if (curr_dir[user_home.size()] != '/')
        prompt += curr_dir;
    else
        prompt += "~" + std::string(curr_dir.data() + user_home.size());

    if (user_id == 0)
        prompt += "# ";
    else
        prompt += "$ ";
    return prompt;
}

void get_input(std::string &input) {
    std::string prompt = get_prompt();
    char       *p      = readline(prompt.data());

    if (p == NULL) {
        // printf("read EOF, exit\n");
        exit(0);
    }

    input.clear();
    for (size_t i = 0; p[i] != '\0' && p[i] != '\n'; ++i)
        if (p[i] != '~')
            input += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            input += get_user_home();
        else
            input += p[i];
    free(p);
}
