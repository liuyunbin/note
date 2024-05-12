
#include "lshell.h"

std::string get_prompt() {
    char*       p        = get_current_dir_name();
    std::string curr_dir = p;
    free(p);

    std::string user_name, user_home;

    uid_t user_id = getuid();

    struct passwd* pw_ptr = getpwuid(user_id);
    if (pw_ptr != NULL) {
        user_name = std::string(pw_ptr->pw_name);
        user_home = std::string(pw_ptr->pw_dir);
    } else {
        user_name = std::to_string(user_id);
    }

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
