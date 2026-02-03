
#include <iostream>
#include <pthread.h>
#include <unistd.h> // for usleep

class singleton {
public:
    static singleton* instance() {
        if (ptr == NULL) {                   // 第一次检查
            pthread_mutex_lock(&mu);
            if (ptr == NULL) {               // 第二次检查
                // 模拟构造耗时
                usleep(1000); // 1ms
                ptr = new singleton();
            }
            pthread_mutex_unlock(&mu);
        }
        return ptr;
    }

    int value; // 构造完成前可能是随机值

protected:
    singleton() {
        // 模拟耗时构造，让问题更容易出现
        usleep(5000); // 5ms
        value = 42;
    }

    singleton(const singleton&) {}
    singleton& operator=(const singleton&) { return *this; }

private:
    static singleton* ptr;
    static pthread_mutex_t mu;
};

singleton* singleton::ptr = NULL;
pthread_mutex_t singleton::mu = PTHREAD_MUTEX_INITIALIZER;

volatile bool printed = false;

void* thread_func(void* arg) {
    int id = *(int*)arg;
    singleton* s = singleton::instance();

    // 检测未初始化值，只打印一次
    if (s->value != 42 && !printed) {
        printed = true;
        std::cout << "Thread " << id << " saw uninitialized value: " << s->value << "\n";
    }
    return NULL;
}

int main() {
    const int THREADS = 200;
    pthread_t threads[THREADS];
    int ids[THREADS];

    for (int i = 0; i < THREADS; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    for (int i = 0; i < THREADS; ++i)
        pthread_join(threads[i], NULL);

    std::cout << "Done\n";
    return 0;
}

