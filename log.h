
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

std::string get_time() {
    time_t now = time(NULL);
    struct tm* info = localtime(&now);
    char buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", info);
    return buf;
}

void log(const std::string& msg = "") {
    std::cout << get_time() << " " << msg << std::endl;
}

std::map<int, std::string> m;            // 信号处理
std::map<int, std::string> dict_except;  // 存储浮点数异常
std::map<int, std::string> dict_round;   // 存储舍入模式

void init() {
    // 信号处理
    m[SIGHUP] = " 1-SIGHUP";
    m[SIGINT] = " 2-SIGINT";
    m[SIGQUIT] = " 3-SIGQUIT";
    m[SIGILL] = " 4-SIGILL";
    m[SIGTRAP] = " 5-SIGTRAP";
    m[SIGABRT] = " 6-SIGABRT";
    m[SIGBUS] = " 7-SIGBUS";
    m[SIGFPE] = " 8-SIGFPE";
    m[SIGKILL] = " 9-SIGKILL";
    m[SIGUSR1] = "10-SIGUSR1";
    m[SIGSEGV] = "11-SIGSEGV";
    m[SIGUSR2] = "12-SIGUSR2";
    m[SIGPIPE] = "13-SIGPIPE";
    m[SIGALRM] = "14-SIGALRM";
    m[SIGTERM] = "15-SIGTERM";
    m[SIGSTKFLT] = "16-SIGSTKFLT";
    m[SIGCHLD] = "17-SIGCHLD";
    m[SIGCONT] = "18-SIGCONT";
    m[SIGSTOP] = "19-SIGSTOP";
    m[SIGTSTP] = "20-SIGTSTP";
    m[SIGTTIN] = "21-SIGTTIN";
    m[SIGTTOU] = "22-SIGTTOU";
    m[SIGURG] = "23-SIGURG";
    m[SIGXCPU] = "24-SIGXCPU";
    m[SIGXFSZ] = "25-SIGXFSZ";
    m[SIGVTALRM] = "26-SIGVTALRM";
    m[SIGPROF] = "27-SIGPROF";
    m[SIGWINCH] = "28-SIGWINCH";
    m[SIGIO] = "29-SIGIO";
    m[SIGPWR] = "30-SIGPWR";
    m[SIGSYS] = "31-SIGSYS";

    // 浮点数异常
    dict_except[FE_DIVBYZERO] = "除以 0";
    dict_except[FE_INEXACT] = "结果不准确";
    dict_except[FE_INVALID] = "参数非法";
    dict_except[FE_OVERFLOW] = "上溢";
    dict_except[FE_UNDERFLOW] = "下溢";

    // 舍入方向
    dict_round[FE_DOWNWARD] = "向下舍入";
    dict_round[FE_TONEAREST] = "最近舍入";
    dict_round[FE_TOWARDZERO] = "向零舍入";
    dict_round[FE_UPWARD] = "向上舍入";
}

