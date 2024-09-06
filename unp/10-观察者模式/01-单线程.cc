
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

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
    std::cout << "observer erase" << std::endl;
}

void Observer::add_observer_pool() {
    std::cout << "observer add" << std::endl;
    observer_pool_->add_observer(this);
}

void Observer::del_observer_pool() {
    std::cout << "observer del" << std::endl;
    observer_pool_->del_observer(this);
}

void Observer::update() {
    std::cout << "observer update" << std::endl;
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
    std::cout << "observerPool notifyObservers" << std::endl;
    for (auto val : pool_) {
        val->update();
    }
}

int main() {
    ObserverPool* observer_pool = new ObserverPool;
    Observer*     observer      = new Observer(observer_pool);
    observer->add_observer_pool();
    observer_pool->notifyObservers();
    observer->del_observer_pool();
    observer_pool->notifyObservers();
    return 0;
}
