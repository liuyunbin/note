
#include "cp.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("请使用：\n");
        printf("\t cp 源文件 目的文件 \n");
        printf("\t cp 源文件 目的目录 \n");
        printf("\t cp 源目录 目的目录 \n");
        return -1;
    }

    // argv[1] 不存在，直接失败
    if (is_directory(argv[1]) == -1) {
        perror(argv[1]);
        return -1;
    }

    // 源文件或目录 和 目的文件或目录相同
    if (argument_is_same(argv[1], argv[2])) {
        printf("源文件或目录 和 目的文件或目录相同\n");
        return 0;
    }

    // 文件 --> 文件，且 文件存在
    if (is_directory(argv[1]) == 0 && is_directory(argv[2]) == 0) {
        cp_file_to_file(argv[1], argv[2]);
        return 0;
    }

    // 文件 --> 目录，且 目录存在
    if (is_directory(argv[1]) == 0 && is_directory(argv[2]) == 1) {
        cp_file_to_directory(argv[1], argv[2]);
        return 0;
    }

    // 文件 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
    if (is_directory(argv[1]) == 0 && is_directory(argv[2]) == -1) {
        cp_file_to_file_or_directory(argv[1], argv[2]);
        return 0;
    }

    // 目录 --> 文件，且 文件存在
    if (is_directory(argv[1]) == 1 && is_directory(argv[2]) == 0) {
        cp_directory_to_file(argv[1], argv[2]);
        return 0;
    }

    // 目录 --> 目录，且 目录存在
    if (is_directory(argv[1]) == 1 && is_directory(argv[2]) == 1) {
        cp_directory_to_directory(argv[1], argv[2]);
        return 0;
    }

    // 目录 --> argv[2]，argv[2] 不存在，argv[2] 可能是文件 或 目录
    if (is_directory(argv[1]) == 1 && is_directory(argv[2]) == -1) {
        cp_directory_to_file_or_directory(argv[1], argv[2]);
        return 0;
    }

    return 0;
}
