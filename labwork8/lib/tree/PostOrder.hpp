#ifndef LIB_TREE_POSTORDER_HPP_
#define LIB_TREE_POSTORDER_HPP_

#include "ITraversal.hpp"
#include "ITemplateTree.hpp"
#include "TreeNode.hpp"

namespace bialger {

class PostOrder : public ITraversal {
 public:
  PostOrder() = delete;

  explicit PostOrder(const ITree& tree);

  PostOrder(const PostOrder& other);
  PostOrder& operator=(const PostOrder& other);
  ~PostOrder() override = default;
  PostOrder(PostOrder&& other) noexcept;
  PostOrder& operator=(PostOrder&& other) noexcept;

  [[nodiscard]] ITreeNode* GetFirst() const override;
  [[nodiscard]] ITreeNode* GetLast() const override;
  [[nodiscard]] ITreeNode* GetEnd() const override;
  [[nodiscard]] ITreeNode* GetPredecessor(ITreeNode* current) const override;
  [[nodiscard]] ITreeNode* GetSuccessor(ITreeNode* current) const override;
 private:
  const ITree* tree_;
};

} // bialger

#endif //LIB_TREE_POSTORDER_HPP_
