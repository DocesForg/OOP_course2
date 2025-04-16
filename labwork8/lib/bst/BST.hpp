#ifndef LIB_BST_BST_HPP_
#define LIB_BST_BST_HPP_

#include <limits>

#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

#include "BstIterator.hpp"
#include "BstConcepts.hpp"

namespace bialger {

template<Allocable T, Comparator<T> Compare = std::less<>, AllocatorType Allocator = std::allocator<T>>
class BST {
  static_assert(std::is_same<typename std::remove_cv<T>::type, T>::value,
                "bialger::BST must have a non-const, non-volatile value_type");

 private:
  using TreeType = BinarySearchTree<T, const T*, Compare, Allocator>;
  using Equals = TreeType::Equals;
  using NodeType = TreeType::NodeType;
  using DefaultTraversal = InOrder;

 public:
  using key_type = T;
  using value_type = key_type;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using iterator = BstIterator<T, Compare, Allocator>;
  using const_iterator = BstIterator<T, Compare, Allocator>;
  using reverse_iterator = BstIterator<T, Compare, Allocator, true>;
  using const_reverse_iterator = BstIterator<T, Compare, Allocator, true>;
  using allocator_type = Allocator;
  using key_allocator = Allocator;
  using key_compare = Compare;
  using value_compare = Compare;
  using TreeInterface = TreeType::TreeInterface;

  BST() : tree_(),
          pre_order_(tree_),
          in_order_(tree_),
          post_order_(tree_),
          allocator_(),
          key_compare_(),
          value_compare_() {}

  BST(const BST& other) : tree_(other.tree_),
                          pre_order_(tree_),
                          in_order_(tree_),
                          post_order_(tree_),
                          allocator_(other.allocator_),
                          key_compare_(other.key_compare_),
                          value_compare_(other.value_compare_) {}

  BST(BST&& other) noexcept: tree_(),
                             pre_order_(tree_),
                             in_order_(tree_),
                             post_order_(tree_),
                             allocator_(),
                             key_compare_(),
                             value_compare_() {
    std::swap(tree_, other.tree_);
    std::swap(allocator_, other.allocator_);
    std::swap(key_compare_, other.key_compare_);
    std::swap(value_compare_, other.value_compare_);
  }

  explicit BST(const Compare& comp, const Allocator& alloc = Allocator()) : tree_(false, comp, alloc),
                                                                            pre_order_(tree_),
                                                                            in_order_(tree_),
                                                                            post_order_(tree_),
                                                                            allocator_(alloc),
                                                                            key_compare_(comp),
                                                                            value_compare_(comp) {}

  explicit BST(const Allocator& alloc) : BST(Compare(), alloc) {}

