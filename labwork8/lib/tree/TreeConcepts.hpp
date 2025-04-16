#ifndef LIB_TREE_TREE_CONCEPTS_HPP_
#define LIB_TREE_TREE_CONCEPTS_HPP_

#include <type_traits>

#include "lib/tree/ITraversal.hpp"

namespace bialger {

template<typename Traversal>
concept Traversable = std::is_base_of<ITraversal, Traversal>::value;

template<typename Compare, typename T>
concept Comparator = requires(Compare& comp, T& t, T& u) {
  { comp(t, u) } -> std::same_as<bool>;
};

template<typename K, typename T, typename Compare>
concept ComparableType = requires(Compare& comp, T& t, K& k) {
  typename Compare::is_transparent;
  { comp(k, t) } -> std::same_as<bool>;
  { comp(t, k) } -> std::same_as<bool>;
};

template<typename T>
concept Allocable = sizeof(T) != 0;

template<typename T>
concept EquallyComparable = requires(T& t, T& u) {
  { t = u } -> std::same_as<T&>;
};

template<typename Allocator>
concept AllocatorType = requires(Allocator& alloc) {
  typename Allocator::value_type;
  { alloc.allocate(1) } -> std::same_as<typename Allocator::value_type*>;
  { alloc.deallocate(alloc.allocate(1), 1) } -> std::same_as<void>;
};

} // bialger

#endif //LIB_TREE_TREE_CONCEPTS_HPP_
