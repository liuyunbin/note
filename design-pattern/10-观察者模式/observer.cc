
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <utility>

class ObserverPool;

class Observer : public std::enable_shared_from_this<Observer> {
   public:
    void add_to_observer_pool(const std::weak_ptr<ObserverPool>& s);

    void update() { std::cout << "observer update" << std::endl; }
};

class ObserverPool {
   public:
    void add_observer(const std::weak_ptr<Observer>& x) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::shared_ptr<Observer> obj(x.lock());
        if (obj)
            observer_pool_.push_back(x);
        else
            std::cout << "In add_observer, observer had been erase."
                      << std::endl;
    }

    void notifyObservers() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto it = std::begin(observer_pool_);
             it != std::end(observer_pool_);) {
            std::shared_ptr<Observer> obj(it->lock());
            if (obj) {
                obj->update();
                ++it;
            } else {
                std::cout << "In notifyObservers, observer had been erase."
                          << std::endl;
                it = observer_pool_.erase(it);
            }
        }
    }

   private:
    std::mutex mutex_;
    std::list<const std::weak_ptr<Observer>> observer_pool_;
};

void Observer::add_to_observer_pool(const std::weak_ptr<ObserverPool>& s) {
    std::shared_ptr<ObserverPool> obj(s.lock());
    if (obj) {
        obj->add_observer(shared_from_this());
    } else {
        std::cout << "In add_to_observer_pool, ObserverPool had been erase."
                  << std::endl;
    }
}

int main() {
    {
        std::cout << "Observer have same time with ObserverPool" << std::endl;
        std::shared_ptr<Observer> observer = std::make_shared<Observer>();
        std::shared_ptr<ObserverPool> observer_pool =
            std::make_shared<ObserverPool>();
        observer->add_to_observer_pool(observer_pool);
        observer_pool->notifyObservers();
    }

    std::cout << std::endl;
    {
        std::cout << "Observer longer than ObserverPool" << std::endl;
        std::shared_ptr<Observer> observer = std::make_shared<Observer>();
        std::weak_ptr<ObserverPool> weak_ptr_observer_pool;
        {
            std::shared_ptr<ObserverPool> observer_pool =
                std::make_shared<ObserverPool>();
            weak_ptr_observer_pool = observer_pool;
        }
        observer->add_to_observer_pool(weak_ptr_observer_pool);
    }

    std::cout << std::endl;
    {
        std::cout << "ObserverPool longer than Observer" << std::endl;
        std::shared_ptr<ObserverPool> observer_pool =
            std::make_shared<ObserverPool>();
        {
            std::shared_ptr<Observer> observer = std::make_shared<Observer>();
            observer->add_to_observer_pool(observer_pool);
        }
        observer_pool->notifyObservers();
    }

    return 0;
}
