//
// ## cp A B 情况的分类：
// 1. A 不存在，直接失败
// 2. A 和 B 相同，直接退出
// 3. A 是文件，B 是文件 且 存在，直接拷贝即可
// 4. A 是文件，B 是目录 且 存在，获取 A 的文件名 name，相当于 cp A B/name
// 5. A 是文件，B 不存在，
//     * 若 B 是形如 X/ 的形式，直接失败
//     * 否则，直接拷贝即可
// 6. A 是目录，B 是文件 且 存在，直接失败
// 7. A 是目录，B 是目录 或 不存在
//     * 若 B 是目录，获取最后一个目录 dir，相当于 cp A B/dir
//     * 然后，将 源目录 和 目的目录 构成一个
//     pair，加入一个队列，依次取出队列中的元素 data，进行如下操作，直到队列为空
//         * 如果 data.second.data() 存在 且 是文件，直接失败
//         * 如果 data.second.data() 不存在，新建 此目录
//         * 打开目录 data.first.data()，依次遍历元素 v，
//             * 如果 v 是文件，直接拷贝，相当于 cp data.first.data()/v
//             data.second.data()/v
//             * 如果 v 是目录，将 make_pair(data.first.data()/v,
//             data.second.data()/v)  打入队列
//
// ## 例子：
// ```
// $ cp A  B    # 文件 --> 文件
// $ cp A  B/   # 文件 --> 目录
// $ cp A/ B/   # 目录 --> 目录
// ```
//
// ## 说明：
// 本程序未处理一半成功，一般失败的情况，即：遇到失败，直接退出，可能部分拷贝成功
//
#include "lshell.h"

int file_type(const std::string &name) {
    struct stat info;

    if (stat(name.data(), &info) == -1) {
        return -1;
    }

    if (S_ISDIR(info.st_mode))
        return 1;  // 目录
    else
        return 0;  // 文件
}

int get_absolute_name(const std::string &from, std::string &to) {
    std::string str;
    if (from.front() != '/') {
        // 获取绝对路径
        char *p = get_current_dir_name();
        str     = std::string(p) + "/" + from;
        free(p);
    } else {
        str = from;
    }
    std::vector<std::string> ve;
    size_t                   pos_begin = 0;
    while (pos_begin != std::string::npos) {
        size_t      pos_end = str.find("/", pos_begin);
        std::string current_str;
        if (pos_end == std::string::npos) {
            current_str = str.substr(pos_begin);
            pos_begin   = std::string::npos;
        } else {
            current_str = str.substr(pos_begin, pos_end - pos_begin);
            pos_begin   = pos_end + 1;
        }
        if (current_str == "" || current_str == ".") {
            // 跳过
        } else if (current_str == "..") {
            if (ve.empty()) {
                printf("invalid filename\n");
                return -1;
            }
            ve.pop_back();
        } else {
            ve.push_back(current_str);
        }
    }
    to.clear();
    for (auto &data : ve)
        to += "/" + data;
    return 0;
}

int argument_is_same(const std::string &left, const std::string &right) {
    std::string to_left;
    std::string to_right;
    if (get_absolute_name(left, to_left) == -1)
        return -1;
    if (get_absolute_name(right, to_right) == -1)
        return -1;
    return to_left == to_right ? 1 : 0;
}

std::string get_file_name(const std::string &name) {
    size_t pos = name.find_last_of('/');
    if (pos == std::string::npos)
        return name;
    return name.substr(pos + 1);
}

