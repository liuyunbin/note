
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <mutex>

bool                    g_terminate{};
std::mutex              g_mtx;
std::condition_variable g_cv;

int main() {
    using namespace std::chrono;
    auto time = milliseconds(500);

    while (true) {
        printf("---------------hello\n");
        std::unique_lock<std::mutex> lock(g_mtx);
        g_cv.wait_for(lock, time, [&] {
            return g_terminate;
        });

        printf("---------------ok\n");
    }

    return 0;
}
