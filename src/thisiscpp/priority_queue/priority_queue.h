#include <cassert>
#include <functional>
#include <vector>

template <typename T>
class MyPriorityQueue {
 public:
  using CmpFunc = std::function<bool(const T&, const T&)>;

  /**
   * @brief Construct a new My Priority Queue object
   *
   * @param capacity
   * @param cmp
   */
  MyPriorityQueue(int capacity, CmpFunc cmp)
      : heap_(capacity + 1), size_(0), cmp_(cmp) {}

  /**
   * @brief Return the PQ element size
   *
   * @return int
   */
  int size() const { return size_; }

  /**
   * @brief Check if the PQ is empty
   *
   * @return true
   * @return false
   */
  bool isEmpty() const { return size_ == 0; }

  /**
   * @brief Calculate the parent index of the node
   *
   * @param node
   * @return int
   */
  int parent(int node) { return node / 2; }

  /**
   * @brief Calculate the left child index of the node
   *
   * @param node
   * @return int
   */
  int left(int node) { return 2 * node; }

  /**
   * @brief Calculate the right child index of the node
   *
   * @param node
   * @return int
   */
  int right(int node) { return 2 * node + 1; }

  /**
   * @brief Swap the two elements in the PQ
   *
   * @param i
   * @param j
   */
  void swap(int i, int j) {
    T temp = heap_[i];
    heap_[i] = heap_[j];
    heap_[j] = temp;
  }

  /**
   * @brief Pop the top element of the PQ
   *
   * @return T
   */
  T peek() {
    if (isEmpty()) {
      throw std::out_of_range("Priority queue underflow");
    }
    return heap_[1];
  }

  /**
   * @brief Resize the PQ
   *
   * @param capacity
   */
  void resize(int capacity) {
    assert(capacity > size_);

    std::vector<T> temp(capacity);
    for (int i = 1; i <= size_; i++) {
      temp[i] = heap_[i];
    }
    heap_ = temp;
  }

  /**
   * @brief Swim the element if it is smaller than its parent
   *
   * @param k
   */
  void swim(int k) {
    while (k > 1 && cmp_(heap_[parent(k)], heap_[k])) {
      swap(parent(k), k);
      k = parent(k);
    }
  }

  /**
   * @brief Sink the element if it is larger than its children
   *
   * @param k
   */
  void push(T val) {
    if (size_ == heap_.size() - 1) {
      resize(2 * heap_.size());
    }
    heap_[++size_] = val;
    swim(size_);
  }

  /**
   * @brief Sink the element if it is larger than its children
   *
   * @param k
   */
  void sink(int k) {
    while (left(k) <= size_) {
      int j = left(k);
      if (j < size_ && cmp_(heap_[j], heap_[j + 1])) {
        j++;
      }
      if (!cmp_(heap_[k], heap_[j])) {
        break;
      }
      swap(k, j);
      k = j;
    }
  }

  /**
   * @brief Pop the top element of the PQ
   *
   * @return T
   */
  T pop() {
    if (isEmpty()) {
      throw std::out_of_range("Priority queue underflow");
    }
    T result = heap_[1];
    swap(1, size_--);
    sink(1);
    heap_[size_ + 1] = T();
    if ((size_ > 0) && (size_ == (heap_.size() - 1) / 4)) {
      resize(heap_.size() / 2);
    }
    return result;
  }

 private:
  std::vector<T> heap_;
  int size_;
  CmpFunc cmp_;
};
