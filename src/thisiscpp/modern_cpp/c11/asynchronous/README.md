## 什么是std::future

在C++中，`std::future` 是用于处理 **异步任务** 的一种机制。它允许你在未来的某个时间获取一个异步操作的结果，避免阻塞主线程或当前线程去等待结果。你可以把 `std::future` 看作是一个占位符，它会在任务执行完毕后持有结果。

### 简单类比：
- 想象一下你去咖啡店点一杯咖啡，服务员告诉你稍等几分钟。这时，他们给你一个取咖啡的牌子，而你继续做其他事情。当咖啡准备好时，你用这个牌子去拿你的咖啡。在这个例子中，**取咖啡的牌子** 就是 `std::future`，而咖啡就是异步操作的结果。

### 使用场景：
`std::future` 通常用于以下场景：
1. **异步任务**：在后台执行某个任务，同时当前线程可以做其他事情。
2. **同步结果**：当异步任务完成时，`std::future` 提供一种方式让你获取任务的结果。
3. **并发处理**：允许多个任务同时执行，并且你可以分别获取它们的执行结果。

### 例子：
假设你有一个任务，计算一个数字的平方，并且这个任务可能很耗时。你不想让主线程被这个任务阻塞，因此你可以使用 `std::future` 来异步地执行这个任务，然后在稍后获取结果。

```cpp
#include <iostream>
#include <future>
#include <chrono>

// 模拟耗时任务，计算平方
int square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return x * x;
}

int main() {
    // 启动异步任务，返回std::future
    std::future<int> result = std::async(std::launch::async, square, 5);

    std::cout << "正在计算平方..." << std::endl;

    // 执行其他任务
    std::cout << "主线程可以做其他事情..." << std::endl;

    // 获取异步任务的结果，get()会阻塞直到任务完成
    int value = result.get();

    // 输出计算结果
    std::cout << "结果是: " << value << std::endl;

    return 0;
}
```

### 解释：
1. **启动异步任务**：  
   - `std::async(std::launch::async, square, 5)` 启动一个异步任务来计算 5 的平方。`std::future<int>` 对象 `result` 用来存储这个任务的返回结果类型 `int`。
   
2. **异步处理**：  
   - 在异步任务执行的同时，主线程继续运行而不会被阻塞。

3. **获取结果**：  
   - 调用 `result.get()` 来获取任务的返回结果。当任务完成时，`get()` 返回异步操作的结果。如果任务尚未完成，`get()` 会阻塞，直到任务完成。

### 未来 vs 现在：
`std::future` 和普通的函数调用的区别在于：
- 普通函数调用是**同步的**，调用者会被阻塞直到函数完成并返回结果。
- `std::future` 是**异步的**，你可以启动一个任务并立刻继续执行其他操作。稍后，当你

## 什么是std::async

`std::async` 是 C++11 中引入的用于启动异步任务的标准库函数。它的主要作用是**在后台异步执行某个函数**，并返回一个 `std::future` 对象，通过该对象可以获取函数执行的结果。

### 基本用法

```cpp
std::future<ReturnType> std::async(LaunchPolicy policy, Callable&& func, Args&&... args);
```

- **ReturnType**：函数返回值的类型。
- **LaunchPolicy**：定义任务的执行策略，通常是 `std::launch::async` 或 `std::launch::deferred`，用来决定是否立即在新线程中执行任务。
- **Callable**：可调用对象，比如函数指针、lambda 表达式、函数对象等。
- **Args**：传递给函数的参数。

`std::async` 的工作原理是启动一个任务并将其结果封装在 `std::future` 中，任务可以在**新线程**中异步执行，也可以在**调用`get()`时延迟执行**，具体行为由 `LaunchPolicy` 决定。

### 详细参数解释

1. **LaunchPolicy**:
   - `std::launch::async`：任务会在**一个新线程**中立即启动并异步执行，主线程不会等待任务完成。
   - `std::launch::deferred`：任务**不会立即执行**，而是推迟到调用 `future.get()` 的时候才执行，且**不会创建新线程**。
   - 默认情况下，如果不传递 `LaunchPolicy`，`std::async` 的行为是由编译器决定的，它可能选择使用 `std::launch::async` 或 `std::launch::deferred`。

