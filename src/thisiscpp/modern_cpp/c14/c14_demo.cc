#include <iostream>
#include <memory>
#include <utility>

// 返回类型推导
auto add(int x, int y) { return x + y; };

// decltype(auto), 相比较于 auto, decltype(auto) 会保留引用和 cv 限定符
decltype(auto) getX(int x) { return x; };

// constexpr 函数
constexpr int square(int x) { return x * x; };

// 变量模板
template <typename T>
constexpr T pi = T(3.1415926535897932385);

// std::interger_sequence
template <std::size_t... Is>
void print_sequence(std::index_sequence<Is...>) {
  ((std::cout << Is << ' '), ...);
}

int main() {
  // 泛型 lambda 表达式
  auto lambda = [](auto x, auto y) { return x + y; };

  std::cout << lambda(1, 2) << std::endl;

  // 二进制字面量
  int bin = 0b1010;
  std::cout << bin << std::endl;

  // 返回类型推导
  std::cout << add(1, 2) << std::endl;

  // 智能指针
  auto ptr = std::make_unique<int>(10);
  std::cout << *ptr << std::endl;

  // 变量模板
  std::cout << pi<double> << std::endl;
  std::cout << pi<float> << std::endl;
  std::cout << pi<int> << std::endl;

  // decltype(auto)
  std::cout << getX(10) << std::endl;

  // constexpr 函数
  std::cout << square(10) << std::endl;

  // std::integer_sequence
  print_sequence(std::make_index_sequence<10>{});

  // std::exchange
  int a{5};
  int b = std::exchange(a, 10);
  std::cout << a << " " << b << std::endl;

  return 0;
}