#ifndef LIB_TREE_PREORDER_HPP_
#define LIB_TREE_PREORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class PreOrder : public ITraversal {
 public:
  PreOrder() = delete;

  explicit PreOrder(const ITree& tree);

  PreOrder(const PreOrder& other);
  PreOrder& operator=(const PreOrder& other);
  ~PreOrder() override = default;
  PreOrder(PreOrder&& other) noexcept;
  PreOrder& operator=(PreOrder&& other) noexcept;

  [[nodiscard]] ITreeNode* GetFirst() const override;
  [[nodiscard]] ITreeNode* GetLast() const override;
  [[nodiscard]] ITreeNode* GetEnd() const override;
  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) const override;
  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) const override;

 protected:
  const ITree* tree_;
};

} // bialger

#endif //LIB_TREE_PREORDER_HPP_