2. **Callable**：
   可以是任何可调用对象，比如：
   - 函数指针
   - 函数对象
   - Lambda 表达式
   - 成员函数指针

3. **Args**：
   要传递给可调用对象的参数。`std::async` 会通过完美转发（`std::forward`）将参数传递给任务。

### 示例：异步执行函数

```cpp
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int computeSquare(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时计算
    return x * x;
}

int main() {
    // 使用 std::async 启动异步任务，立即在新线程中执行
    std::future<int> result = std::async(std::launch::async, computeSquare, 5);

    std::cout << "主线程继续执行..." << std::endl;

    // 获取异步任务的结果，调用 get() 时如果任务没有完成，会阻塞等待
    int value = result.get();  // 等待并获取结果
    std::cout << "结果是: " << value << std::endl;

    return 0;
}
```

### 说明：
1. `std::async` 使用 `std::launch::async` 启动任务 `computeSquare(5)`，并在后台异步执行它。
2. 主线程继续运行，输出 "主线程继续执行..."。
3. 当 `future.get()` 被调用时，主线程会等待异步任务完成，并返回计算结果。

### 示例：延迟执行任务

```cpp
#include <iostream>
#include <future>

int computeSquare(int x) {
    return x * x;
}

int main() {
    // 使用 std::launch::deferred，任务不会立即执行
    std::future<int> result = std::async(std::launch::deferred, computeSquare, 5);

    std::cout << "主线程正在做其他工作..." << std::endl;

    // 只有在调用 get() 时任务才会执行
    int value = result.get();
    std::cout << "结果是: " << value << std::endl;

    return 0;
}
```

### 说明：
1. 使用 `std::launch::deferred` 启动任务，任务不会在 `async` 调用时立即执行，而是等到调用 `get()` 时才执行。
2. 当 `result.get()` 被调用时，任务会在主线程中同步执行。

### 何时使用 `std::async`？

- **异步计算**：如果有某些计算比较耗时并且不想阻塞主线程，`std::async` 可以让你在后台执行这些任务。
- **并发执行**：通过 `std::async`，你可以轻松启动多个并发任务，并使用 `std::future` 来等待它们的结果。
- **懒惰计算**：使用 `std::launch::deferred`，可以推迟任务的执行，直到需要结果时才执行任务。

### 可能的陷阱

- **共享状态异常**：如果没有调用 `get()` 或 `wait()`，而 `std::future` 对象超出其生命周期，会导致任务异常终止。确保任务的结果被处理或显式忽略（通过 `future.wait()` 或 `get()`）。
- **过多线程创建**：使用 `std::launch::async` 会创建新线程，可能会造成系统开销。如果频繁调用 `std::async`，考虑线程池等方式来管理线程数量。

### 总结
`std::async` 是一种简单、优雅的方式来实现异步任务执行。它可以让程序更高效地处理并发任务，避免主线程的阻塞。使用得当时，它能提高程序的响应性和性能。

## 什么是std::promise

`std::promise` 是 C++11 标准库中的一个模板类，它和 `std::future` 搭配使用，主要用来在线程间传递数据或结果。`std::promise` 的作用是允许你在一个线程中**设置一个值**，而这个值可以在另一个线程中通过与之关联的 `std::future` 获取到。

### 关键概念

- **`std::promise`**：允许你在线程中设置一个结果（通常是异步计算的结果），并将其传递给其他线程。
- **`std::future`**：与 `std::promise` 关联，负责获取设置好的值。`std::future` 提供了线程间同步机制，确保调用 `get()` 获取结果时，其他线程已经设置了该结果。

### 主要功能

`std::promise` 可以设置以下三种状态：
1. **设置值**：通过 `set_value()` 方法来设置任务的结果。
2. **设置异常**：通过 `set_exception()` 设置一个异常，这样关联的 `std::future` 在获取值时会抛出异常。
3. **共享状态**：`std::promise` 和 `std::future` 共享一个状态，`std::promise` 设置结果或异常，`std::future` 负责获取。

