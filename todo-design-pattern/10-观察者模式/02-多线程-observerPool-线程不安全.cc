
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

using namespace std::chrono_literals;

class ObserverPool;

class Observer {
public:
    Observer(ObserverPool* s);
    ~Observer();

    void add_observer_pool();
    void del_observer_pool();
    // 此步可能调用 add_observer_pool 或 del_observer_pool
    void update();

private:
    ObserverPool* observer_pool_;
};

class ObserverPool {
public:
    ObserverPool();
    ~ObserverPool();

    void add_observer(Observer* x);
    void del_observer(Observer* x);
    void notifyObservers();

private:
    std::vector<Observer*> pool_;
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
    observer_pool_->add_observer(this);
}

void Observer::del_observer_pool() {
    std::cout << "observer del..." << std::endl;
    observer_pool_->del_observer(this);
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

void ObserverPool::add_observer(Observer* x) {
    pool_.push_back(x);
}

void ObserverPool::del_observer(Observer* x) {
    for (auto it = pool_.begin(); it != pool_.end();) {
        if (*it == x) {
            it = pool_.erase(it);
        } else {
            ++it;
        }
    }
}

void ObserverPool::notifyObservers() {
    std::cout << "observerPool notifyObservers..." << std::endl;
    for (auto val : pool_) {
        std::this_thread::sleep_for(1s);  // 模拟耗时
        val->update();
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
        Observer* observer1 = new Observer(observer_pool);
        Observer* observer2 = new Observer(observer_pool);
        Observer* observer3 = new Observer(observer_pool);
        Observer* observer4 = new Observer(observer_pool);
        Observer* observer5 = new Observer(observer_pool);

        observer1->add_observer_pool();
        observer2->add_observer_pool();
        observer3->add_observer_pool();
        observer4->add_observer_pool();
        observer5->add_observer_pool();

        std::this_thread::sleep_for(2s);

        observer1->del_observer_pool();
        observer2->del_observer_pool();
        observer3->del_observer_pool();
        observer4->del_observer_pool();
        observer5->del_observer_pool();

        delete observer1;
        delete observer2;
        delete observer3;
        delete observer4;
        delete observer5;
    });

    t1.join();
    t2.join();
    return 0;
}
