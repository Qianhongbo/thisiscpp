# CPP 11 基础新特性

## 1. auto 关键字

auto 关键字可以让编译器自动推导变量的类型，从而简化代码书写。例如：

```cpp
auto i = 10; // i 的类型为 int
auto d = 3.14; // d 的类型为 double
```

```cpp
int n = 20;
auto *p = &n, m = 10; // auto 被推导为 int 类型，所以 m 也被推导为 int 类型
```

```cpp
int x = 0;
auto *p1 = &x;  // p1 为 int *，auto 推导为 int
auto p2 = &x;   // p2 为 int*，auto 推导为 int*
auto &r1 = x;   // r1 为 int&，auto 推导为 int
auto r2 = r1;   // r2 为  int，auto 推导为 int
```

```cpp
int x = 0;
const auto n = x;  // n 为 const int ，auto 被推导为 int
auto f = n;  // f 为 int，auto 被推导为 int（const 属性被抛弃）
const auto &r1 = x;  // r1 为 const int& 类型，auto 被推导为 int
auto &r2 = r1;       // r2 为 const int& 类型，auto 被推导为 const int
```

```cpp
class A {
 public:
  static int get(void) { return 100; }
};

class B {
 public:
  static const char *get(void) { return "class B string"; }
};

template <typename T>
void print() {
  auto x = T::get();
  std::cout << x << std::endl;
}

int main() {
  print<A>();
  print<B>();
  return 0;
}
```

## 2. nullptr 关键字

nullptr 是 C++11 新增的关键字，用于表示空指针。nullptr 是一个字面常量，可以隐式转换为任意指针类型。例如：

```cpp
int *p = nullptr;
```

## 3. decltype 关键字

decltype 关键字用于获取表达式的类型。例如：

```cpp
int x = 10;
decltype(x) y = 20; // y 的类型为 int
```

### 3.1 decltype(auto)

decltype(auto) 可以用于声明变量，其类型由表达式的类型推导得到。例如：

```cpp
int x = 10;
decltype(auto) y = x; // y 的类型为 int
```

### 3.2 decltype(auto) 与 auto 的区别

```cpp
int a = 10;
int &ref = a;

auto x =ref; // x 的类型为 int

decltype(ref) y = a; // y 的类型为 int&

decltype(auto) z = ref; // z 的类型为 int&
```

## 4. lambda 表达式

lambda 表达式是 C++11 新增的特性，用于定义匿名函数。lambda 表达式的语法如下：

```cpp
[capture](parameters) -> return_type { body }
```

例如：

```cpp
auto f = [](int x, int y) -> int { return x + y; };
std::cout << f(10, 20) << std::endl;
```

### 4.1 lambda 表达式的捕获列表

lambda 表达式的捕获列表用于捕获外部变量。捕获列表有以下几种形式：

- `[]`：不捕获任何外部变量
- `[var]`：捕获 var 变量
- `[&var]`：以引用方式捕获 var 变量
- `[=]`：以值方式捕获所有外部变量
- `[&]`：以引用方式捕获所有外部变量
- `[var, &var2]`：var 以值方式捕获，var2 以引用方式捕获
- `[=, &var]`：以值方式捕获所有外部变量，但 var 以引用方式捕获
- `[&, var]`：以引用方式捕获所有外部变量，但 var 以值方式捕获
- `[this]`：捕获 this 指针
- `[&, this]`：以引用方式捕获所有外部变量，但 this 指针以值方式捕获
- `[=, this]`：以值方式捕获所有外部变量，但 this 指针以引用方式捕获

### 4.2 lambda 表达式的参数列表

lambda 表达式的参数列表用于定义函数参数。例如：

```cpp
auto f = [](int x, int y) -> int { return x + y; };
