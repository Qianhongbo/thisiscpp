#include <chrono>
#include <future>
#include <iostream>

int square(int x) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return x * x;
}

int main() {
  std::future<int> result = std::async(std::launch::async, square, 5);

  std::cout << "Calculating square..." << std::endl;

  std::cout << "Main thread is doing something else..." << std::endl;

  int square_result = result.get();

  std::cout << "Square result: " << square_result << std::endl;

  return 0;
}