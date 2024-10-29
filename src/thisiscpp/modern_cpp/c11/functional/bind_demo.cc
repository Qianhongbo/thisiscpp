#include <functional>
#include <iostream>

int add(int a, int b) { return a + b; }

int main() {
  auto bound_add = std::bind(add, std::placeholders::_1, 3);
  std::cout << "Result: " << bound_add(2) << std::endl;  // 输出 Result: 5
  return 0;
}