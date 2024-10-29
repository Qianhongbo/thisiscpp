# 模板

## Trailing Return Type

尾置返回类型（Trailing Return Type）是C++11引入的一种语法，用于在函数声明中将返回类型放在参数列表之后。这种语法特别适用于模板函数，因为它可以简化返回类型的声明，尤其是在返回类型依赖于模板参数时。

### 语法
尾置返回类型的语法如下：

```cpp
auto function_name(parameters) -> return_type {
    // function body
}
```

### 示例
以下是一个使用尾置返回类型的示例：

```cpp
#include <iostream>
#include <type_traits>

// 一个简单的模板函数，返回两个参数的和
template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << std::endl;           // 输出 3
    std::cout << add(1.5, 2.5) << std::endl;       // 输出 4.0
    std::cout << add(1, 2.5) << std::endl;         // 输出 3.5
    return 0;
}
```

在这个示例中，`add`函数使用了尾置返回类型`-> decltype(a + b)`，表示返回类型是表达式`a + b`的类型。