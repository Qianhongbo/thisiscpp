#pragma once

#include <atomic>
#include <condition_variable>
#include <queue>

#include "gaea/common/macros.h"

namespace rina {
namespace edr {

template <typename T>
class MessageQueue {
 public:
  /**
   * @brief Construct a new Message Queue object
   *
   */
  MessageQueue() = default;

  /**
   * @brief Copy constructor was deleted
   *
   */
  MessageQueue(const MessageQueue &) = delete;

  /**
   * @brief Copy assignment operator was deleted
   *
   * @return MessageQueue&
   */
  MessageQueue &operator=(const MessageQueue &) = delete;

  /**
   * @brief Close the queue
   *
   */
  void Shutdown();

  /**
   * @brief Get the size of the queue
   *
   * @return size_t size of the queue
   */
  size_t Size() const;

  /**
   * @brief Check if the queue is empty
   *
   * @return true if the queue is empty
   * @return false if the queue is not empty
   */
  bool Empty() const { return Size() == 0; }

  /**
   * @brief Push a message to the queue
   *
   * @param msg message of type T
   */
  void Push(const T &msg);

  /**
   * @brief Pop a message from the queue
   *
   * @return T message of type T
   */
  T Pop();

 private:
  std::queue<T> queue_;

  mutable std::mutex mutex_;
  std::condition_variable cv_;
  std::atomic<bool> shutdown_flag_{false};
};

template <typename T>
void MessageQueue<T>::Shutdown() {
  if (shutdown_flag_.load()) {
    return;
  }
  shutdown_flag_.store(true);
  cv_.notify_all();
  // clear the queue
  std::lock_guard<std::mutex> lock(mutex_);
  while (!queue_.empty()) {
    queue_.pop();
  }
}

template <typename T>
void MessageQueue<T>::Push(const T &msg) {
  std::lock_guard<std::mutex> lock(mutex_);
  queue_.push(msg);
  cv_.notify_one();
}

template <typename T>
T MessageQueue<T>::Pop() {
  std::unique_lock<std::mutex> lock(mutex_);
  cv_.wait(lock, [this] { return shutdown_flag_ || !queue_.empty(); });
  if (queue_.empty()) {
    return T();
  }
  T msg = queue_.front();
  queue_.pop();
  return msg;
}

template <typename T>
size_t MessageQueue<T>::Size() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return queue_.size();
}

template <typename T>
using MessageQueuePtr = std::shared_ptr<MessageQueue<std::shared_ptr<T>>>;

class MessageQueueFactory {
 public:
  /**
   * @brief Create a new message queue
   *
   * @tparam T type of the message queue
   * @return MessageQueuePtr pointer to the message queue
   */
  template <typename T>
  MessageQueuePtr<T> CreateMessageQueue() {
    return std::make_shared<MessageQueue<std::shared_ptr<T>>>();
  }

 private:
  DECLARE_SINGLETON(MessageQueueFactory)
};

}  // namespace edr
}  // namespace rina
