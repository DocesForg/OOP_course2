#ifndef LIB_TREE_INORDER_HPP_
#define LIB_TREE_INORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class InOrder : public ITraversal {
 public:
  InOrder() = delete;

  explicit InOrder(const ITree& tree);

  InOrder(const InOrder& other);
  InOrder& operator=(const InOrder& other);
  ~InOrder() override = default;
  InOrder(InOrder&& other) noexcept;
  InOrder& operator=(InOrder&& other) noexcept;

  [[nodiscard]] ITreeNode* GetFirst() const override;
  [[nodiscard]] ITreeNode* GetLast() const override;
  [[nodiscard]] ITreeNode* GetEnd() const override;
  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) const override;
  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) const override;

 protected:
  const ITree* tree_;

  [[nodiscard]] static ITreeNode* GetMin(ITreeNode* current);
  [[nodiscard]] static ITreeNode* GetMax(ITreeNode* current);
};

} // bialger

#endif //LIB_TREE_INORDER_HPP_
