#include <vector>

/**
 * [a, b, c, d, e, f, g]
 *  0  1  2  3  4  5  6
 *
 * parent(i) = i / 2
 * left(i) = 2 * i
 * right(i) = 2 * i + 1
 *
 */

class SimpleMinPQ {
 private:
  std::vector<int> heap_;
  int size_;

 public:
  /**
   * @brief Construct a new Simple Min PriorityQueue object
   *
   * @param capacity
   */
  explicit SimpleMinPQ(int capacity) : heap_(capacity + 1), size_(0) {}

  /**
   * @brief Return the PQ element size
   *
   * @return int
   */
  int size() const { return size_; }

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
   * @brief Peek the top element of the PQ
   *
   * @return int
   */
  int peek() { return heap_[1]; }

  /**
   * @brief Swim the element if it is smaller than its parent
   *
   * @param k
   */
  void swim(int k) {
    while (k > 1 && heap_[parent(k)] > heap_[k]) {
      std::swap(heap_[parent(k)], heap_[k]);
      k = parent(k);
    }
  }

  /**
   * @brief Push the element to the PQ
   *
   * @param value
   */
  void push(const int& value) {
    heap_[++size_] = value;
    swim(size_);
  }

  /**
   * @brief Sink the element if it is larger than its children
   *
   * @param x
   */
  void sink(int x) {
    while (left(x) <= size_ || right(x) <= size_) {
      int min_val = x;
      if (left(x) <= size_ && heap_[left(x)] < heap_[min_val]) {
        min_val = left(x);
      }
      if (right(x) <= size_ && heap_[right(x)] < heap_[min_val]) {
        min_val = right(x);
      }
      if (min_val == x) {
        break;
      }
      std::swap(heap_[x], heap_[min_val]);
      x = min_val;
    }
  }

  /**
   * @brief Pop the top element of the PQ
   *
   * @return int
   */
  int pop() {
    int top = heap_[1];
    std::swap(heap_[1], heap_[size_--]);
    sink(1);
    return top;
  }
};
