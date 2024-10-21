#include <chrono>
#include <future>
#include <iostream>
#include <thread>

// 模拟一个耗时的任务
void calculateSquare(std::promise<int>&& prom, int x) {
  std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时操作
  prom.set_value(x * x);                                 // 设置结果
}

int main() {
  // 创建 promise 和对应的 future
  std::promise<int> prom;
  std::future<int> fut = prom.get_future();

  // 在新线程中计算平方值，并将结果通过 promise 传回
  std::thread t(calculateSquare, std::move(prom), 6);

  std::cout << "主线程正在等待结果..." << std::endl;

  // 获取计算结果，调用 get() 会阻塞直到结果可用
  int result = fut.get();
  std::cout << "计算结果是: " << result << std::endl;

  t.join();
  return 0;
}