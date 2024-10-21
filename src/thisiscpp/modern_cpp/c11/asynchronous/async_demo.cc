#include <future>
#include <iostream>

int computeSquare(int x) {
  std::cout << "计算平方..." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时计算
  return x * x;
}

int main() {
  // 使用 std::async 启动异步任务，立即在新线程中执行
  std::future<int> result1 = std::async(std::launch::async, computeSquare, 5);
  // 使用 std::launch::deferred，任务不会立即执行
  std::future<int> result2 = std::async(std::launch::deferred, computeSquare, 5);

  std::cout << "主线程正在做其他工作..." << std::endl;

  // 只有在调用 get() 时任务才会执行
  int value1 = result1.get();
  std::cout << "结果1是: " << value1 << std::endl;

  int value2 = result2.get();
  std::cout << "结果2是: " << value2 << std::endl;

  return 0;
}