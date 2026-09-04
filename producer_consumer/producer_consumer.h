#ifndef PRODUCER_CONSUMER_H_
#define PRODUCER_CONSUMER_H_

#include <unistd.h> // for sleep

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <mutex>
#include <thread>
#include <utility>

template <typename T>
class ProducerConsumer {
 public:

  /**************************************************
   *                                                *
   *             constructor                        *
   *                                                *
   **************************************************/

  ProducerConsumer() {
  }

  ProducerConsumer(const ProducerConsumer& rhs) {
    {
      std::lock_guard<std::mutex> lock(rhs.buf_mutex_);
      max_buf_size_ = rhs.max_buf_size_,
               buf_ = rhs.buf_;
    }
    {
      std::lock_guard<std::mutex> lock(rhs.count_mutex_);
      count_producer_wait_   = rhs.count_producer_wait_;
      count_producer_run_    = rhs.count_producer_run_;
      count_producer_finish_ = rhs.count_producer_finish_;
      count_consumer_wait_   = rhs.count_consumer_wait_;
      count_consumer_run_    = rhs.count_consumer_run_;
      count_consumer_finish_ = rhs.count_consumer_finish_; 
    }
  }

  /**************************************************
   *                                                *
   *                  swap                          *
   *                                                *
   **************************************************/

  void swap(ProducerConsumer& rhs) {
    using std::swap;
    {
#if   __cplusplus >= 201703L
      std::scoped_lock lock(buf_mutex_, rhs.buf_mutex_);
#elif __cplusplus >= 201103L
      std::lock(buf_mutex_, rhs.buf_mutex_);
      std::lock_guard<std::mutex> lhs_lock(    buf_mutex_, std::adopt_lock);
      std::lock_guard<std::mutex> rhs_lock(rhs.buf_mutex_, std::adopt_lock);
#else
      std::cerr << "ProducerConsumer need c++11 or later" << std::endl;
      std::exit(EXIT_FAILURE);
#endif
      swap(max_buf_size_, rhs.max_buf_size_);
      swap(buf_, rhs.buf_);
    }
    {
#if   __cplusplus >= 201703L
      std::scoped_lock lock(count_mutex_, rhs.count_mutex_);
#elif __cplusplus >= 201103L
      std::lock(count_mutex_, rhs.count_mutex_);
      std::lock_guard<std::mutex> lhs_lock(    count_mutex_, std::adopt_lock);
      std::lock_guard<std::mutex> rhs_lock(rhs.count_mutex_, std::adopt_lock);
#else
      std::cerr << "ProducerConsumer need c++11 or later" << std::endl;
      std::exit(EXIT_FAILURE);
#endif
      swap(count_producer_wait_  , rhs.count_producer_wait_);
      swap(count_producer_run_   , rhs.count_producer_run_);
      swap(count_producer_finish_, rhs.count_producer_finish_);
      swap(count_consumer_wait_  , rhs.count_consumer_wait_);
      swap(count_consumer_run_   , rhs.count_consumer_run_);
      swap(count_consumer_finish_, rhs.count_consumer_finish_); 
    }
  }

  /**************************************************
   *                                                *
   *                  operator=                     *
   *                                                *
   **************************************************/

  ProducerConsumer& operator=(const ProducerConsumer& rhs) {
    auto temp(rhs);
    swap(temp);
    return *this;
  }

  /**************************************************
   *                                                *
   *            set_max_buf_size                    *
   *            get_max_buf_size                    *
   *            get_count_producer_wait             *
   *            get_count_producer_run              *
   *            get_count_producer_finish           *
   *            get_count_consumer_wait             *
   *            get_count_consumer_run              *
   *            get_count_consumer_finish           *
   *                                                *
   **************************************************/

  void        set_max_buf_size(std::size_t max_buf_size) { std::lock_guard<std::mutex> lock(buf_mutex_); max_buf_size_ = max_buf_size ; }
  std::size_t get_max_buf_size() const                   { std::lock_guard<std::mutex> lock(buf_mutex_);          return max_buf_size_; }

  std::size_t get_count_producer_wait()   const { std::lock_guard<std::mutex> lock(count_mutex_); return count_producer_wait_;   }
  std::size_t get_count_producer_run()    const { std::lock_guard<std::mutex> lock(count_mutex_); return count_producer_run_;    }
  std::size_t get_count_producer_finish() const { std::lock_guard<std::mutex> lock(count_mutex_); return count_producer_finish_; }
  std::size_t get_count_consumer_wait()   const { std::lock_guard<std::mutex> lock(count_mutex_); return count_consumer_wait_;   }
  std::size_t get_count_consumer_run()    const { std::lock_guard<std::mutex> lock(count_mutex_); return count_consumer_run_;    }
  std::size_t get_count_consumer_finish() const { std::lock_guard<std::mutex> lock(count_mutex_); return count_consumer_finish_; }


