
#include "lshell.h"

// 获取提示符
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

// 获取用户输入
std::string get_input() {
    std::string prompt = get_prompt();
    char*       p      = readline(prompt.data());

    if (p == NULL)
        exit(0);

    std::string    user_home;
    struct passwd* pw_ptr = getpwuid(getuid());
    if (pw_ptr != NULL)
        user_home = std::string(pw_ptr->pw_dir);

    std::string input;
    for (size_t i = 0; p[i] != '\0' && p[i] != '\n'; ++i)
        if (p[i] != '~')
            input += p[i];
        else if (p[i + 1] == ' ' || p[i + 1] == '\0' || p[i + 1] == '/')
            input += user_home;
        else
            input += p[i];
    free(p);

    // 去掉末尾的空白
    while (!input.empty() && input.back() == ' ')
        input.pop_back();
    // 加入历史命令
    if (!input.empty())
        add_history(input.data());
    return input;
}

// 解析单个命令
int parse_input(std::vector<cmd_t>& cmds, std::string& str) {
    while (!str.empty() && str.back() == ' ')
        str.pop_back();
    cmd_t cmd;
    cmd.str = str;
    for (size_t i = 0; i < str.size();) {
        while (i < str.size() && str[i] == ' ')
            ++i;
        if (i >= str.size())
            break;
        if (str[i] == '<') {
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.vec.empty() || i >= str.size()) {
                printf("please use: cmd <  file_name\n");
                return -1;
            }
            std::string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            cmd.in = name;
            continue;
        }
        if (str[i] == '>') {
            bool add = false;
            if (i + 1 < str.size() && str[i + 1] == '>') {
                ++i;
                add = true;
            }
            while (++i < str.size() && str[i] == ' ')
                ;
            if (cmd.vec.empty() || i >= str.size()) {
                if (add)
                    printf("please use: cmd >> file_name\n");
                else
                    printf("please use: cmd >  file_name\n");
                return -1;
            }
            std::string name;
            while (i < str.size() && str[i] != ' ')
                name.push_back(str[i++]);
            if (add)
                cmd.add = name;
            else
                cmd.out = name;
            continue;
        }
        std::string name;
        while (i < str.size() && str[i] != ' ')
            name.push_back(str[i++]);
        cmd.vec.push_back(name);
    }
    cmds.push_back(cmd);
    return 0;
}

// 解析用户输入
void handle_input(std::vector<cmd_t>& cmds, bool& fg, std::string& input) {
    // 判断是否后台运行
    if (!input.empty() && input.back() == '&') {
        input.pop_back();
        fg = false;
    } else {
        fg = true;
    }

    // 处理管道并存储其参数
    cmds.clear();
    for (size_t i = 0; i < input.size(); ++i) {
        while (i < input.size() && input[i] == ' ')
            ++i;
        if (i >= input.size())
            break;
        if (input[i] == '|') {
            printf("invalid cmd!\n");
            cmds.clear();
            return;
        }
        std::string str;
        while (i < input.size() && input[i] != '|')
            str.push_back(input[i++]);
        if (parse_input(cmds, str) != 0) {
            cmds.clear();
            return;
        }
    }
}
