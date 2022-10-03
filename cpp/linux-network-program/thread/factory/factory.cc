
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>

class StockFactory;

class Stock {
   public:
    Stock(std::string name) : name_(name) {}

    const std::string& get_name() const { return name_; }

   private:
    std::string name_;
};

class StockFactory : public std::enable_shared_from_this<StockFactory> {
   public:
    std::shared_ptr<Stock> get(const std::string& name) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& weak_stock = stocks_[name];
        std::shared_ptr<Stock> stock = weak_stock.lock();
        if (!stock) {
            stock.reset(
                new Stock(name),
                std::bind(StockFactory::static_delete_stock,
                          std::weak_ptr<StockFactory>(shared_from_this()),
                          std::placeholders::_1));
            weak_stock = stock;
        }
        return stock;
    }

   private:
    std::mutex mutex_;
    std::unordered_map<std::string, std::weak_ptr<Stock>> stocks_;

    static void static_delete_stock(
        const std::weak_ptr<StockFactory>& weak_factory, Stock* stock) {
        std::shared_ptr<StockFactory> obj(weak_factory.lock());
        if (obj) obj->delete_stock(stock);
        delete stock;
    }

    void delete_stock(Stock* stock) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = stocks_[stock->get_name()];
        if (it.expired()) stocks_.erase(stock->get_name());
    }
};

int main() {
    {
        std::shared_ptr<StockFactory> factory =
            std::make_shared<StockFactory>();
        {
            std::shared_ptr<Stock> stock1 = factory->get("Google");
            std::shared_ptr<Stock> stock2 = factory->get("Google");
        }
    }

    {
        std::shared_ptr<Stock> stock1;
        {
            std::shared_ptr<StockFactory> factory =
                std::make_shared<StockFactory>();
            stock1 = factory->get("Google");
            std::shared_ptr<Stock> stock2 = factory->get("Google");
        }
    }

    return 0;
}
