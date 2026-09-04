
#include <TinyLog/log_stream.h>
#include <TinyLog/logger.h>
#include <TinyLog/logging.h>
#include <TinyLog/logging_async.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

using namespace TinyLog;

int bytes = 0;

std::FILE* p = std::fopen("/dev/null", "w");

void output(const char* st, int n) {
    bytes += n;
    std::fwrite(st, 1, n, p);
}

int main() {
    Logger::setLogOutput(output);

    int N = 1024 * 1024;
    char data[] = "1234567890";
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i != N; ++i) LOG_ERROR << data << data;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ti =
        std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    double seconds = ti.count();
    bytes /= (1024 * 1024);
    std::cerr << seconds << " seconds\t" << bytes << " MB\t"
              << (bytes / seconds) << "MiB/s" << std::endl;
    return 0;
}
