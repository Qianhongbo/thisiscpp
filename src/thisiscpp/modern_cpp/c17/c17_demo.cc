#include <any>
#include <iostream>
#include <optional>
#include <string_view>
#include <tuple>
#include <variant>

std::optional<int> divide(int a, int b) {
  if (b == 0) {
    return std::nullopt;
  }
  return a / b;
};

void print(std::string_view sv) { std::cout << sv << std::endl; }

int main() {
  // std::tuple
  std::tuple<int, double, std::string> t(10, 3.14, "hello");
  auto [a, b, c] = t;
  std::cout << a << " " << b << " " << c << std::endl;

  // if switch 初始化语句
  if (auto x = 10; x > 5) {
    std::cout << x << std::endl;
  }

  if (auto x = 10) {
    std::cout << x << std::endl;
  }

  if (auto x = 0) {
    std::cout << x << std::endl;
  }

  // std::optional
  if (auto result = divide(10, 2); result.has_value()) {
    std::cout << result.value() << std::endl;
  }

  if (auto result = divide(10, 0); result.has_value()) {
    std::cout << result.value() << std::endl;
  } else {
    std::cout << "Divide by zero" << std::endl;
  }

  // std::variant
  std::variant<int, double, std::string> v;
  v = 10;
  std::cout << std::get<int>(v) << std::endl;

  v = 3.14;
  std::cout << std::get<double>(v) << std::endl;

  v = "hello";
  std::cout << std::get<std::string>(v) << std::endl;

  // std::any
  std::any a1 = 10;
  std::cout << std::any_cast<int>(a1) << std::endl;

  a1 = 3.14;
  std::cout << std::any_cast<double>(a1) << std::endl;

  a1 = "hello";
  std::cout << std::any_cast<const char *>(a1) << std::endl;

  // std::string_view
  // 可以同时管理 const char* 和 std::string
  // 减少了拷贝，无论是子串还是函数变量
  std::string s = "hello string_view";
  print(s);

  return 0;
}