### `std::promise` 和 `std::future` 的关系
当你创建一个 `std::promise` 对象时，它会自动生成一个与之关联的 `std::future` 对象。`std::future` 提供了 `get()` 函数，调用它可以等待结果的计算完成并获取到由 `std::promise` 设置的结果。

### 示例：简单的 `std::promise` 和 `std::future`

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

// 模拟一个耗时的任务
void calculateSquare(std::promise<int>&& prom, int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时操作
    prom.set_value(x * x);  // 设置结果
}

int main() {
    // 创建 promise 和对应的 future
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    // 在新线程中计算平方值，并将结果通过 promise 传回
    std::thread t(calculateSquare, std::move(prom), 6);

    std::cout << "主线程正在等待结果..." << std::endl;

    // 获取计算结果，调用 get() 会阻塞直到结果可用
    int result = fut.get();
    std::cout << "计算结果是: " << result << std::endl;

    t.join();
    return 0;
}
```

### 说明：
1. **`std::promise<int> prom`** 创建了一个可以存储 `int` 类型结果的 promise 对象。
2. `prom.get_future()` 生成了一个关联的 `std::future<int>` 对象，用于在另一个线程中获取计算结果。
3. 新线程执行 `calculateSquare` 函数，并通过 `prom.set_value()` 设置计算结果。
4. 主线程通过 `fut.get()` 阻塞并等待结果，直到新线程设置好结果后返回。

### 异常处理示例：`std::promise` 设置异常

除了设置值，`std::promise` 还可以设置异常，`std::future` 在调用 `get()` 时会抛出该异常。

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

// 任务函数，模拟错误
void calculateWithError(std::promise<int>&& prom) {
    try {
        throw std::runtime_error("计算时发生错误！");
    } catch (...) {
        prom.set_exception(std::current_exception());  // 设置异常
    }
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t(calculateWithError, std::move(prom));

    try {
        int result = fut.get();  // 这里会抛出异常
    } catch (const std::exception& e) {
        std::cerr << "捕获到异常: " << e.what() << std::endl;
    }

    t.join();
    return 0;
}
```

### 说明：
1. 使用 `std::promise::set_exception()` 可以在 promise 中设置一个异常，`std::future` 在调用 `get()` 时会抛出这个异常。
2. 在 `main()` 中，当 `fut.get()` 被调用时，`future` 通过捕获 `std::promise` 设置的异常来处理。

### 总结：
- **`std::promise` 和 `std::future` 的配合使用**：`std::promise` 用于设置值或异常，而 `std::future` 用于获取结果或者处理异常。它们之间共享同一个状态，允许不同线程之间进行同步和结果传递。
  
- **设置结果与异常的机制**：使用 `std::promise::set_value()` 设置结果，使用 `std::promise::set_exception()` 设置异常。然后，`std::future` 提供的 `get()` 方法可以获取结果或抛出异常。

- **使用场景**：`std::promise` 主要用于需要在不同线程间传递值的场景。与 `std::async` 的自动线程管理不同，`std::promise` 通常需要你自己管理线程的启动与同步。

## 什么是std::packaged_task

`std::packaged_task` 是 C++11 引入的一个模板类，主要用于将可调用对象（如函数、函数对象或 lambda 表达式）封装成一个任务，以便在将来某个时刻执行。它与 `std::future` 结合使用，可以获取任务执行的结果或异常。

### 主要特性

- **封装可调用对象**：`std::packaged_task` 允许将可调用对象（如函数或 lambda）封装起来，从而可以在后续的某个时间点执行。
- **与 `std::future` 结合使用**：每个 `std::packaged_task` 都与一个 `std::future` 对象关联，可以通过 `future.get()` 获取任务的结果。
- **线程安全**：可以在多个线程中安全地使用 `std::packaged_task`，适合用于异步任务的调度。

### 使用方式

