#ifndef READER_WRITER_AND_READER_FIRST_H_
#define READER_WRITER_AND_READER_FIRST_H_

#include <unistd.h> // for sleep

#include <algorithm>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <mutex>
#include <thread>
#include <utility>

template <typename T>
class ReaderWriterAndReaderFirst {
 public:

  /**************************************************
   *                                                *
   *             constructor                        *
   *                                                *
   **************************************************/

  ReaderWriterAndReaderFirst() {
  }

  ReaderWriterAndReaderFirst(const ReaderWriterAndReaderFirst& rhs) {
    {
      std::lock_guard<std::mutex> lock(rhs.buf_mutex_);
      max_buf_size_ = rhs.max_buf_size_,
               buf_ = rhs.buf_;
    }
    {
      std::lock_guard<std::mutex> lock(rhs.count_mutex_);
      count_writer_wait_   = rhs.count_writer_wait_;
      count_writer_run_    = rhs.count_writer_run_;
      count_writer_finish_ = rhs.count_writer_finish_;
      count_reader_wait_   = rhs.count_reader_wait_;
      count_reader_run_    = rhs.count_reader_run_;
      count_reader_finish_ = rhs.count_reader_finish_; 
    }
  }

  /**************************************************
   *                                                *
   *                  swap                          *
   *                                                *
   **************************************************/

  void swap(ReaderWriterAndReaderFirst& rhs) {
    using std::swap;
    {
#if   __cplusplus >= 201703L
      std::scoped_lock lock(buf_mutex_, rhs.buf_mutex_);
#elif __cplusplus >= 201103L
      std::lock(buf_mutex_, rhs.buf_mutex_);
      std::lock_guard<std::mutex> lhs_lock(    buf_mutex_, std::adopt_lock);
      std::lock_guard<std::mutex> rhs_lock(rhs.buf_mutex_, std::adopt_lock);
#else
      std::cerr << "ReaderWriterAndReaderFirst need c++11 or later" << std::endl;
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
      std::cerr << "ReaderWriterAndReaderFirst need c++11 or later" << std::endl;
      std::exit(EXIT_FAILURE);
#endif
      swap(count_writer_wait_  , rhs.count_writer_wait_);
      swap(count_writer_run_   , rhs.count_writer_run_);
      swap(count_writer_finish_, rhs.count_writer_finish_);
      swap(count_reader_wait_  , rhs.count_reader_wait_);
      swap(count_reader_run_   , rhs.count_reader_run_);
      swap(count_reader_finish_, rhs.count_reader_finish_); 
    }
  }

  /**************************************************
   *                                                *
   *                  operator=                     *
   *                                                *
   **************************************************/

  ReaderWriterAndReaderFirst& operator=(const ReaderWriterAndReaderFirst& rhs) {
    auto temp(rhs);
    swap(temp);
    return *this;
  }

  /**************************************************
   *                                                *
   *            set_max_buf_size                    *
   *            get_max_buf_size                    *
   *            get_count_writer_wait               *
   *            get_count_writer_run                *
   *            get_count_writer_finish             *
   *            get_count_reader_wait               *
   *            get_count_reader_run                *
   *            get_count_reader_finish             *
   *                                                *
   **************************************************/

  void        set_max_buf_size(std::size_t max_buf_size) { std::lock_guard<std::mutex> lock(buf_mutex_); max_buf_size_ = max_buf_size ; }
  std::size_t get_max_buf_size() const                   { std::lock_guard<std::mutex> lock(buf_mutex_);          return max_buf_size_; }

  std::size_t get_count_writer_wait()   const { std::lock_guard<std::mutex> lock(count_mutex_); return count_writer_wait_;   }
  std::size_t get_count_writer_run()    const { std::lock_guard<std::mutex> lock(count_mutex_); return count_writer_run_;    }
  std::size_t get_count_writer_finish() const { std::lock_guard<std::mutex> lock(count_mutex_); return count_writer_finish_; }
  std::size_t get_count_reader_wait()   const { std::lock_guard<std::mutex> lock(count_mutex_); return count_reader_wait_;   }
  std::size_t get_count_reader_run()    const { std::lock_guard<std::mutex> lock(count_mutex_); return count_reader_run_;    }
  std::size_t get_count_reader_finish() const { std::lock_guard<std::mutex> lock(count_mutex_); return count_reader_finish_; }

