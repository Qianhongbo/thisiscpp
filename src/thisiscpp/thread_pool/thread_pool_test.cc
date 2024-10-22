#include "thisiscpp/thread_pool/thread_pool.h"
#include "gtest/gtest.h"

TEST(ThreadPoolTest, ThreadPool) {
  ThreadPool pool(4);

  std::vector<std::future<int>> results;
  for (int i = 0; i < 8; ++i) {
    results.emplace_back(pool.enqueue([i] {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      return i * i;
    }));
  }

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(results[i].get(), i * i);
  }
}