#include <iostream>
#include <type_traits>

// 一个简单的模板函数，返回两个参数的和
template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
  return a + b;
}

// template <typename T1, typename T2>
// decltype(a + b) add2(T1 a, T2 b) {
//   return a + b;
// }

int main() {
  std::cout << add(1, 2) << std::endl;      // 输出 3
  std::cout << add(1.5, 2.5) << std::endl;  // 输出 4.0
  std::cout << add(1, 2.5) << std::endl;    // 输出 3.5
  return 0;
}