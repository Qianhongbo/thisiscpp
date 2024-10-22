#include <iostream>

class EagerSingleton {
 public:
  static EagerSingleton* getInstance() {
    static EagerSingleton instance;
    return &instance;
  }

  void printMessage() {
    std::cout << "EagerSingleton::printMessage()" << std::endl;
  }

 private:
  EagerSingleton() {}
  EagerSingleton(const EagerSingleton&) = delete;
  EagerSingleton& operator=(const EagerSingleton&) = delete;
};