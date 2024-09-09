#include "message_queue.h"

#include "gtest/gtest.h"
#include <thread>

namespace rina {
namespace edr {

TEST(MessageQueueTest, PushPop) {
  MessageQueue<int> queue;
  queue.Push(1);
  queue.Push(2);
  queue.Push(3);
  EXPECT_EQ(queue.Pop(), 1);
  EXPECT_EQ(queue.Pop(), 2);
  EXPECT_EQ(queue.Pop(), 3);
}

TEST(MessageQueueTest, PushPopString) {
  MessageQueue<std::string> queue;
  queue.Push("hello");
  queue.Push("world");
  EXPECT_EQ(queue.Pop(), "hello");
  EXPECT_EQ(queue.Pop(), "world");
}

TEST(MessageQueueTest, PopBeforePush) {
  MessageQueue<int> queue;
  std::thread t([&queue] {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    queue.Push(1);
  });
  EXPECT_EQ(queue.Pop(), 1);
  t.join();
}

TEST(MessageQueueTest, MultiThread) {
  MessageQueue<int> queue;
  std::thread t1([&queue] {
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
  });
  std::thread t2([&queue] {
    EXPECT_EQ(queue.Pop(), 1);
    EXPECT_EQ(queue.Pop(), 2);
    EXPECT_EQ(queue.Pop(), 3);
  });
  t1.join();
  t2.join();
}

TEST(MessageQueueTest, Size) {
  MessageQueue<int> queue;
  EXPECT_EQ(queue.Size(), 0);
  queue.Push(1);
  EXPECT_EQ(queue.Size(), 1);
  queue.Push(2);
  EXPECT_EQ(queue.Size(), 2);
  queue.Pop();
  EXPECT_EQ(queue.Size(), 1);
  queue.Pop();
  EXPECT_EQ(queue.Size(), 0);
}

// TEST(MessageQueueTest, Factory) {
//   auto queue = MessageQueueFactory::Instance()->CreateMessageQueue<int>();
//   queue->Push(std::make_shared<int>(1));
//   queue->Push(std::make_shared<int>(2));
//   queue->Push(std::make_shared<int>(3));

//   EXPECT_EQ(*queue->Pop(), 1);
//   EXPECT_EQ(*queue->Pop(), 2);
//   EXPECT_EQ(*queue->Pop(), 3);
// }

} // namespace edr
} // namespace rina