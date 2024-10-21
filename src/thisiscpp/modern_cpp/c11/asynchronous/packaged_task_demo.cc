#include <future>
#include <iostream>
#include <thread>

// 定义一个简单的任务
int computeSquare(int x) { return x * x; }

int main() {
  // 创建一个 packaged_task，封装 computeSquare 函数
  std::packaged_task<int(int)> task(computeSquare);

  // 获取与 packaged_task 关联的 future 对象
  std::future<int> result = task.get_future();

  // 在新线程中执行任务
  std::thread t(std::move(task), 5);  // 传递参数 5

  std::cout << "主线程继续执行..." << std::endl;

  // 获取计算结果，调用 get() 会阻塞直到结果可用
  int value = result.get();  // 等待并获取结果
  std::cout << "结果是: " << value << std::endl;

  t.join();  // 等待线程结束
  return 0;
}