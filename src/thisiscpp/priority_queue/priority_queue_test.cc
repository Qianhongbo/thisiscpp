#include "thisiscpp/priority_queue/priority_queue.h"
#include "gtest/gtest.h"

TEST(PriorityQueueTest, MyPriorityQueue) {
  MyPriorityQueue<double> pq(
      10, [](const double& a, const double& b) { return a > b; });

  EXPECT_EQ(pq.size(), 0);
  EXPECT_EQ(pq.isEmpty(), true);
  EXPECT_EQ(pq.parent(1), 0);
  EXPECT_EQ(pq.left(1), 2);
  EXPECT_EQ(pq.right(1), 3);
  EXPECT_EQ(pq.left(2), 4);
  EXPECT_EQ(pq.right(2), 5);
  EXPECT_EQ(pq.left(3), 6);
  EXPECT_EQ(pq.right(3), 7);

  pq.push(1.0);
  EXPECT_EQ(pq.size(), 1);
  EXPECT_EQ(pq.isEmpty(), false);
  EXPECT_EQ(pq.peek(), 1.0);
  pq.push(2.0);
  EXPECT_EQ(pq.size(), 2);
  EXPECT_EQ(pq.peek(), 2.0);
  pq.push(3.0);
  EXPECT_EQ(pq.size(), 3);

  EXPECT_EQ(pq.pop(), 3.0);
  EXPECT_EQ(pq.pop(), 2.0);
  EXPECT_EQ(pq.pop(), 1.0);
}