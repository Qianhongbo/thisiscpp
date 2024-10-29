# Functional

## std::bind

`std::bind`是C++11引入的一个标准库函数，用于创建函数对象（function object），它将函数或可调用对象与一组参数绑定在一起。`std::bind`返回一个新的函数对象，当调用这个新的函数对象时，它会调用原始函数，并使用绑定的参数。

### 语法
```cpp
#include <functional>

auto bound_function = std::bind(callable, arg1, arg2, ...);
```

- **callable**: 可以是函数指针、成员函数指针、函数对象或lambda表达式。
- **arg1, arg2, ...**: 要绑定的参数，可以是具体的值、占位符（如`std::placeholders::_1`）或其他绑定的参数。

### 示例
以下是一些使用`std::bind`的示例：

#### 绑定普通函数
```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    auto bound_add = std::bind(add, 2, 3);
    std::cout << "Result: " << bound_add() << std::endl;  // 输出 Result: 5
    return 0;
}
```

#### 绑定成员函数
```cpp
#include <iostream>
#include <functional>

class MyClass {
public:
    void display(int a, int b) {
        std::cout << "a: " << a << ", b: " << b << std::endl;
    }
};

int main() {
    MyClass obj;
    auto bound_display = std::bind(&MyClass::display, &obj, 2, 3);
    bound_display();  // 输出 a: 2, b: 3
    return 0;
}
```

#### 使用占位符
```cpp
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    using namespace std::placeholders;
    auto bound_add = std::bind(add, _1, 3);
    std::cout << "Result: " << bound_add(2) << std::endl;  // 输出 Result: 5
    return 0;
}
```
