#ifndef LIB_TREE_ITRAVERSAL_HPP_
#define LIB_TREE_ITRAVERSAL_HPP_

#include "ITreeNode.hpp"

namespace bialger {

class ITraversal {
 public:
  virtual ~ITraversal() = default;

  [[nodiscard]] virtual ITreeNode* GetFirst() const = 0;
  [[nodiscard]] virtual ITreeNode* GetLast() const = 0;
  [[nodiscard]] virtual ITreeNode* GetEnd() const = 0;
  [[nodiscard]] virtual ITreeNode* GetPredecessor(ITreeNode* current) const = 0;
  [[nodiscard]] virtual ITreeNode* GetSuccessor(ITreeNode* current) const = 0;
};

} // bialger

#endif //LIB_TREE_ITRAVERSAL_HPP_
