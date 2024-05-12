
#include "lshell.h"

std::map<std::string, int (*)(int argc, char* argv[])> m;  // 存储内置命令

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
    m["about"]  = do_about;
    m["exit"]   = do_exit;
    m["cd"]     = do_cd;
    m["ulimit"] = do_ulimit;
    m["jobs"]   = do_jobs;
    m["bg"]     = do_bg;
    m["fg"]     = do_fg;
}

bool is_builtin(const cmd_t& cmd) {
    return m.find(cmd.vec[0]) != m.end();
}

bool run_builtin(int argc, char* argv[]) {
    return m[argv[0]](argc, argv);
}
