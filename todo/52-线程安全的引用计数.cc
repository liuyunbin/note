
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

class Counter {
public:
    Counter() : value_(0) {
    }

    Counter(const Counter& rhs) {
        std::lock_guard<std::mutex> lock(rhs.mutex_);
        value_ = rhs.value_;
    }

    void swap(Counter& rhs) noexcept {
        if (this == &rhs)
            return;
#if __cplusplus >= 201703L
        std::scoped_lock lock(mutex_, rhs.mutex_);
#elif __cplusplus >= 201103L
        std::lock(mutex_, rhs.mutex_);
        std::lock_guard<std::mutex> lhs_lock(mutex_, std::adopt_lock);
        std::lock_guard<std::mutex> rhs_lock(rhs.mutex_, std::adopt_lock);
#else
        std::cerr << "Counter need c++11 or later" << std::endl;
        std::exit(EXIT_FAILURE);
#endif
        using std::swap;
        swap(value_, rhs.value_);
    }

    Counter& operator=(const Counter& rhs) {
        if (this == &rhs)
            return *this;
        auto temp(rhs);
        swap(temp);
        return *this;
    }

    std::size_t get_value() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }

    Counter& operator++() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++value_;
        return *this;
    }

    Counter operator++(int) {
        auto temp = *this;
        ++*this;
        return temp;
    }

private:
    std::size_t        value_;
    mutable std::mutex mutex_;
};

void swap(Counter& lhs, Counter& rhs) noexcept {
    lhs.swap(rhs);
}

void function(Counter& count) {
    for (int i = 0; i != 100; ++i)
        ++count;
}

int main() {
    Counter count;

    std::thread thread1(function, std::ref(count));
    std::thread thread2(function, std::ref(count));

    thread1.join();
    thread2.join();

    std::cout << count.get_value() << std::endl;

    return 0;
}
