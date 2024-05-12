
#include "lshell.h"

int main() {
    std::string prompt;
    std::string input;
    std::vector<cmd_t> cmds;
    bool fg;

    init_signal();
    init_builtin();

    for (;;) {
        prompt = get_prompt();
        input = get_input(prompt);
        handle_input(cmds, fg, input);
        handle_jobs(cmds, fg);
        check_jobs();
    }

    return 0;
}
