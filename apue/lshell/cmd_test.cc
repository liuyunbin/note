
#include <map>

#include "lshell.h"

int do_ls(const cmd& cmd);
int do_cp(const cmd& cmd);
int do_bc(const cmd& cmd);
int do_more(const cmd& cmd);

std::map<std::string, int (*)(cmd_t&)> m_test;

void init_cmd_builtin() {
    m_test["ls"]   = do_ls;
    m_test["cp"]   = do_cp;
    m_test["bc"]   = do_bc;
    m_test["more"] = do_more;
}

bool is_cmd_test(const cmd& cmd) {
    return m_test.find(cmd.str()) != m_test.end();
}

int run_cmd_test(const cmd& cmd) {
    if (is_cmd_test(cmd))
        return m_test[cmd.str](cmd);
    return -1;
}
