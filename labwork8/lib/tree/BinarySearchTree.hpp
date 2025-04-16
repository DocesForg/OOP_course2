#ifndef LIB_TREE_BINARYSEARCHTREE_HPP_
#define LIB_TREE_BINARYSEARCHTREE_HPP_

#include <memory>
#include <cstdint>
#include <type_traits>

#include "ITemplateTree.hpp"
#include "TreeNode.hpp"
#include "TreeConcepts.hpp"
#include "PreOrder.hpp"
#include "InOrder.hpp"
#include "PostOrder.hpp"

namespace bialger {

template<typename T, typename Compare>
struct Equivalent {
  bool operator()(const T& lhs, const T& rhs) const {
    return !comparator_(lhs, rhs) && !comparator_(rhs, lhs);
  }

 protected:
  Compare comparator_{};
};

template<typename Compare>
struct Equivalent<void, Compare> {
  template<typename U, ComparableType<U, Compare> V>
  bool operator()(const U& lhs, const V& rhs) const {
    return !comparator_(lhs, rhs) && !comparator_(rhs, lhs);
  }

  template<typename U>
  bool operator()(const U& lhs, const U& rhs) const {
    return !comparator_(lhs, rhs) && !comparator_(rhs, lhs);
  }

 protected:
  Compare comparator_{};
};

template<Allocable T, typename U, Comparator<T> Less, AllocatorType Allocator>
class BinarySearchTree : public ITemplateTree<T, U> {
 public:
  using Equals = Equivalent<void, Less>;
  using TreeInterface = ITemplateTree<T, U>;
  using NodeType = TreeNode<T, U>;
  using key_type = T;
  using value_type = U;

  explicit BinarySearchTree(bool allow_duplicates = false,
                            const Less& less = Less(),
                            const Allocator& alloc = Allocator())
      : end_(nullptr), root_(nullptr), node_allocator_(alloc), allow_duplicates_(allow_duplicates), less_(less), size_{} {};

  BinarySearchTree(const BinarySearchTree& other)
      : end_(nullptr),
        root_(nullptr),
        node_allocator_(other.node_allocator_),
        allow_duplicates_(other.allow_duplicates_),
        less_(other.less_),
        size_{} {
    other.Traverse<PreOrder>([&](const NodeType* current) {
      this->Insert(current->key, current->value);
    });
  }

  BinarySearchTree& operator=(const BinarySearchTree& other) {
    if (this == &other) {
      return *this;
    }

    allow_duplicates_ = other.allow_duplicates_;
    less_ = other.less_;
    node_allocator_ = other.node_allocator_;

    Clear();
    other.Traverse<PreOrder>([&](const NodeType* current) {
      this->Insert(current->key, current->value);
    });

    return *this;
  }

  ~BinarySearchTree() {
    Clear();
  }

  BinarySearchTree(BinarySearchTree&& other) noexcept
      : end_(nullptr),
        root_(nullptr),
        node_allocator_(),
        allow_duplicates_(),
        less_(),
        size_{} {
    std::swap(end_, other.end_);
    std::swap(root_, other.root_);
    std::swap(node_allocator_, other.node_allocator_);
    std::swap(allow_duplicates_, other.allow_duplicates_);
    std::swap(less_, other.less_);
    std::swap(size_, other.size_);
  }

  BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    Clear();
    std::swap(end_, other.end_);
    std::swap(root_, other.root_);
    std::swap(node_allocator_, other.node_allocator_);
    std::swap(allow_duplicates_, other.allow_duplicates_);
    std::swap(less_, other.less_);
    std::swap(size_, other.size_);
    return *this;
  }

  void Clear() override {
    Traverse<PostOrder>([&](NodeType* current) {
      DeleteNode(current);
    });

    end_ = nullptr;
    root_ = end_;
  }

  std::pair<NodeType*, bool> Insert(const T& key, const U& value) override {
    std::pair<NodeType*, bool> result = {end_, false};
    root_ = Insert(root_, result, key, value);
    return result;
  }