  /************************************************
   *                                              *
   *            WriterBlocking                    *
   *            WriterNonBlocking                 *
   *                                              *
   ************************************************/

  void WriterBlocking(const T& data) {
    std::thread thread([this](const T& data){ this->Writer(data); }, data);
    thread.join();
  }

  void WriterNonBlocking(const T& data) {
    std::thread thread([this](const T& data){ this->Writer(data); }, data);
    thread.detach();
  }

  /**************************************************
   *                                                *
   *               ReaderBlocking                   *
   *               ReaderNonBlocking                *
   *                                                *
   **************************************************/

  void ReaderBlocking() {
    std::thread thread([this](){ this->Reader(); });
    thread.join();
  }

  void ReaderNonBlocking() {
    std::thread thread([this](){ this->Reader(); });
    thread.detach();
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
      os << "count_reader_finish_ : " << count_reader_finish_ << std::endl;
      os << "count_reader_run_    : " << count_reader_run_    << std::endl;
      os << "count_reader_wait_   : " << count_reader_wait_   << std::endl;
      os << "count_writer_finish_ : " << count_writer_finish_ << std::endl;
      os << "count_writer_run_    : " << count_writer_run_    << std::endl;
      os << "count_writer_wait_   : " << count_writer_wait_   << std::endl;
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

  std::size_t count_writer_wait_   = 0;
  std::size_t count_writer_run_    = 0;
  std::size_t count_writer_finish_ = 0;
  std::size_t count_reader_wait_   = 0;
  std::size_t count_reader_run_    = 0;
  std::size_t count_reader_finish_ = 0;

  mutable std::mutex  count_mutex_;

  mutable std::condition_variable wait_writer_;
  mutable std::condition_variable wait_reader_;

  /*****************************************
   *                                       *
   *                  writer               *
   *                                       *
   *****************************************/

  void Writer(const T& data) {
    {
        std::unique_lock<std::mutex> lock(count_mutex_);
        ++count_writer_wait_;
        wait_writer_.wait(lock, [this]{ return count_reader_wait_ + count_reader_run_ + count_writer_run_ == 0; });
        --count_writer_wait_;
        ++count_writer_run_;
    }
    {
        std::lock_guard<std::mutex> lock(buf_mutex_);
        buf_.push_back(data);
    }
    sleep(5); // this line just test
    {
        std::lock_guard<std::mutex> lock(count_mutex_);
        --count_writer_run_;
        ++count_writer_finish_;
        if (count_reader_wait_ > 0)
            wait_reader_.notify_all();
        else if (count_writer_wait_ > 0)
            wait_writer_.notify_all();
    }
  }

  /*******************************************
   *                                         *
   *                Reader                   *
   *                                         *
   *******************************************/

  void Reader() {
    {
        std::unique_lock<std::mutex> lock(count_mutex_);
        ++count_reader_wait_;
        wait_reader_.wait(lock, [this]{ return count_writer_run_ == 0; });
        --count_reader_wait_;
        ++count_reader_run_;
    }

    /**********************
     *                    *
     *        read        *
     *                    *
     **********************/
    sleep(5); // this line just test
    {
        std::lock_guard<std::mutex> lock(count_mutex_);
        --count_reader_run_;
        ++count_reader_finish_;
        if (count_reader_run_ == 0 && count_writer_wait_ != 0)
            wait_writer_.notify_all();
    }
  }
};

template <typename T>
void swap(ReaderWriterAndReaderFirst<T>& lhs, ReaderWriterAndReaderFirst<T>& rhs) {
  lhs.swap(rhs);
}

#endif
