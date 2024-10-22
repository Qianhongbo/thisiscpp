#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
 public:
  ThreadPool(std::size_t num_threads) {
    for (std::size_t i = 0; i < num_threads; i++) {
      workers_.emplace_back([this] {
        for (;;) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
            if (stop_ && tasks_.empty()) {
              return;
            }
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          task();
        }
      });
    }
  }

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  ~ThreadPool() {
    stop_ = true;
    cv_.notify_all();
    for (auto& worker : workers_) {
      worker.join();
    }
  }

  template <class F, class... Args>
  auto enqueue(F&& f, Args&&... args)
      -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (stop_) {
        throw std::runtime_error("enqueue on stopped ThreadPool");
      }
      tasks_.emplace([task]() { (*task)(); });
    }
    cv_.notify_one();
    return res;
  }

 private:
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;

  std::atomic<bool> stop_{false};
  std::mutex mutex_;
  std::condition_variable cv_;
};