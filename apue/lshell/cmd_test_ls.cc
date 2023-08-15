
#include <dirent.h>     // opendir
#include <fcntl.h>      // fstatat
#include <sys/stat.h>   // fstatat
#include <sys/types.h>  // opendir
#include <unistd.h>     // getopt

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

int show_file_info(const char* name, int dir_fd, bool show_detail) {
    struct stat info;

    if (fstatat(dir_fd, name, &info, 0) == -1) {
        perror(name);
        return -1;
    }

    if (show_detail) {
        printf("%s", mode_to_str(info.st_mode).data());
        printf("%4d ", (int)info.st_nlink);
        printf("%-8s ", uid_to_name(info.st_uid).data());
        printf("%-8s ", gid_to_name(info.st_gid).data());
        printf("%8ld ", (long)info.st_size);
        printf("%.12s ", 4 + ctime(&info.st_mtime));
    }
    printf("%s\n", name);

    return 0;
}

int list_file(const char* name, bool show_detail) {
    return show_file_info(name, AT_FDCWD, show_detail);
}

int list_directory(const char* name, bool show_detail) {
    DIR* dir_ptr = opendir(name);
    if (dir_ptr == NULL) {
        // 无法打开目录
        perror(name);
        return -1;
    }
    struct dirent* dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL)
        if (show_file_info(dirent_ptr->d_name, dirfd(dir_ptr), show_detail) ==
            -1)
            return -1;
    closedir(dir_ptr);
    return 0;
}

int list(const char* name, bool show_detail) {
    int ret = is_directory(name);
    if (ret == -1) {
        perror("ls");
        return -1;
    }
    if (ret == 1)  // 目录
        return list_directory(name, show_detail);
    return list_file(name, show_detail);
}

static int usage() {
    printf("ls    -------- list simple\n");
    printf("ls -l -------- list detail\n");
    printf("ls -h -------- help\n");
    return 0;
}

int do_ls(int argc, char* argv[]) {
    bool show_detail = false;

    int opt;
    while ((opt = getopt(argc, argv, "hl")) != -1) {
        switch (opt) {
        case 'h':
            return usage();
        case 'l':
            show_detail = true;
            break;
        default:
            return -1;
        }
    }

    if (optind == argc)
        return list(".", show_detail);
    for (int i = optind; i < argc; ++i)
        if (list(argv[i], show_detail) == -1)
            return -1;

    return 0;
}