1. **创建 `std::packaged_task`**：将可调用对象（如函数或 lambda）传递给 `std::packaged_task` 的构造函数。
2. **获取 `std::future`**：通过调用 `get_future()` 方法获取与 `packaged_task` 关联的 `std::future` 对象。
3. **执行任务**：可以在任意线程中调用 `operator()` 来执行封装的可调用对象。
4. **获取结果**：使用 `future.get()` 来获取任务的返回值或处理异常。

### 示例代码

```cpp
#include <iostream>
#include <future>
#include <thread>

// 定义一个简单的任务
int computeSquare(int x) {
    return x * x;
}

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
```

### 说明
1. **创建 `std::packaged_task`**：将 `computeSquare` 函数封装到 `packaged_task` 中，指定参数类型为 `int(int)`。
2. **获取 `std::future`**：通过 `task.get_future()` 获取一个与任务关联的 `std::future` 对象。
3. **执行任务**：在新线程中通过 `std::thread` 来执行封装的任务。
4. **获取结果**：主线程可以通过 `result.get()` 获取计算结果。

### 总结
`std::packaged_task` 是 C++ 中处理异步任务的一种灵活工具，它可以将可调用对象封装起来，使得在将来某个时刻执行任务变得简单。同时，它与 `std::future` 配合使用，允许你在异步操作中获取结果或异常。这种封装和结果获取机制使得 `std::packaged_task` 特别适合用于多线程和异步编程场景。

## std::packaged_task和std::async的区别

`std::packaged_task` 和 `std::async` 都是在 C++11 中引入的用于异步编程的工具，但它们有不同的用途和特性。以下是二者的主要区别：

### 1. **功能和角色**

- **`std::packaged_task`**:
  - **功能**：封装一个可调用对象（如函数或 lambda），并在后续某个时间点执行这个任务。
  - **角色**：作为一个可调用对象的封装器，允许在不同的线程中异步执行任务并获取结果。

- **`std::async`**:
  - **功能**：用于启动一个异步任务并返回一个 `std::future`，该任务可能会在新线程中执行。
  - **角色**：作为一个简单的异步任务启动器，内部管理线程的创建和调度。

### 2. **任务的执行**

- **`std::packaged_task`**:
  - 你需要手动执行任务。调用 `operator()` 来执行封装的可调用对象。
  - 你可以在任何线程中执行这个任务，甚至在主线程中。

- **`std::async`**:
  - 自动管理任务的执行，内部选择适当的策略来决定是立即在新线程中执行任务，还是在调用 `get()` 时延迟执行。
  - 任务的执行通常是隐式的，用户只需要关心结果的获取。

### 3. **线程管理**

- **`std::packaged_task`**:
  - 你需要自己管理线程的生命周期。使用 `std::packaged_task` 时，通常需要显式创建线程（例如使用 `std::thread`）来执行任务。

- **`std::async`**:
  - 自动处理线程的管理。用户不需要显式创建或管理线程，`std::async` 会根据需要创建线程。

### 4. **异常处理**

- **`std::packaged_task`**:
  - 如果任务抛出异常，异常会被捕获并保存在与之关联的 `std::future` 中，调用 `get()` 时会抛出该异常。

- **`std::async`**:
  - 与 `std::packaged_task` 类似，`std::async` 也会将异常捕获并存储在 `std::future` 中。

### 5. **返回值的处理**

- **`std::packaged_task`**:
  - 返回值由你显式地通过 `future.get()` 获取。

- **`std::async`**:
  - 返回值也通过 `future.get()` 获取，但用户只需调用 `std::async` 来启动任务，底层细节被隐藏。

### 示例比较

#### 使用 `std::packaged_task`

```cpp
#include <iostream>
#include <thread>
#include <future>

int computeSquare(int x) {
    return x * x;
}

int main() {
    std::packaged_task<int(int)> task(computeSquare);
    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 5);
    int value = result.get();
    std::cout << "结果是: " << value << std::endl;

    t.join();
    return 0;
}
```

#### 使用 `std::async`

```cpp
#include <iostream>
#include <future>

int computeSquare(int x) {
    return x * x;
}

int main() {
    std::future<int> result = std::async(std::launch::async, computeSquare, 5);
    int value = result.get();
    std::cout << "结果是: " << value << std::endl;

    return 0;
}
```

