
#include "ls.h"

#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

const char *uid_to_name(uid_t uid) {
  struct passwd *pw_ptr = getpwuid(uid);

  if (pw_ptr == NULL) { // 无该 uid 对应的用户
    static char num_str[10];
    sprintf(num_str, "%d", uid);
    return num_str;
  } else {
    return pw_ptr->pw_name;
  }
}

const char *gid_to_name(gid_t gid) {
  struct group *grp_ptr = getgrgid(gid);

  if (grp_ptr == NULL) { // 无该 gid 对应的组
    static char num_str[10];
    sprintf(num_str, "%d", gid);
    return num_str;
  } else {
    return grp_ptr->gr_name;
  }
}

void mode_to_letters(int mode, char *str) {
  strcpy(str, "----------");

  // 文件类型
  if (S_ISDIR(mode))
    str[0] = 'd'; // 目录
  if (S_ISCHR(mode))
    str[0] = 'c'; // 设备文件
  if (S_ISBLK(mode))
    str[0] = 'b'; // 块文件

  // 用户权限
  if (mode & S_IRUSR)
    str[1] = 'r';
  if (mode & S_IWUSR)
    str[2] = 'w';
  if (mode & S_IXUSR)
    str[3] = 'x';

  // 组权限
  if (mode & S_IRGRP)
    str[4] = 'r';
  if (mode & S_IWGRP)
    str[5] = 'w';
  if (mode & S_IXGRP)
    str[6] = 'x';

  // 其他人权限
  if (mode & S_IROTH)
    str[7] = 'r';
  if (mode & S_IWOTH)
    str[8] = 'w';
  if (mode & S_IXOTH)
    str[9] = 'x';
}

void show_file_info(const char *file_name, const struct stat *stat_ptr) {
  char mode_str[11];
  mode_to_letters(stat_ptr->st_mode, mode_str);

  printf("%s", mode_str);
  printf("%4d ", (int)stat_ptr->st_nlink);
  printf("%-8s ", uid_to_name(stat_ptr->st_uid));
  printf("%-8s ", gid_to_name(stat_ptr->st_gid));
  printf("%8ld ", (long)stat_ptr->st_size);
  printf("%.12s ", 4 + ctime(&stat_ptr->st_mtime));
  printf("%s\n", file_name);
}

void do_stat(const char *file_name, int dir_fd) {
  struct stat info;

  if (fstatat(dir_fd, file_name, &info, 0) == -1) {
    perror(file_name);
    exit(EXIT_FAILURE);
  }
  show_file_info(file_name, &info);
}

bool is_directory(const char *name) {
  struct stat info;
  if (stat(name, &info) == -1) {
    perror(name);
    exit(EXIT_FAILURE);
  }
  if (S_ISDIR(info.st_mode))
    return true;
  else
    return false;
}

void ls(const char *name) {
  if (is_directory(name)) { // 目录
    DIR *dir_ptr = opendir(name);
    if (dir_ptr == NULL) { // 无法打开目录
      perror(name);
      exit(EXIT_FAILURE);
    }
    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL)
      do_stat(dirent_ptr->d_name, dirfd(dir_ptr));
    closedir(dir_ptr);
  } else { // 普通文件
    do_stat(name, AT_FDCWD);
  }
}