  BST(const std::initializer_list<T>& list,
      const Compare& comp = Compare(),
      const Allocator& alloc = Allocator()) : tree_(false, comp, alloc),
                                              pre_order_(tree_),
                                              in_order_(tree_),
                                              post_order_(tree_),
                                              allocator_(alloc),
                                              key_compare_(comp),
                                              value_compare_(comp) {
    auto it = list.begin();
    auto end = list.end();

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  BST(std::initializer_list<value_type> list, const Allocator& alloc) : BST(list, Compare(), alloc) {
    auto it = list.begin();
    auto end = list.end();

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  template<InputIterator<T> InputIt>
  BST(InputIt first, InputIt last,
      const Compare& comp = Compare(),
      const Allocator& alloc = Allocator()) : tree_(false, comp, alloc),
                                              pre_order_(tree_),
                                              in_order_(tree_),
                                              post_order_(tree_),
                                              allocator_(alloc),
                                              key_compare_(comp),
                                              value_compare_(comp) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  template<InputIterator<T> InputIt>
  BST(InputIt first, InputIt last, const Allocator& alloc) : BST(first, last, Compare(), alloc) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  BST& operator=(const std::initializer_list<T>& list) {
    clear();
    auto it = list.begin();
    auto end = list.end();

    for (; it != end; ++it) {
      insert(*it);
    }

    return *this;
  }

  BST& operator=(const BST& other) {
    if (this == &other) {
      return *this;
    }

    tree_ = other.tree_;
    allocator_ = other.allocator_;
    key_compare_ = other.key_compare_;
    value_compare_ = other.value_compare_;
    return *this;
  }

  BST& operator=(BST&& other) noexcept {
    if (this == &other) {
      return *this;
    }

    std::swap(tree_, other.tree_);
    std::swap(allocator_, other.allocator_);
    std::swap(key_compare_, other.key_compare_);
    std::swap(value_compare_, other.value_compare_);
    return *this;
  }

  ~BST() {
    tree_.Clear();
  }

  void clear() {
    tree_.Clear();
  }

  template<Traversable Traversal = DefaultTraversal>
  iterator begin() const {
    return iterator(GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal>
  iterator end() const {
    return iterator(tree_.GetEnd(), GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal>
  const_iterator cbegin() const {
    return begin<Traversal>();
  }

  template<Traversable Traversal = DefaultTraversal>
  const_iterator cend() const {
    return end<Traversal>();
  }

  template<Traversable Traversal = DefaultTraversal>
  reverse_iterator rbegin() const {
    return reverse_iterator(GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal>
  reverse_iterator rend() const {
    return reverse_iterator(tree_.GetEnd(), GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal>
  const_reverse_iterator crbegin() const {
    return rbegin<Traversal>();
  }

  template<Traversable Traversal = DefaultTraversal>
  const_reverse_iterator crend() const {
    return rend<Traversal>();
  }

  template<Traversable Traversal = DefaultTraversal>
  std::pair<iterator, bool> insert(const T& key) {
    if (tree_.GetComparator()(key, key)) {
      throw std::invalid_argument("Incorrect template parameter Compare: is not strict");
    }

    auto result = tree_.Insert(key, &key);
    iterator it = iterator(result.first, GetTraversalLink<Traversal>());
    return {it, result.second};
  }

  template<Traversable Traversal = DefaultTraversal>
  iterator insert(iterator pos, const T& key) {
    return insert<Traversal>(key).first;
  }

  template<InputIterator<T> InputIt>
  void insert(InputIt first, InputIt last) {
    if (first == last) {
      return;
    }

    if (tree_.GetComparator()(*first, *first)) {
      throw std::invalid_argument("Incorrect template parameter Compare: is not strict");
    }

    for (; first != last; ++first) {
      insert(*first);
    }
  }

  template<Iterable<T> Container>
  void insert(const Container& other) {
    insert(other.cbegin(), other.cend());
  }

  void insert(const std::initializer_list<T>& list) {
    auto it = list.begin();
    auto end = list.end();

    if (it == end) {
      return;
    }

    if (tree_.GetComparator()(*it, *it)) {
      throw std::invalid_argument("Incorrect template parameter Compare: is not strict");
    }

    for (; it != end; ++it) {
      insert(*it);
    }
  }

  iterator erase(iterator pos) {
    iterator next = pos.next();
    tree_.Delete(pos.current_);
    return next;
  }

  iterator erase(const_iterator first, const_iterator last) {
    while (first != last) {
      first = erase(first);
    }

    return last;
  }

  size_type erase(const T& key) {
    size_type counter = 0;

    for (auto it = find(key); it != end(); it = find(key)) {
      erase(it);
      ++counter;
    }

    return counter;
  }

  template<Traversable Traversal = DefaultTraversal>
  iterator find(const T& key) {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal>
  const_iterator find(const T& key) const {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal, ComparableType<T, Compare> K>
  iterator find(const K& key) {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  template<Traversable Traversal = DefaultTraversal, ComparableType<T, Compare> K>
  const_iterator find(const K& key) const {
    return iterator(tree_.FindFirst(key), GetTraversalLink<Traversal>());
  }

  size_type count(const T& key) const {
    return (find(key) == cend()) ? 0 : 1;
  }

  template<ComparableType<T, Compare> K>
  size_type count(const K& key) const {
    return (find(key) == cend()) ? 0 : 1;
  }

  bool contains(const T& key) const {
    return find(key) != cend();
  }

  template<ComparableType<T, Compare> K>
  bool contains(const K& key) const {
    return find(key) != cend();
  }

  iterator lower_bound(const T& key) {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  const_iterator lower_bound(const T& key) const {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  template<ComparableType<T, Compare> K>
  iterator lower_bound(const K& key) {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  template<ComparableType<T, Compare> K>
  const_iterator lower_bound(const K& key) const {
    NodeType* first = tree_.FindFirst(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return iterator(tree_.FindNext(key), traversal);
    }

    return iterator(first, traversal);
  }

  iterator upper_bound(const T& key) {
    return iterator(tree_.FindNext(key), in_order_);
  }

  const_iterator upper_bound(const T& key) const {
    return const_iterator(tree_.FindNext(key), in_order_);
  }

  template<ComparableType<T, Compare> K>
  iterator upper_bound(const K& key) {
    return iterator(tree_.FindNext(key), in_order_);
  }

  template<ComparableType<T, Compare> K>
  const_iterator upper_bound(const K& key) const {
    return const_iterator(tree_.FindNext(key), in_order_);
  }

  std::pair<iterator, iterator> equal_range(const T& key) {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return {iterator(next, traversal), iterator(next, traversal)};
    }

    return {iterator(first, traversal), iterator(next, traversal)};
  }

  std::pair<const_iterator, const_iterator> equal_range(const T& key) const {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return {const_iterator(next, traversal), const_iterator(next, traversal)};
    }

    return {const_iterator(first, traversal), const_iterator(next, traversal)};
  }

  template<ComparableType<T, Compare> K>
  std::pair<iterator, iterator> equal_range(const K& key) {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return {iterator(next, traversal), iterator(next, traversal)};
    }

    return {iterator(first, traversal), iterator(next, traversal)};
  }

  template<ComparableType<T, Compare> K>
  std::pair<const_iterator, const_iterator> equal_range(const K& key) const {
    NodeType* first = tree_.FindFirst(key);
    NodeType* next = tree_.FindNext(key);
    const ITraversal& traversal = in_order_;

    if (first == tree_.GetEnd()) {
      return {const_iterator(next, traversal), const_iterator(next, traversal)};
    }

    return {const_iterator(first, traversal), const_iterator(next, traversal)};
  }

  bool operator==(const BST& other) const {
    if (tree_.GetSize() != other.tree_.GetSize()) {
      return false;
    }

    for (const_iterator this_it = cbegin(), other_it = other.cbegin();
         this_it != cend() && other_it != cend();
         ++this_it, ++other_it) {
      if (*this_it != *other_it) {
        return false;
      }
    }

    return true;
  }

  auto operator<=>(const BST& other) const {
    for (const_iterator this_it = cbegin(), other_it = other.cbegin();
         this_it != cend() && other_it != cend();
         ++this_it, ++other_it) {
      if (*this_it < *other_it) {
        return std::strong_ordering::less;
      } else if (*this_it > *other_it) {
        return std::strong_ordering::greater;
      }
    }

    if (tree_.GetSize() < other.tree_.GetSize()) {
      return std::strong_ordering::less;
    }

    if (tree_.GetSize() > other.tree_.GetSize()) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equivalent;
  }

  [[nodiscard]] size_type size() const {
    return tree_.GetSize();
  }

  [[nodiscard]] bool empty() const {
    return tree_.GetSize() == 0;
  }

  static difference_type max_size() {
    return std::numeric_limits<difference_type>::max();
  }

  void swap(BST& other) {
    std::swap(tree_, other.tree_);
    std::swap(allocator_, other.allocator_);
    std::swap(key_compare_, other.key_compare_);
    std::swap(value_compare_, other.value_compare_);
  }

  key_allocator get_allocator() const {
    return tree_.GetAllocator();
  }

  key_compare key_comp() const {
    return tree_.GetComparator();
  }

  value_compare value_comp() const {
    return tree_.GetComparator();
  }

  Equals key_eq() const {
    return tree_.GetEquivalent();
  }

  template<Traversable Traversal = InOrder>
  std::ostream& PrintToStream(std::ostream& os) {
    tree_.template Traverse<Traversal>([&](const NodeType* current) -> void {
      os << current->key << ' ';
    });

    return os;
  }

 private:
  TreeType tree_;
  PreOrder pre_order_;
  InOrder in_order_;
  PostOrder post_order_;
  allocator_type allocator_;
  key_compare key_compare_;
  value_compare value_compare_;

  template<Traversable Traversal>
  [[nodiscard]] const ITraversal& GetTraversalLink() const {
    if constexpr (std::is_same<Traversal, PreOrder>::value) {
      return pre_order_;
    } else if (std::is_same<Traversal, InOrder>::value) {
      return in_order_;
    } else {
      return post_order_;
    }
  }
};

template<Allocable T, Comparator<T> Compare = std::less<>, AllocatorType Allocator = std::allocator<T>>
void swap(BST<T, Compare, Allocator>& first, BST<T, Compare, Allocator>& second) {
  first.swap(second);
}

template<Allocable Key, Comparator<Key> Compare, AllocatorType Alloc, Predicate<Key> Pred>
typename BST<Key, Compare, Alloc>::size_type erase_if(BST<Key, Compare, Alloc>& c, Pred pred) {
  auto old_size = c.size();

  for (auto first = c.begin(), last = c.end(); first != last;) {
    if (pred(*first)) {
      first = c.erase(first);
    } else {
      ++first;
    }
  }

  return old_size - c.size();
}

using CharSet = BST<char>;
static_assert(Iterable<CharSet, char>, "BST is not iterable.");
static_assert(InputIterator<CharSet::iterator, char>, "BST iterator is not an input iterator");
static_assert(std::bidirectional_iterator<CharSet::iterator>, "BST iterator is not an bidirectional iterator");
static_assert(InputIterator<CharSet::reverse_iterator, char>, "BST reversed iterator is not an input iterator");
static_assert(std::bidirectional_iterator<CharSet::reverse_iterator>,
              "BST reversed iterator is not an bidirectional iterator");

} // bialger

#endif //LIB_BST_BST_HPP_