int cp_file(const std::string &from, const std::string &to) {
    int in_fd = open(from.data(), O_RDONLY);
    if (in_fd == -1) {
        perror("cp");
        return -1;
    }

    int out_fd = open(to.data(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd == -1) {
        perror("cp");
        return -1;
    }

    char buf[1024];

    for (;;) {
        int buf_len = read(in_fd, buf, sizeof(buf));
        if (buf_len < 0) {
            perror("cp");
            return -1;
        }
        if (buf_len == 0)
            break;
        write(out_fd, buf, buf_len);
    }

    close(in_fd);
    close(out_fd);
    return 0;
}

int cp_directory(const std::string &from, const std::string &to) {
    std::queue<std::pair<std::string, std::string>> qu;
    qu.push(std::make_pair(from, to));

    for (;;) {
        if (qu.empty())
            break;
        std::pair<std::string, std::string> data = qu.front();
        qu.pop();

        int type = file_type(data.second);
        if (type == 0) {
            // data.second 存在且是文件，失败
            printf("无法拷贝从目录到文件 且 文件存在的情况\n");
            return -1;
        }

        if (type == -1) {
            // data.second 不存在
            if (mkdir(data.second.data(), 0755) == -1) {
                perror("");
                return -1;
            }
        }

        // data.first 存在且是目录
        DIR *dir_ptr = opendir(data.first.data());
        if (dir_ptr == NULL) {
            perror("cp");
            return -1;
        }

        struct dirent *dirent_ptr;
        while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
            std::string name = data.first + "/" + dirent_ptr->d_name;
            int         type = file_type(name);
            if (type == -1)
                return -1;
            if (type == 0) {
                // 文件
                int ret = cp_file(name, data.second + "/" + dirent_ptr->d_name);
                if (ret == -1)
                    return -1;
            } else {
                // 目录
                if (strcmp(dirent_ptr->d_name, ".") == 0)
                    continue;
                if (strcmp(dirent_ptr->d_name, "..") == 0)
                    continue;
                qu.push(std::make_pair(data.first + "/" + dirent_ptr->d_name,
                                       data.second + "/" + dirent_ptr->d_name));
            }
        }

        closedir(dir_ptr);
    }
    return 0;
}

// 拷贝 文件 --> 文件，且 文件存在
int cp_file_to_file(const std::string &from, const std::string &to) {
    return cp_file(from, to);
}

// 拷贝 文件 --> 目录，且 目录存在
int cp_file_to_directory(const std::string &from, const std::string &to) {
    return cp_file(from, to + "/" + get_file_name(from));
}

// 拷贝 文件 --> 文件 或 目录，且 文件 或 目录 不存在
int cp_file_to_file_or_directory(const std::string &from,
                                 const std::string &to) {
    if (to.size() > 0 && to.back() == '/') {
        // to 是目录，失败
        printf("无法拷贝 文件 --> 目录，且 目录不存在的情况\n");
        return -1;
    } else {
        // to 是文件
        cp_file(from, to);
        return 0;
    }
}

// 拷贝 目录 --> 文件，且 文件存在，直接失败
int cp_directory_to_file(const std::string &from, const std::string &to) {
    printf("无法拷贝 目录 --> 文件，且 文件存在的情况\n");
    return -1;
}

// 拷贝 目录 --> 目录，且 目录存在
int cp_directory_to_directory(const std::string &from, const std::string &to) {
    std::string str = from;
    if (str.size() > 0 && str.back() == '/')
        str.pop_back();
    size_t pos = str.find_last_of('/');
    if (pos != std::string::npos)
        str = str.substr(pos + 1);
    return cp_directory(from, to + "/" + str);
}

// 拷贝 目录 --> 文件 或 目录，且 文件 或 目录 不存在
int cp_directory_to_file_or_directory(const std::string &from,
                                      const std::string &to) {
    return cp_directory(from, to);
}

int do_cp(int argc, char *argv[]) {
    if (argc != 3) {
        printf("please use: cp ... ...\n");
        return -1;
    }

    int file_type_argv_1 = file_type(argv[1]);
    int file_type_argv_2 = file_type(argv[2]);

    if (file_type_argv_1 == -1) {
        // 第一个文件参数不存在
        perror("cp");
        return -1;
    }

    int ret = argument_is_same(argv[1], argv[2]);
    if (ret == -1)
        return -1;
    if (ret == 1) {
        // 源文件或目录 和 目的文件或目录相同
        printf(" %s and %s is same\n", argv[1], argv[2]);
        return -1;
    }

    // 文件 --> 文件，且 文件存在
    if (file_type_argv_1 == 0 && file_type_argv_2 == 0)
        return cp_file_to_file(argv[1], argv[2]);

    // 文件 --> 目录，且 目录存在
    if (file_type_argv_1 == 0 && file_type_argv_2 == 1)
        return cp_file_to_directory(argv[1], argv[2]);

    // 文件 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
    if (file_type_argv_1 == 0 && file_type_argv_2 == -1)
        return cp_file_to_file_or_directory(argv[1], argv[2]);

    // 目录 --> 文件，且 文件存在
    if (file_type_argv_1 == 1 && file_type_argv_2 == 0)
        return cp_directory_to_file(argv[1], argv[2]);

    // 目录 --> 目录，且 目录存在
    if (file_type_argv_1 == 1 && file_type_argv_2 == 1)
        return cp_directory_to_directory(argv[1], argv[2]);

    // 目录 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
    if (file_type_argv_1 == 1 && file_type_argv_2 == -1)
        return cp_directory_to_file_or_directory(argv[1], argv[2]);

    return 0;
}