  void Delete(NodeType* node) override {
    if (node == nullptr || node == end_) {
      return;
    }

    if (node->HasLeft() && node->HasRight()) {
      NodeType* min = GetMin(node->right);
      SwapNodes(node, min);
      Delete(node);
    } else if (node->HasLeft()) {
      NodeType* left = node->left;
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = left;
        left->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = left;
        left->parent = parent;
      } else {
        parent->right = left;
        left->parent = parent;
      }

      DeleteNode(node);
    } else if (node->HasRight()) {
      NodeType* right = node->right;
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = right;
        right->parent = nullptr;
      } else if (parent->left == node) {
        parent->left = right;
        right->parent = parent;
      } else {
        parent->right = right;
        right->parent = parent;
      }

      DeleteNode(node);
    } else {
      NodeType* parent = node->parent;

      if (node == root_) {
        root_ = end_;
      } else if (parent->left == node) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }

      DeleteNode(node);
    }
  }

  [[nodiscard]] NodeType* FindFirst(const T& key) const override {
    return FindFirst(root_, key);
  }

  [[nodiscard]] NodeType* FindNext(const T& key) const override {
    return FindNextByKey(root_, key);
  }

  [[nodiscard]] bool Contains(const T& key) const override {
    return FindFirst(key) != nullptr;
  }

  template<ComparableType<T, Less> K>
  [[nodiscard]] NodeType* FindFirst(const K& key) const {
    return FindFirst(root_, key);
  }

  template<ComparableType<T, Less> K>
  [[nodiscard]] NodeType* FindNext(const K& key) const {
    return FindNextByKey(root_, key);
  }

  template<ComparableType<T, Less> K>
  [[nodiscard]] bool Contains(const K& key) const {
    return FindFirst(key) != nullptr;
  }

  template<Traversable Traversal>
  void Traverse(const std::function<void(const NodeType*)>& callback) const {
    Traverse<Traversal>(root_, callback);
  }

  template<Traversable Traversal>
  void Traverse(const std::function<void(NodeType*)>& callback) {
    Traverse<Traversal>(root_, callback);
  }

  [[nodiscard]] ITreeNode* GetRoot() const override {
    return root_;
  }

  [[nodiscard]] ITreeNode* GetEnd() const override {
    return end_;
  }

  [[nodiscard]] bool AllowsDuplicates() const override {
    return allow_duplicates_;
  }

  [[nodiscard]] size_t GetSize() const override {
    return size_;
  }

  [[nodiscard]] Less GetComparator() const {
    return less_;
  }

  [[nodiscard]] Equals GetEquivalent() const {
    return equals_;
  }

  [[nodiscard]] Allocator GetAllocator() const {
    return Allocator(node_allocator_);
  }

  bool AreEqual(const T& lhs, const T& rhs) const requires EquallyComparable<T> {
    return (lhs == rhs) || equals_(lhs, rhs);
  }

  bool AreEqual(const T& lhs, const T& rhs) const {
    if (equals_(lhs, rhs)) {
      return true;
    }

    const char* lhs_bytes = &lhs;
    const char* rhs_bytes = &rhs;
    size_t size = sizeof(T);

    for (size_t i = 0; i < size; ++i) {
      if (lhs_bytes[i] != rhs_bytes[i]) {
        return false;
      }
    }

    return true;
  }

 protected:
  using NodeAllocatorType = typename std::allocator_traits<Allocator>::template rebind_alloc<NodeType>;
  using NodeAllocatorTraits = std::allocator_traits<NodeAllocatorType>;

  bool allow_duplicates_;
  size_t size_;
  NodeType* end_;
  NodeType* root_;
  NodeAllocatorType node_allocator_;
  Less less_;
  Equals equals_;

  NodeType* CreateNode(const T& key, const U& value) {
    NodeType* new_node = NodeAllocatorTraits::allocate(node_allocator_, 1);
    NodeAllocatorTraits::construct(node_allocator_, new_node, key, value);
    ++size_;

    return new_node;
  }

  void DeleteNode(NodeType* node) {
    NodeAllocatorTraits::destroy(node_allocator_, node);
    NodeAllocatorTraits::deallocate(node_allocator_, node, 1);
    --size_;
  }

  virtual NodeType* Insert(NodeType* node, std::pair<NodeType*, bool>& result, const T& key, const U& value) {
    if (node == nullptr) {
      NodeType* new_node = CreateNode(key, value);
      result.first = new_node;
      result.second = true;

      return new_node;
    }

    if (AreEqual(key, node->key) && !allow_duplicates_) {
      node->value = value;
      result.first = node;
      result.second = false;
    } else if ((less_(key, node->key)) || (allow_duplicates_ && AreEqual(key, node->key))) {
      node->left = Insert(node->left, result, key, value);
      node->left->parent = node;
    } else if (less_(node->key, key)) {
      node->right = Insert(node->right, result, key, value);
      node->right->parent = node;
    }

    return node;
  }

  NodeType* FindFirst(NodeType* node, const T& key) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (AreEqual(key, node->key)) {
      return node;
    }

    if (less_(key, node->key)) {
      return FindFirst(node->left, key);
    } else if (less_(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  template<ComparableType<T, Less> K>
  NodeType* FindFirst(NodeType* node, const K& key) const {
    if (node == nullptr) {
      return nullptr;
    }

    if (equals_(key, node->key)) {
      return node;
    }

    if (less_(key, node->key)) {
      return FindFirst(node->left, key);
    } else if (less_(node->key, key)) {
      return FindFirst(node->right, key);
    }

    return node;
  }

  NodeType* FindNextByKey(NodeType* node, const T& key) const {
    NodeType* next = nullptr;

    while (node != nullptr) {
      if (AreEqual(key, node->key)) {
        node = node->right;
      } else if (less_(key, node->key) || (allow_duplicates_ && AreEqual(key, node->key))) {
        if (next == nullptr || less_(node->key, next->key)) {
          next = node;
        }

        node = node->left;
      } else {
        node = node->right;
      }
    }

    return next;
  }

  template<ComparableType<T, Less> K>
  NodeType* FindNextByKey(NodeType* node, const K& key) const {
    NodeType* next = nullptr;

    while (node != nullptr) {
      if (equals_(key, node->key)) {
        node = node->right;
      } else if (less_(key, node->key) || (allow_duplicates_ && equals_(key, node->key))) {
        if (next == nullptr || less_(node->key, next->key)) {
          next = node;
        }

        node = node->left;
      } else {
        node = node->right;
      }
    }

    return next;
  }

  void SwapNodes(NodeType* first, NodeType* second) {
    if (first == nullptr || second == nullptr || first == second) {
      return;
    }

    if (first->parent == nullptr) {
      root_ = second;
    } else if (first == first->parent->left) {
      first->parent->left = second;
    } else {
      first->parent->right = second;
    }

    if (second->parent == nullptr) {
      root_ = first;
    } else if (second == second->parent->left) {
      second->parent->left = first;
    } else {
      second->parent->right = first;
    }

    std::swap(first->left, second->left);
    std::swap(first->right, second->right);
    std::swap(first->parent, second->parent);

    if (first->HasLeft()) {
      first->left->parent = first;
    }

    if (first->HasRight()) {
      first->right->parent = first;
    }

    if (second->HasLeft()) {
      second->left->parent = second;
    }

    if (second->HasRight()) {
      second->right->parent = second;
    }
  }

  NodeType* GetMin(NodeType* current) {
    if (current == nullptr) {
      return current;
    }

    while (current->HasLeft()) {
      current = current->left;
    }

    return current;
  }

  NodeType* GetMax(NodeType* current) {
    if (current == nullptr) {
      return current;
    }

    while (current->HasRight()) {
      current = current->right;
    }

    return current;
  }

  template<Traversable Traversal>
  void Traverse(NodeType* node, const std::function<void(NodeType*)>& callback) {
    if (node == nullptr) {
      return;
    }

    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      callback(node);
    }

    Traverse<Traversal>(node->left, callback);

    if constexpr (std::is_same<Traversal, InOrder>::value) {
      callback(node);
    }

    Traverse<Traversal>(node->right, callback);

    if constexpr (std::is_same<Traversal, PostOrder>::value) {
      callback(node);
    }
  }

  template<Traversable Traversal>
  void Traverse(const NodeType* node, const std::function<void(const NodeType*)>& callback) const {
    if (node == nullptr) {
      return;
    }

    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      callback(node);
    }

    Traverse<Traversal>(node->left, callback);

    if constexpr (std::is_same<Traversal, InOrder>::value) {
      callback(node);
    }

    Traverse<Traversal>(node->right, callback);

    if constexpr (std::is_same<Traversal, PostOrder>::value) {
      callback(node);
    }
  }
};

} // bialger

#endif //LIB_TREE_BINARYSEARCHTREE_HPP_
