#ifndef LIB_BST_BSTITERATOR_HPP_
#define LIB_BST_BSTITERATOR_HPP_

#include <iostream>

#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"
#include "BstConcepts.hpp"

namespace bialger {

template<Allocable T, Comparator<T> Compare, AllocatorType Allocator>
class BST;

template<Allocable T, Comparator<T> Compare, AllocatorType Allocator, bool is_reversed = false>
class BstIterator {
 public:
  friend class BST<T, Compare, Allocator>;

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;

 private:
  using TreeInterface = BST<T, Compare, Allocator>::TreeInterface;
  using NodeType = TreeInterface::NodeType;

 public:

  BstIterator() : current_(nullptr), traversal_(nullptr), end_(nullptr) {}

  explicit BstIterator(const ITraversal& traversal) : traversal_(&traversal), end_(traversal.GetEnd()) {
    current_ = dynamic_cast<NodeType*>(is_reversed ? traversal_->GetLast() : traversal_->GetFirst());
  }

  BstIterator(ITreeNode* node, const ITraversal& traversal) : traversal_(&traversal), end_(traversal.GetEnd()) {
    current_ = dynamic_cast<NodeType*>(node);
  }

  BstIterator(const BstIterator& other)
      : current_(other.current_), traversal_(other.traversal_), end_(other.traversal_->GetEnd()) {}

  BstIterator& operator=(const BstIterator& other) {
    if (this == &other) {
      return *this;
    }

    if (traversal_ != other.traversal_) {
      throw std::invalid_argument("Can`t assign iterator with different traversals.");
    }

    current_ = other.current_;
    return *this;
  }

  BstIterator(BstIterator&& other) noexcept
      : current_(nullptr), traversal_(nullptr), end_(nullptr) {
    std::swap(current_, other.current_);
    std::swap(traversal_, other.traversal_);
    std::swap(end_, other.end_);
  }

  BstIterator& operator=(BstIterator&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    std::swap(current_, other.current_);
    std::swap(traversal_, other.traversal_);
    std::swap(end_, other.end_);
    return *this;
  }

  const_reference operator*() const {
    if (current_ == end_) {
      throw std::out_of_range("Bad dereference attempt: *BST::end()");
    }

    return current_->key;
  }

  const_pointer operator->() const {
    if (current_ == end_) {
      throw std::out_of_range("Bad dereference attempt: BST::end()->");
    }

    return &current_->key;
  }

  BstIterator& operator++() {
    if (current_ == end_) {
      throw std::out_of_range("Bad incrementation attempt: ++BST::end()");
    }

    ITreeNode* next = is_reversed ? traversal_->GetPredecessor(current_) : traversal_->GetSuccessor(current_);
    current_ = dynamic_cast<NodeType*>(next);

    return *this;
  }

  [[nodiscard]] BstIterator operator++(int) {
    if (current_ == end_) {
      throw std::out_of_range("Bad incrementation attempt: ++BST::end()");
    }

    BstIterator tmp = *this;
    ++*this;
    return tmp;
  }

  BstIterator& operator--() {
    ITreeNode* next = is_reversed ? traversal_->GetSuccessor(current_) : traversal_->GetPredecessor(current_);
    current_ = dynamic_cast<NodeType*>(next);
    return *this;
  }

  [[nodiscard]] BstIterator operator--(int) {
    BstIterator tmp = *this;
    --*this;
    return tmp;
  }

  [[nodiscard]] BstIterator next() {
    BstIterator tmp = *this;
    ++tmp;
    return tmp;
  }

  [[nodiscard]] BstIterator prev() {
    BstIterator tmp = *this;
    --tmp;
    return tmp;
  }

  bool operator==(const BstIterator& other) const {
    return current_ == other.current_ && traversal_ == other.traversal_;
  }

  bool operator!=(const BstIterator& other) const {
    return !(*this == other);
  }

 private:
  NodeType* current_;
  ITreeNode* end_;
  const ITraversal* traversal_;
};

} // bialger

#endif //LIB_BST_BSTITERATOR_HPP_