  /**************************************************
   *                                                *
   *               ProducerBlocking                 *
   *               ProducerNonBlocking              *
   *                                                *
   **************************************************/

  void ProducerBlocking(const T& data) {
    std::thread thread([this](const T& data){ this->Producer(data); }, data);
    thread.join();
  }

  void ProducerNonBlocking(const T& data) {
    std::thread thread([this](const T& data){ this->Producer(data); }, data);
    thread.detach();
  }

  /************************************************
   *                                              *
   *            ConsumerBlocking                  *
   *            ConsumerNonBlocking               *
   *                                              *
   ************************************************/

  T ConsumerBlocking() {
    {
      std::lock_guard<std::mutex> lock(count_mutex_);
      ++count_consumer_wait_;
    }
    T data;
    {
      std::unique_lock<std::mutex> lock(buf_mutex_);
      wait_consumer_.wait(lock, [this]{ return buf_.size() > 0; });
      {
        std::lock_guard<std::mutex> lock(count_mutex_);
        --count_consumer_wait_;
        ++count_consumer_run_;
      }
      data = buf_.front();
      buf_.pop_front(); 
    }
    sleep(5); // this line just test
    {
      std::lock_guard<std::mutex> lock(count_mutex_);
      --count_consumer_run_;
      ++count_consumer_finish_;
      if (count_producer_wait_ > 0)
        wait_producer_.notify_all();
      else if (count_consumer_wait_ > 0)
        wait_consumer_.notify_all();
    }
    return data;
  }

  std::pair<T, bool> ConsumerNonBlocking() {
    {
      std::lock_guard<std::mutex> lock(buf_mutex_);
      if (buf_.empty())
        return {T(), false};
    }
    return {ConsumerBlocking(), true};
  }

  /********************************************
   *                                          *
   *               output_log                 *
   *                                          *
   ********************************************/

  template <typename CharT, typename Traits>
  void output_log(std::basic_ostream<CharT, Traits>& os) const {
    {
      std::lock_guard<std::mutex> lock(count_mutex_);
      os << std::endl;
      os << "count_producer_finish_ : " << count_producer_finish_ << std::endl;
      os << "count_producer_run_    : " << count_producer_run_    << std::endl;
      os << "count_producer_wait_   : " << count_producer_wait_   << std::endl;
      os << "count_consumer_finish_ : " << count_consumer_finish_ << std::endl;
      os << "count_consumer_run_    : " << count_consumer_run_    << std::endl;
      os << "count_consumer_wait_   : " << count_consumer_wait_   << std::endl;
    }
    {
      std::lock_guard<std::mutex> lock(buf_mutex_);
      os << "max     buf_size       : " << max_buf_size_ << std::endl;
      os << "current buf_size       : " << buf_.size()   << std::endl;
      os << "        buf            : ";
      std::copy(std::begin(buf_), std::end(buf_), std::ostream_iterator<T>(os, " "));
      os << std::endl << std::endl;
    }
  }

 private:

  static constexpr std::size_t DEFAULT_MAX_BUF_SIZE = 5;

  std::size_t max_buf_size_ = DEFAULT_MAX_BUF_SIZE;
    
          std::deque<T> buf_;
  mutable std::mutex    buf_mutex_;

  std::size_t count_producer_wait_   = 0;
  std::size_t count_producer_run_    = 0;
  std::size_t count_producer_finish_ = 0;
  std::size_t count_consumer_wait_   = 0;
  std::size_t count_consumer_run_    = 0;
  std::size_t count_consumer_finish_ = 0;

  mutable std::mutex  count_mutex_;

  mutable std::condition_variable wait_producer_;
  mutable std::condition_variable wait_consumer_;

  /*****************************************
   *                                       *
   *                 producer              *
   *                                       *
   *****************************************/

  void Producer(const T& data) {
    {
      std::lock_guard<std::mutex> lock(count_mutex_);
      ++count_producer_wait_;
    }
    {
      std::unique_lock<std::mutex> lock(buf_mutex_);
      wait_producer_.wait(lock, [this]{ return buf_.size() < max_buf_size_; });
      {
        std::lock_guard<std::mutex> lock(count_mutex_);
        --count_producer_wait_;
        ++count_producer_run_;
      }
      buf_.push_back(data);
    }
    sleep(5); // this line just test
    {
      std::lock_guard<std::mutex> lock(count_mutex_);
      --count_producer_run_;
      ++count_producer_finish_;
      if (count_consumer_wait_ > 0)
        wait_consumer_.notify_all();
      else if (count_producer_wait_ > 0)
        wait_producer_.notify_all();
    }
  }
};

template <typename T>
void swap(ProducerConsumer<T>& lhs, ProducerConsumer<T>& rhs) {
  lhs.swap(rhs);
}

#endif
