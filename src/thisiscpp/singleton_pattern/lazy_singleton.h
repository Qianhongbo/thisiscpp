#include <iostream>
#include <mutex>

class LazySingleton {
 public:
  static LazySingleton* getInstance(bool create_if_needed = true) {
    static LazySingleton* instance = nullptr;
    if (!instance && create_if_needed) {
      static std::once_flag flag;
      std::call_once(flag,
                     [&]() { instance = new (std::nothrow) LazySingleton(); });
    }
    return instance;
  }

  void printMessage() {
    std::cout << "LazySingleton::printMessage()" << std::endl;
  }

 private:
  LazySingleton() {}
  LazySingleton(const LazySingleton&) = delete;
  LazySingleton& operator=(const LazySingleton&) = delete;
};