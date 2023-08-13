
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "lshell.h"

std::string mode_to_str(int mode) {
    std::string result = "----------";

    // 文件类型
    if (S_ISDIR(mode))
        result[0] = 'd';  // 目录
    if (S_ISCHR(mode))
        result[0] = 'c';  // 设备文件
    if (S_ISBLK(mode))
        result[0] = 'b';  // 块文件

    // 用户权限
    if (mode & S_IRUSR)
        result[1] = 'r';
    if (mode & S_IWUSR)
        result[2] = 'w';
    if (mode & S_IXUSR)
        result[3] = 'x';

    // 组权限
    if (mode & S_IRGRP)
        result[4] = 'r';
    if (mode & S_IWGRP)
        result[5] = 'w';
    if (mode & S_IXGRP)
        result[6] = 'x';

    // 其他人权限
    if (mode & S_IROTH)
        result[7] = 'r';
    if (mode & S_IWOTH)
        result[8] = 'w';
    if (mode & S_IXOTH)
        result[9] = 'x';
    return result;
}

void show_file_info(const std::string &file_name, const struct stat *stat_ptr) {
    printf("%s", mode_to_str(stat_ptr->st_mode).data());
    printf("%4d ", (int)stat_ptr->st_nlink);
    printf("%-8s ", uid_to_name(stat_ptr->st_uid).data());
    printf("%-8s ", gid_to_name(stat_ptr->st_gid).data());
    printf("%8ld ", (long)stat_ptr->st_size);
    printf("%.12s ", 4 + ctime(&stat_ptr->st_mtime));
    printf("%s\n", file_name.data());
}

int do_stat(const std::string &file_name, int dir_fd) {
    struct stat info;

    if (fstatat(dir_fd, file_name.data(), &info, 0) == -1) {
        perror(file_name.data());
        return -1;
    }
    show_file_info(file_name, &info);
    return 0;
}

int is_directory(const std::string &name) {
    struct stat info;
    if (stat(name.data(), &info) == -1)
        return -1;
    if (S_ISDIR(info.st_mode))
        return 1;
    else
        return 0;
}

int do_ls(cmd_t &cmd) {
    std::string name;
    if (cmd.cmd_vec.size() == 1)
        name = ".";
    else
        name = cmd.cmd_vec[1];
    int ret = is_directory(name);
    if (ret == -1)
        return -1;
    if (ret == 1) {  // 目录
        DIR *dir_ptr = opendir(name.data());
        if (dir_ptr == NULL) {
            // 无法打开目录
            perror(name.data());
            return -1;
        }
        struct dirent *dirent_ptr;
        while ((dirent_ptr = readdir(dir_ptr)) != NULL)
            if (do_stat(dirent_ptr->d_name, dirfd(dir_ptr)) == -1)
                return -1;
        closedir(dir_ptr);
        return 0;
    } else {  // 普通文件
        return do_stat(name, AT_FDCWD);
    }
}
