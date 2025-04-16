#ifndef LIB_BST_BST_CONCEPTS_HPP_
#define LIB_BST_BST_CONCEPTS_HPP_

#include <type_traits>
#include <cstdint>

namespace bialger {

template<typename Iter, typename T>
concept InputIterator = requires(Iter it, T& t) {
  t = *it;
  ++it;
};

template<typename Container, typename T>
concept Iterable = requires(Container& c, T& t) {
  { c.cbegin() } -> InputIterator<T>;
  { c.cend() } -> InputIterator<T>;
};

template<typename Pred, typename T>
concept Predicate = requires(Pred& p, T& t) {
  { p(t) } -> std::same_as<bool>;
};

} // bialger

#endif //LIB_BST_BST_CONCEPTS_HPP_
