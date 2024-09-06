
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

using namespace std::chrono_literals;

class ObserverPool;

class Observer : public std::enable_shared_from_this<Observer> {
public:
    Observer(ObserverPool* s);
    ~Observer();

    void add_observer_pool();
    // 此步可能调用 add_observer_pool
    void update();

private:
    ObserverPool* observer_pool_;
};

class ObserverPool {
public:
    ObserverPool();
    ~ObserverPool();

    void add_observer(const std::weak_ptr<Observer>& x);
    void notifyObservers();

private:
    std::vector<std::weak_ptr<Observer>> pool_;
    std::mutex                           mutex_;
};

Observer::Observer(ObserverPool* s) {
    std::cout << "observer init" << std::endl;
    observer_pool_ = s;
}

Observer::~Observer() {
    std::cout << "observer erase: " << this << std::endl;
}

void Observer::add_observer_pool() {
    std::cout << "observer add..." << std::endl;
    observer_pool_->add_observer(shared_from_this());
}

void Observer::update() {
    std::cout << "observer update, addr: " << this << std::endl;
}

ObserverPool::ObserverPool() {
    std::cout << "observerPool init" << std::endl;
}

ObserverPool::~ObserverPool() {
    std::cout << "observerPool erase" << std::endl;
}

void ObserverPool::add_observer(const std::weak_ptr<Observer>& x) {
    std::lock_guard<std::mutex> guard(mutex_);
    pool_.push_back(x);
}

void ObserverPool::notifyObservers() {
    std::lock_guard<std::mutex> guard(mutex_);
    std::cout << "observerPool notifyObservers..." << std::endl;
    for (auto it = std::begin(pool_); it != std::end(pool_);) {
        std::this_thread::sleep_for(1s);  // 模拟耗时
        std::shared_ptr<Observer> obj(it->lock());
        if (obj) {
            obj->update();
            ++it;
        } else {
            std::cout << "In notifyObservers, observer had been erase."
                      << std::endl;
            it = pool_.erase(it);
        }
    }
}

ObserverPool* observer_pool;

int main() {
    observer_pool = new ObserverPool;

    std::thread t1([]() {
        std::this_thread::sleep_for(1s);
        observer_pool->notifyObservers();
    });

    std::thread t2([]() {
        {
            auto observer1 = std::make_shared<Observer>(observer_pool);
            auto observer2 = std::make_shared<Observer>(observer_pool);
            auto observer3 = std::make_shared<Observer>(observer_pool);
            auto observer4 = std::make_shared<Observer>(observer_pool);
            auto observer5 = std::make_shared<Observer>(observer_pool);

            observer1->add_observer_pool();
            observer2->add_observer_pool();
            observer3->add_observer_pool();
            observer4->add_observer_pool();
            observer5->add_observer_pool();
        }

        std::this_thread::sleep_for(2s);
    });

    t1.join();
    t2.join();
    return 0;
}