// 展示 PID PGID SID
void show_pid_pgid_sid(pid_t pid) {
    std::string msg;
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

// 测试 PGID
void test_pgid(pid_t pid, pid_t pgid) {
    log();
    show_pid_pgid_sid(pid);

    std::string msg;
    msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show_pid_pgid_sid(pid);
    log();
}

// 测试 SID
void test_sid() {
    log();
    show_pid_pgid_sid(getpid());

    std::string msg = "新建会话";
    if (setsid() < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    show_pid_pgid_sid(getpid());
    log();
}

// 测试 浮点数
class Double {
   public:
    union Node {
        double x;
        uint64_t y;
    };

    double data;
    std::string bit;
    std::string bit_by_test;
    std::string bit_by_cs;
    std::string bit_by_show;
    std::string double_by_hand;
    std::string double_by_cs;

    Double(double x) {
        init();

        data = x;

        Node node;
        node.x = x;
        bit = std::bitset<64>(node.y).to_string();
        bit_by_test = bit;
        bit_by_cs = bit;
        bit_by_show = to_bit();
        double_by_hand = to_double_hand();
        double_by_cs = to_double_cs();
    }

    Double(const std::string& str) {
        init();

        bit = trim(str);
        if ((int)bit.size() < 64) {
            // 往后补0
            bit += std::string(64 - (int)bit.size(), '0');
        }

        bit_by_test = bit;
        bit_by_show = to_bit();
        double_by_hand = to_double_hand();

        Node node;
        std::stringstream tmp(double_by_hand);
        tmp >> node.x;

        data = node.x;

        bit = std::bitset<64>(node.y).to_string();
        bit_by_cs = bit;
        double_by_cs = to_double_cs();
    }

   private:
    std::map<int, std::string> dict_pow;  // 存储 2 的幂次
                                          // 负幂次只存储小数点后的部分

    void init() {
        // 2 的幂次
        int n = 2000;
        std::string str;

        str = "5";
        for (int i = -1; i >= -n; --i) {
            dict_pow[i] = str;

            str = "";
            int sum = 0;
            for (char ch : dict_pow[i]) {
                sum = sum * 10 + (ch - '0');
                str += std::string(1, sum / 2 + '0');
                sum %= 2;
            }
            if (sum != 0) str += "5";
        }

        str = "1";
        for (int i = 0; i <= n; ++i) {
            dict_pow[i] = str;

            str = "";
            int sum = 0;
            for (int j = (int)dict_pow[i].size() - 1; j >= 0; --j) {
                sum += (dict_pow[i][j] - '0') * 2;
                str = std::string(1, sum % 10 + '0') + str;
                sum /= 10;
            }
            if (sum != 0) str = std::string(1, sum + '0') + str;
        }
    }

    // 移除所有的 空字符
    std::string trim(const std::string& str) {
        std::string result;
        for (char ch : str) {
            if (!std::isspace(ch)) {
                result += ch;
            }
        }
        return result;
    }

    // 浮点数 符号位 阶码 尾码
    std::string to_bit() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12, 52);

        std::bitset<11> e_bit(e_str);
        std::bitset<52> f_bit(f_str);

        int e_int = e_bit.to_ulong();

        if (e_bit.none() && not f_bit.none()) {
            // 非规约数字: 阶码都为 0, 尾码不都为 0
            e_int -= 1022;
        } else if (not e_bit.all() && not e_bit.none()) {
            // 规约数字: 阶码不都为 0, 也不都为 1
            e_int -= 1023;
        } else {
            // 还剩 0 无穷 非数字
        }

        std::string e_int_string = std::to_string(e_int);
        e_int_string =
            std::string(5 - (int)e_int_string.size(), ' ') + e_int_string;

        std::string result;
        result += s_str + " ";
        result += e_str + "(" + e_int_string + ") ";
        result += f_str + " ";
        result += bit.substr(64);  // 多余 64 位的部分
        return result;
    }

    // 计算机内部存储的浮点数(字符串)
    std::string to_double_cs() {
        Node node;
        node.y = std::bitset<64>(bit.substr(0, 64)).to_ulong();

        data = node.x;

        std::stringstream tmp;
        // 不使用科学计数数
        tmp << std::setprecision(2000) << std::fixed << node.x;  // 最多 1074 位
        std::string result = tmp.str();
        size_t index = result.find_last_not_of('0');

        if (result[index] == '.') {
            --index;
        }
        return result.substr(0, index + 1);
    }

    // 两个数的加法(十进制)
    // type 为 0 表示整数加法 1 表示小数加法
    std::string add(std::string x, std::string y, int type = 0) {
        if (x.size() > y.size()) {
            swap(x, y);
        }
        if (type == 0)
            x = std::string(y.size() - x.size(), '0') + x;  // 整数
        else
            x = x + std::string(y.size() - x.size(), '0');  // 小数

        int sum = 0;
        std::string z;

        for (int i = (int)x.size() - 1; i >= 0; --i) {
            sum += (x[i] - '0') + (y[i] - '0');
            z = std::string(1, '0' + sum % 10) + z;
            sum /= 10;
        }
        if (sum != 0) {
            z = std::string(1, '0' + sum) + z;
        }
        return z;
    }

    // 二进制的浮点数转化为 十进制,
    // str_int --> 整数部分, str_dec --> 小数部分
    std::string to_double_hand(const std::string& str_int,
                               const std::string& str_dec) {
        std::string result_int = "0";
        for (int i = 0; i < (int)str_int.size(); ++i)
            if (str_int[i] == '1')
                result_int = add(result_int, dict_pow[str_int.size() - 1 - i]);

        std::string result_dec;
        for (int i = 0; i < (int)str_dec.size(); ++i)
            if (str_dec[i] == '1')
                result_dec = add(result_dec, dict_pow[-1 - i], 1);

        if (result_dec.empty())
            return result_int;
        else
            return result_int + "." + result_dec;
    }

    // 手动计算浮点数(字符串)
    std::string to_double_hand() {
        std::string s_str = bit.substr(0, 1);
        std::string e_str = bit.substr(1, 11);
        std::string f_str = bit.substr(12);

        std::bitset<11> e_bit(e_str);
        int e_int = e_bit.to_ulong();

        std::bitset<52> f_bit(f_str);  // 只用于判断 0 无穷 非数字

        // 阶码都为 1, 尾码都为 0
        if (e_bit.all() && f_bit.none()) {
            return s_str == "1" ? "负无穷" : "正无穷";
        }

        // 阶码都为 1, 尾码不都为 0
        if (e_bit.all() && not f_bit.none()) {
            return "非数字";
        }

        // 阶码都为 0, 尾码都为 0
        if (e_bit.none() && f_bit.none()) {
            return s_str == "1" ? "负零" : "正零";
        }

        std::string str_int;          // 尾码的整数部分
        std::string str_dec = f_str;  // 尾码的小数部分

        if (e_bit.none() && not f_bit.none()) {
            // 阶码都为 0, 尾码不都为 0
            // 非规约数字
            f_str = "0." + f_str;
            e_int -= 1022;
        } else {
            // 阶码不都为 0, 也不都为 1
            // 规约数字
            f_str = "1." + f_str;
            e_int -= 1023;
            str_int = "1";
        }

        // 处理 阶码 的移位
        if (e_int > 0) {
            if ((int)str_dec.size() < e_int)
                str_dec += std::string(e_int - str_dec.size(), 0);

            str_int += str_dec.substr(0, e_int);
            str_dec = str_dec.substr(e_int);
        } else if (e_int < 0) {
            if (!str_int.empty())
                str_dec = std::string(-e_int - 1, '0') + str_int + str_dec;
            else
                str_dec = std::string(-e_int, '0') + str_dec;
            str_int = "";
        }
        std::string result = to_double_hand(str_int, str_dec);
        if (s_str == "1") {
            result = "-" + result;
        }
        return result;
    }
};
