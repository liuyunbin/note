
#include "cp.h"

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

#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#define BUF_SIZE 4096

int is_directory(const std::string &name) {
  struct stat info;
  if (stat(name.data(), &info) == -1)
    return -1;
  if (S_ISDIR(info.st_mode))
    return 1;
  else
    return 0;
}

std::string get_absolute_name(const char *name) {
  char buf[BUF_SIZE] = "";

  if (name[0] != '/') {
    // 获取绝对路径
    if (getcwd(buf, sizeof(buf)) == NULL) {
      perror("");
      exit(EXIT_FAILURE);
    }
    strcat(buf, "/");
  }

  strcat(buf, name); // 此步可能溢出，只为测试使用

  std::vector<std::string> ve;

  char *p = strtok(buf, "/");
  while (p != NULL) {
    if (strcmp(p, ".") == 0) {
      //空
    } else {
      if (strcmp(p, "..") == 0) {
        if (!ve.empty())
          ve.pop_back();
      } else {
        ve.push_back(p);
      }
    }
    p = strtok(NULL, "/");
  }

  if (ve.empty())
    return "/";

  std::string result;

  for (const auto &data : ve)
    result = result + "/" + data;

  size_t len = strlen(name);
  if (len > 0 && name[len - 1] == '/')
    result += "/";
  return result;
}

bool argument_is_same(const char *from, const char *to) {
  return get_absolute_name(from) == get_absolute_name(to);
}

const char *get_file_name(const char *name) {
  const char *p = strrchr(name, '/');
  if (p == NULL) {
    return name;
  } else {
    return p + 1;
  }
}

void cp_file(const std::string &from, const std::string &to) {
  int in_fd = open(from.data(), O_RDONLY);
  if (in_fd == -1) {
    perror(from.data());
    exit(EXIT_FAILURE);
  }

  int out_fd = open(to.data(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (out_fd == -1) {
    perror(to.data());
    exit(EXIT_FAILURE);
  }

  char buf[BUF_SIZE];
  int buf_len;

  while ((buf_len = read(in_fd, buf, sizeof(buf))) > 0) {
    if (write(out_fd, buf, buf_len) != buf_len) {
      perror("");
      exit(EXIT_FAILURE);
    }
  }

  close(in_fd);
  close(out_fd);
}

void cp_directory(const std::string &from, const std::string &to) {
  std::queue<std::pair<std::string, std::string>> qu;
  qu.push(std::make_pair(from, to));

  for (;;) {
    if (qu.empty())
      break;
    auto data = qu.front();
    qu.pop();

    if (is_directory(data.second) == 0) {
      // data.second 存在 且 是 文件，失败
      printf("无法拷贝从目录到文件 且 文件存在的情况\n");
      exit(EXIT_FAILURE);
    }

    if (is_directory(data.second) == -1) {
      // data.second 不存在
      if (mkdir(data.second.data(), 0755) == -1) {
        perror("");
        exit(EXIT_FAILURE);
      }
    }

    DIR *dir_ptr = opendir(data.first.data());
    if (dir_ptr == NULL) {
      perror(data.first.data());
      exit(EXIT_FAILURE);
    }

    struct dirent *dirent_ptr;
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
      if (is_directory(data.first + "/" + dirent_ptr->d_name) == 0) {
        // 文件
        cp_file(data.first + "/" + dirent_ptr->d_name,
                data.second + "/" + dirent_ptr->d_name);
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
}

// 拷贝 文件 --> 文件，且 文件存在
void cp_file_to_file(const char *from, const char *to) { cp_file(from, to); }

// 拷贝 文件 --> 目录，且 目录存在
void cp_file_to_directory(const char *from, const char *to) {
  cp_file(from, std::string(to) + "/" + get_file_name(from));
}

// 拷贝 文件 --> 文件 或 目录，且 文件 或 目录 不存在
void cp_file_to_file_or_directory(const char *from, const char *to) {
  size_t len = strlen(to);

  if (len > 0 && to[len - 1] == '/') {
    // to 是目录，失败
    printf("无法拷贝 文件 --> 目录，且 目录不存在的情况\n");
    exit(EXIT_FAILURE);
  } else {
    // to 是文件
    cp_file(from, to);
  }
}

// 拷贝 目录 --> 文件，且 文件存在，直接失败
void cp_directory_to_file(const char *from, const char *to) {
  printf("无法拷贝 目录 --> 文件，且 文件存在的情况\n");
  exit(EXIT_FAILURE);
}

// 拷贝 目录 --> 目录，且 目录存在
void cp_directory_to_directory(const char *from, const char *to) {
  char buf[BUF_SIZE];

  strcpy(buf, from); // 此处可能会溢出，仅测试

  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '/')
    buf[len - 1] = '\0';

  char *p = strrchr(buf, '/');
  if (p == NULL)
    p = buf;
  else
    p = p + 1;

  cp_directory(from, std::string(to) + "/" + p);
}

// 拷贝 目录 --> 文件 或 目录，且 文件 或 目录 不存在
void cp_directory_to_file_or_directory(const char *from, const char *to) {
  cp_directory(from, to);
}

