#ifndef LIB_TREE_ITEMPLATETREE_HPP_
#define LIB_TREE_ITEMPLATETREE_HPP_

#include <functional>

#include "TreeNode.hpp"
#include "ITree.hpp"

namespace bialger {

template <typename T, typename U>
class ITemplateTree : public ITree {
 public:
  using NodeType = TreeNode<T, U>;
  using key_type = T;
  using value_type = U;
  
  ~ITemplateTree() override = default;

  virtual void Clear() = 0;

  virtual std::pair<NodeType*, bool> Insert(const T& key, const U& value) = 0;
  virtual void Delete(NodeType* node) = 0;
  [[nodiscard]] virtual NodeType* FindFirst(const T& key) const = 0;
  [[nodiscard]] virtual NodeType* FindNext(const T& key) const = 0;
  [[nodiscard]] virtual bool Contains(const T& key) const  = 0;
};

} // bialger

#endif //LIB_TREE_ITEMPLATETREE_HPP_