### 总结

- **`std::packaged_task`** 适用于需要手动管理任务执行和线程的场景，提供了更大的灵活性。
- **`std::async`** 提供了一种更简单、自动化的方式来启动异步任务，隐藏了线程管理的复杂性。

选择使用哪种工具取决于你的具体需求。如果你需要手动控制任务的执行和线程的管理，`std::packaged_task` 是一个不错的选择；如果你希望简单地启动异步任务并自动管理，`std::async` 是更合适的工具。

## packaged_task这种封装和直接把函数传递到线程中有什么区别

`std::packaged_task` 和直接将函数传递给 `std::thread` 都可以用于实现多线程编程，但它们在使用方式、功能和适用场景上有一些重要的区别。以下是这两者的主要区别：

### 1. **结果处理**

- **`std::packaged_task`**:
  - `std::packaged_task` 可以封装一个可调用对象，并将其与 `std::future` 关联。这样，你可以通过 `future.get()` 来获取任务的返回值或处理异常。
  - `std::packaged_task` 允许你在任务执行结束后获取结果，适合需要返回值的场景。

- **直接传递函数到 `std::thread`**:
  - 当你将函数传递给 `std::thread` 时，你通常不能直接获取返回值。如果函数需要返回值，你必须使用全局变量、共享变量或其他机制来共享结果。
  - 直接传递函数时，无法直接捕获异常并传递给调用者，异常处理的方式更复杂。

### 2. **灵活性**

- **`std::packaged_task`**:
  - 你可以在任意时刻调用 `std::packaged_task` 的 `operator()` 来执行封装的任务。这使得任务的执行可以在不同的上下文中进行，提供了更大的灵活性。
  - 任务可以被多次执行，但必须创建新的 `std::packaged_task` 实例。

- **直接传递函数到 `std::thread`**:
  - 一旦你创建了 `std::thread`，它会立即开始执行传递的函数。任务的执行时机是固定的，不能延迟。
  - 你不能在同一个 `std::thread` 对象中重新执行同一个函数。

### 3. **易用性**

- **`std::packaged_task`**:
  - 使用 `std::packaged_task` 会稍微复杂一些，因为你需要创建一个 `future` 并管理任务的生命周期。
  - 适用于更复杂的异步编程场景，特别是需要返回值或处理异常的情况。

- **直接传递函数到 `std::thread`**:
  - 使用 `std::thread` 更加简单直观，适合简单的任务执行。
  - 适用于仅需执行某个任务而不关心返回值或异常的场景。

### 4. **参数传递**

- **`std::packaged_task`**:
  - 你可以传递任意参数，并且可以通过 `std::ref` 传递引用。
  - 封装的可调用对象可以在不同线程中灵活执行。

- **直接传递函数到 `std::thread`**:
  - 传递参数的方式相似，但必须在创建 `std::thread` 时指定。
  - 使用 `std::ref` 传递引用时，管理起来更容易。

### 示例比较

#### 使用 `std::packaged_task`

```cpp
#include <iostream>
#include <thread>
#include <future>

int computeSquare(int x) {
    return x * x;
}

int main() {
    std::packaged_task<int(int)> task(computeSquare);
    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 5); // 执行任务
    int value = result.get(); // 获取结果
    std::cout << "结果是: " << value << std::endl;

    t.join(); // 等待线程结束
    return 0;
}
```

#### 直接传递函数到 `std::thread`

```cpp
#include <iostream>
#include <thread>

void computeSquare(int x) {
    std::cout << "平方: " << (x * x) << std::endl;
}

int main() {
    std::thread t(computeSquare, 5); // 执行任务
    t.join(); // 等待线程结束
    return 0;
}
```

### 总结

- **`std::packaged_task`** 适用于需要返回值、捕获异常或在不同上下文中执行的场景，提供了更大的灵活性和控制力。
- **直接将函数传递给 `std::thread`** 更简单，适合只需执行任务而不关心结果或异常的场景。

根据你的需求选择使用哪种方式，可以帮助你更好地实现多线程编程。