
template <typename T>
std::string format(const char* fmt, T data) {
    char buf[2048];
    snprintf(buf, sizeof(buf), fmt, data);
    return buf;
}

double to_double(const std::string& str) {
    double data;
    sscanf(str.data(), "%lf", &data);
    return data;
}

// 存储浮点数异常
std::map<int, std::string> dict_except{
    {FE_DIVBYZERO, "除以0"        },
    {FE_INEXACT,   "结果不准确"},
    {FE_INVALID,   "参数非法"   },
    {FE_OVERFLOW,  "上溢"         },
    {FE_UNDERFLOW, "下溢"         }
};

//存储舍入模式
std::map<int, std::string> dict_round{
    {FE_DOWNWARD,   "向下舍入"},
    {FE_TONEAREST,  "最近舍入"},
    {FE_TOWARDZERO, "向零舍入"},
    {FE_UPWARD,     "向上舍入"}
};

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
}

// 测试 浮点数
class Double {
  public:
    union Node {
        double   x;
        uint64_t y;
    };

    double      data;
    std::string bit;
    std::string bit_by_test;
    std::string bit_by_cs;
    std::string bit_by_show;
    std::string double_by_hand;
    std::string double_by_cs;

    Double(double x) {
        init();

        Node node;
        node.x         = x;
        bit            = std::bitset<64>(node.y).to_string();
        bit_by_test    = bit;
        bit_by_cs      = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();
        double_by_cs   = to_double_cs();
        data           = x;
    }

    Double(const std::string& str) {
        init();

        bit = trim(str);
        if ((int)bit.size() < 64) {
            // 往后补0
            bit += std::string(64 - (int)bit.size(), '0');
        }

        bit_by_test    = bit;
        bit_by_show    = to_bit();
        double_by_hand = to_double_hand();

        Node node;
        node.x = to_double(double_by_hand);

        bit          = std::bitset<64>(node.y).to_string();
        bit_by_cs    = bit;
        double_by_cs = to_double_cs();
        data         = node.x;
    }

  private:
    // 存储 2 的幂次, 负幂次只存储小数点后的部分
    std::map<int, std::string> dict_pow;

    void init() {
        // 2 的幂次
        int         n = 2000;
        std::string str;

        str = "5";
        for (int i = -1; i >= -n; --i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (char ch : dict_pow[i]) {
                sum = sum * 10 + (ch - '0');
                str += std::string(1, sum / 2 + '0');
                sum %= 2;
            }
            if (sum != 0)
                str += "5";
        }

        str = "1";
        for (int i = 0; i <= n; ++i) {
            dict_pow[i] = str;

            str     = "";
            int sum = 0;
            for (int j = (int)dict_pow[i].size() - 1; j >= 0; --j) {
                sum += (dict_pow[i][j] - '0') * 2;
                str = std::string(1, sum % 10 + '0') + str;
                sum /= 10;
            }
            if (sum != 0)
                str = std::string(1, sum + '0') + str;
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

        std::string e_int_string = to_string(e_int);
        e_int_string =
            std::string(5 - (int)e_int_string.size(), ' ') + e_int_string;

        std::string result;
        return to_string(s_str,
                         " ",
                         e_str,
                         "(",
                         e_int_string,
                         ") ",
                         f_str,
                         " ",
                         bit.substr(64));  // 多余 64 位的部分
    }

    // 计算机内部存储的浮点数(字符串)
    std::string to_double_cs() {
        Node node;
        node.y             = std::bitset<64>(bit.substr(0, 64)).to_ulong();
        std::string result = format("%.2000f", node.x);  // 最多 1074 位
        size_t      index  = result.find_last_not_of('0');

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

        int         sum = 0;
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
        int             e_int = e_bit.to_ulong();

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

template <typename T>
void test_double(const std::string& name, T data) {
    Double d(data);

    log();
    log("        测试类型: ", name);
    log("    测试的二进制: ", d.bit_by_test);
    log("    存储的二进制: ", d.bit_by_cs);
    log("          手动值: ", d.double_by_hand);
    log("          存储值: ", d.double_by_cs);
    log("    保留两位小数: ", format("%.2lf", d.data));
}
