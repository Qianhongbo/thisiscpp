#include <algorithm>
#include <iostream>
#include <utility>

class MyClass {
 public:
  MyClass() : size_(0), data_(nullptr) {};

  MyClass(int s) : size_(s), data_(new int[s]) {
    for (int i = 0; i < size_; ++i) {
      data_[i] = 0;
    }
  }

  ~MyClass() {
    if (data_ != nullptr) {
      delete[] data_;
    }
  }

  MyClass(const MyClass& other) : size_(other.size_), data_(new int[size_]) {
    std::copy(other.data_, other.data_ + size_, data_);
  }

  MyClass(MyClass&& other) noexcept
      : size_(std::exchange(other.size_, 0)),
        data_(std::exchange(other.data_, nullptr)) {}

  MyClass& operator=(const MyClass& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      data_ = new int[size_];
      std::copy(other.data_, other.data_ + size_, data_);
    }
    return *this;
  }

  MyClass& operator=(MyClass&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      size_ = std::exchange(other.size_, 0);
      data_ = std::exchange(other.data_, nullptr);
    }
    return *this;
  }

  int size() const { return size_; }

  int& operator[](int index) { return data_[index]; }

 private:
  int size_;
  int* data_;
};