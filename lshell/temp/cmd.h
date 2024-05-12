
#ifndef CMD_H_
#define CMD_H_

class cmd_t {
public:
    cmd_t(const std::string& str);

    void run();

    char** argv;
};

class cmds_t {};

#endif
