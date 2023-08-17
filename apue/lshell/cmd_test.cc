
#include <map>

#include "lshell.h"

std::map<std::string, int (*)(int argc, char* argv[])> m_test;

void init_cmd_test() {
    m_test["cp"]   = do_cp;
    m_test["bc"]   = do_bc;
    m_test["more"] = do_more;
}

bool is_cmd_test(const cmd_t& cmd) {
    return m_test.find(cmd.vec[0]) != m_test.end();
}

int run_cmd_test(int argc, char* argv[]) {
    return m_test[argv[0]](argc, argv);
}
