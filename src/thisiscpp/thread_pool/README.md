# Thread pool

## 变参数模板

变参数模板（Variadic Templates）是 C++11 引入的一种强大特性，它允许你定义接受可变数量参数的模板。通过变参数模板，你可以创建更加灵活和通用的代码，适应不同类型和数量的参数。以下是变参数模板的详细解释：

### 1. **定义和语法**

变参数模板使用模板参数包（parameter pack）来表示任意数量的模板参数。基本语法如下：

```cpp
template <typename... Args>
```

- **`typename... Args`**：`Args` 是一个模板参数包，表示可以接受零个或多个类型参数。
- `...` 符号用于指示这是一个参数包。

### 2. **使用变参数模板**

变参数模板通常用于函数模板、类模板和其他类型的模板。以下是一些主要用途和示例：

#### 2.1 函数模板

你可以定义一个接受任意数量参数的函数模板。例如，实现一个可以计算任意数量参数之和的函数：

```cpp
#include <iostream>

// 递归基：当没有参数时返回 0
template <typename T>
T sum(T value) {
    return value;
}

// 变参数模板：计算多个参数的和
template <typename T, typename... Args>
T sum(T value, Args... args) {
    return value + sum(args...); // 递归调用
}

int main() {
    std::cout << "Sum: " << sum(1, 2, 3, 4, 5) << std::endl; // 输出 15
    return 0;
}
```

#### 2.2 类模板

变参数模板也可以用于类模板，例如，创建一个简单的日志类，接受任意数量的日志消息：

```cpp
#include <iostream>
#include <string>

// 日志类
template <typename... Args>
class Logger {
public:
    void log(Args... args) {
        logImpl(args...); // 调用辅助函数
    }

private:
    void logImpl(Args... args) {
        (std::cout << ... << args) << std::endl; // 使用折叠表达式打印参数
    }
};

int main() {
    Logger<std::string, int> logger;
    logger.log("Error:", 404, "Not Found");
    return 0;
}
```

### 3. **参数包展开**

在变参数模板中，可以使用参数包展开（pack expansion）来处理参数包中的每个参数。以下是两种常见的参数包展开方式：

#### 3.1 函数调用

你可以在函数调用中展开参数包：

```cpp
template <typename... Args>
void func(Args... args) {
    // 在函数内部调用其他函数，展开参数包
    anotherFunc(args...);
}
```

#### 3.2 使用逗号表达式

在 C++17 中，你可以使用折叠表达式来简化对参数包的处理，例如计算和：

```cpp
template <typename... Args>
auto sum(Args... args) {
    return (args + ...); // C++17 中的折叠表达式
}
```

### 4. **优点和应用**

- **灵活性**：变参数模板提供了灵活的接口，可以处理任意数量的参数。
- **代码复用**：可以编写通用代码，避免为不同参数数量编写多个重载函数。
- **类型安全**：使用模板参数，可以保证在编译时检查参数的类型。

### 5. **示例：字符串连接**

下面是一个使用变参数模板进行字符串连接的示例：

```cpp
#include <iostream>
#include <string>

// 递归基：当没有参数时返回空字符串
std::string concat() {
    return "";
}

// 变参数模板：连接多个字符串
template <typename T, typename... Args>
std::string concat(T value, Args... args) {
    return std::to_string(value) + concat(args...);
}

int main() {
    std::string result = concat("Value:", 42, "and", 3.14);
    std::cout << result << std::endl; // 输出 "Value:42and3.14"
    return 0;
}
```

### 总结

- **变参数模板** 允许你定义接受可变数量参数的模板，提供了更大的灵活性和代码复用能力。
- **参数包展开** 是变参数模板的一个重要特性，使得在函数调用或其他操作中处理多个参数变得简单。
- 变参数模板在许多场景下都非常有用，包括日志记录、数据处理、API 设计等。