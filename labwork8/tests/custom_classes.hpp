#ifndef CUSTOM_CLASSES_HPP_
#define CUSTOM_CLASSES_HPP_

#include <memory>
#include <cstdint>

#include "test_functions.hpp"

namespace bialger {

template<typename Container>
concept Sizeable = requires(Container& c) {
  { c.size() } -> std::same_as<std::size_t>;
};

template<typename T>
concept Integral = std::is_integral<T>::value;

template<typename T>
struct LessContainer {
 public:
  bool operator()(const T& a, const T& b) const {
    return a < b;
  }

  [[nodiscard]] uint32_t GetId() const {
    return id_;
  }

 private:
  uint32_t id_ = GetRandomNumber();
};

template<>
struct LessContainer<void> {
 public:
  typedef char is_transparent;

  template<Sizeable Container, Integral Integer>
  bool operator()(const Container& a, const Integer& b) const {
    return a.size() < b;
  }

  template<Sizeable Container, Integral Integer>
  bool operator()(const Integer& b, const Container& a) const {
    return b < a.size();
  }

  template<typename U>
  bool operator()(const U& a, const U& b) const {
    return a < b;
  }

  [[nodiscard]] uint32_t GetId() const {
    return id_;
  }

 private:
  uint32_t id_ = GetRandomNumber();
};

template<typename T>
bool operator==(const LessContainer<T>& rhs, const LessContainer<T>& lhs) {
  return rhs.GetId() == lhs.GetId();
}

template<typename T>
bool operator!=(const LessContainer<T>& rhs, const LessContainer<T>& lhs) {
  return rhs.GetId() != lhs.GetId();
}

template<typename T>
struct CountingAllocator {
 public:
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  static_assert(sizeof(T) != 0, "cannot allocate incomplete types");

  CountingAllocator() : id_(GetRandomNumber()), allocations_count_(), deallocations_count_() {}

  explicit CountingAllocator(const size_type& id) : id_(id), allocations_count_(), deallocations_count_() {}

  template<typename U>
  CountingAllocator(const CountingAllocator<U>& other)
      : id_(other.GetId()),
        allocations_count_(other.GetAllocationsCount()),
        deallocations_count_(other.GetDeallocationsCount()) {}

  CountingAllocator(const CountingAllocator& other)
      : id_(other.GetId()),
        allocations_count_(other.GetAllocationsCount()),
        deallocations_count_(other.GetDeallocationsCount()) {}

  template<typename U>
  CountingAllocator& operator=(const CountingAllocator<U>& other) {
    if (this == &other) {
      return *this;
    }

    id_ = other.GetId();

    return *this;
  }

  CountingAllocator& operator=(const CountingAllocator& other) {
    if (this == &other) {
      return *this;
    }

    id_ = other.id_;
    allocations_count_ = other.allocations_count_;
    deallocations_count_ = other.deallocations_count_;

    return *this;
  }

  [[nodiscard]] T* allocate(size_t n) {
    allocations_count_ += n;
    return static_cast<T*>(malloc(n * sizeof(T)));
  }

  void deallocate(T* p, size_t n) {
    deallocations_count_ += n;
    free(p);
  }

  bool operator==(const CountingAllocator& other) const {
    return id_ == other.id_;
  }

  [[nodiscard]] size_type GetId() const {
    return id_;
  }

  bool operator!=(const CountingAllocator& other) const {
    return id_ != other.id_;
  }

  [[nodiscard]] size_type GetAllocationsCount() const {
    return allocations_count_;
  }

  [[nodiscard]] size_type GetDeallocationsCount() const {
    return deallocations_count_;
  }

 private:
  size_type id_;
  size_type allocations_count_;
  size_type deallocations_count_;
};

} // bialger

#endif //CUSTOM_CLASSES_HPP_
