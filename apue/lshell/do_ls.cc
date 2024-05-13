
#include "lshell.h"

static bool show_detail = false;

static int show_file_info(const char* name, int dir_fd) {
    if (name[0] == '.' && name[1] == '\0')
        return 0;  // 跳过 "."
    if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
        return 0;  // 跳过 ".."

    struct stat info;

    if (fstatat(dir_fd, name, &info, 0) == -1) {
        perror("ls");
        return -1;
    }

    if (not show_detail) {
        printf("%s\n", name);
        return 0;
    }

    // 文件类型
    mode_t      mode      = info.st_mode;
    std::string file_type = "----------";
    if (S_ISDIR(mode))
        file_type[0] = 'd';  // 目录
    if (S_ISCHR(mode))
        file_type[0] = 'c';  // 设备文件
    if (S_ISBLK(mode))
        file_type[0] = 'b';  // 块文件

    // 用户权限
    if (mode & S_IRUSR)
        file_type[1] = 'r';
    if (mode & S_IWUSR)
        file_type[2] = 'w';
    if (mode & S_IXUSR)
        file_type[3] = 'x';

    // 组权限
    if (mode & S_IRGRP)
        file_type[4] = 'r';
    if (mode & S_IWGRP)
        file_type[5] = 'w';
    if (mode & S_IXGRP)
        file_type[6] = 'x';

    // 其他人权限
    if (mode & S_IROTH)
        file_type[7] = 'r';
    if (mode & S_IWOTH)
        file_type[8] = 'w';
    if (mode & S_IXOTH)
        file_type[9] = 'x';
    printf("%s", file_type.data());

    // 硬链接数
    std::string st_nlink = std::to_string(info.st_nlink);
    printf(" %3s", st_nlink.data());

    // 用户名称
    uid_t          uid = info.st_uid;
    std::string    user_name;
    struct passwd* pw_ptr = getpwuid(uid);
    if (pw_ptr != NULL)
        user_name = std::string(pw_ptr->pw_name);
    else
        user_name = std::to_string(uid);
    printf(" %8s", user_name.data());

    // 组名称
    uid_t         gid = info.st_gid;
    std::string   group_name;
    struct group* grp_ptr = getgrgid(gid);
    if (grp_ptr != NULL)
        group_name = std::string(grp_ptr->gr_name);
    else
        group_name = std::to_string(gid);
    printf(" %8s", group_name.data());

    // 文件大小
    std::string st_size = std::to_string(info.st_size);
    printf(" %8s", st_size.data());

    // 文件内容修改时间
    struct tm* t = localtime(&info.st_mtime);
    char       buf[1024];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", t);
    printf(" %s", buf);

    // 文件名称
    printf(" %s\n", name);

    return 0;
}

static int list_file(const char* name) {
    return show_file_info(name, AT_FDCWD);
}

static int list_directory(const char* name) {
    DIR* dir_ptr = opendir(name);
    if (dir_ptr == NULL) {
        // 无法打开目录
        perror("ls");
        return -1;
    }
    struct dirent* dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL)
        if (show_file_info(dirent_ptr->d_name, dirfd(dir_ptr)) == -1)
            return -1;
    closedir(dir_ptr);
    return 0;
}

static int list(const char* name) {
    struct stat info;

    if (stat(name, &info) == -1) {
        perror("ls");
        return -1;
    }

    if (S_ISDIR(info.st_mode))
        return list_directory(name);  // 目录
    else
        return list_file(name);  // 文件
}

static int usage() {
    fputs("usage: ls  [OPTION]... [FILE]... \n", stdout);
    fputs("                                 \n", stdout);
    fputs("  -h    帮助信息                 \n", stdout);
    fputs("  -l    显示详细信息             \n", stdout);

    return 0;
}

int do_ls(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "hl")) != -1) {
        switch (opt) {
        case 'h':
            return usage();
            break;
        case 'l':
            show_detail = true;
            break;
        default:
            return -1;
        }
    }

    if (optind == argc)
        return list(".");
    for (int i = optind; i < argc; ++i) {
        if (optind + 1 < argc)
            printf("\n%s\n", argv[i]);
        if (list(argv[i]) == -1)
            return -1;
    }

    return 0;
}
