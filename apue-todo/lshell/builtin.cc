
#include "lshell.h"

// 存储内置命令
std::map<std::string, int (*)(int argc, char* argv[])> m_builtin;
#define BUILTIN(val) m_builtin[#val] = do_##val

// 存储测试命令
std::map<std::string, int (*)(int argc, char* argv[])> m_test_cmd;
#define TEST_CMD(val) m_test_cmd[#val] = do_##val

int do_about(int argc, char* argv[]) {
    printf("write by liuyunbin\n");
    return 0;
}

int do_exit(int argc, char* argv[]) {
    exit(0);
}

int do_cd(int argc, char* argv[]) {
    if (argc > 2) {
        printf("cd: too many arguments\n");
        return -1;
    }
    std::string user_home;

    uid_t user_id = getuid();

    struct passwd* pw_ptr = getpwuid(user_id);
    if (pw_ptr != NULL) {
        user_home = std::string(pw_ptr->pw_dir);
    }

    std::string str;
    if (argc == 1)
        str = user_home;
    else
        str = argv[1];

    if (chdir(str.data()) == -1) {
        perror("cd");
        return -1;
    }
    return 0;
}

void init_builtin() {
    BUILTIN(about);
    BUILTIN(bg);
    BUILTIN(cd);
    BUILTIN(exit);
    BUILTIN(fg);
    BUILTIN(jobs);
    BUILTIN(ulimit);
}

bool is_builtin(const cmd_t& cmd) {
    return m_builtin.find(cmd.vec[0]) != m_builtin.end();
}

bool run_builtin(int argc, char* argv[]) {
    return m_builtin[argv[0]](argc, argv);
}

void init_test_cmd() {
    TEST_CMD(bc);
    TEST_CMD(cat);
    TEST_CMD(cp);
    TEST_CMD(more);
    TEST_CMD(ls);
}

bool is_test_cmd(const cmd_t& cmd) {
    return m_test_cmd.find(cmd.vec[0]) != m_test_cmd.end();
}

bool run_test_cmd(int argc, char* argv[]) {
    return m_test_cmd[argv[0]](argc, argv);
}
