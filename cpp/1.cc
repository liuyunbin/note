
#include "log.h"

int main() {
    log();
    log("测试缓冲");
    log();

    // 全缓存
    // * 程序结束
    // * 缓冲区满
    // * 手动刷新缓存
    // * 涉及磁盘文件一般是全缓存
    // 行缓冲
    // * 程序结束
    // * 缓冲区满
    // * 遇到文件结束符
    // * 手动刷新缓存
    // * 涉及终端一般是行缓存
    // 无缓冲
    // * 涉及终端输出错误是无缓存
    std::cout << std::endl << "测试  自动刷新缓冲" << std::endl;
    std::cout << std::unitbuf;  // 每次调用都自动刷新缓冲区
    std::cout << "暂停5s...";
    sleep(5);
    std::cout << "完成" << std::endl;

    std::cout << std::endl << "测试不自动刷新缓冲" << std::endl;
    std::cout << std::nounitbuf;  // 不自动刷新缓冲区
    std::cout << "暂停5s...";
    sleep(5);
    std::cout << "完成" << std::endl;

    log();
    log("主进程正常退出");
    log();
    return 0;
}
