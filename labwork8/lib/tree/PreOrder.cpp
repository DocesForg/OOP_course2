#include "PreOrder.hpp"

bialger::PreOrder::PreOrder(const bialger::ITree& tree) : tree_(&tree) {}

bialger::ITreeNode* bialger::PreOrder::GetFirst() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  return tree_->GetRoot();
}

bialger::ITreeNode* bialger::PreOrder::GetLast() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  ITreeNode* node = tree_->GetRoot();

  if (node == nullptr) {
    return node;
  }

  while (!node->IsLeaf()) {
    if (node->HasRight()) {
      node = node->GetRight();
    } else {
      node = node->GetLeft();
    }
  }

  return node;
}

bialger::ITreeNode* bialger::PreOrder::GetEnd() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  return tree_->GetEnd();
}

bialger::ITreeNode* bialger::PreOrder::GetPredecessor(bialger::ITreeNode* current) const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  if (current == GetFirst()) {
    return tree_->GetEnd();
  } else if (current == tree_->GetEnd()) {
    return GetLast();
  }

  ITreeNode* parent = current->GetParent();

  if (current == parent->GetRight() && parent->HasLeft()) {
    current = parent->GetLeft();

    while (!current->IsLeaf()) {
      if (current->HasRight()) {
        current = current->GetRight();
      } else {
        current = current->GetLeft();
      }
    }

    return current;
  }

  return parent;
}

bialger::ITreeNode* bialger::PreOrder::GetSuccessor(bialger::ITreeNode* current) const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  if (current == tree_->GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_->GetEnd();
  }

  if (current->HasLeft()) {
    return current->GetLeft();
  }

  if (current->HasRight()) {
    return current->GetRight();
  }

  ITreeNode* parent = current->GetParent();

  while (parent != nullptr) {
    if (parent->HasRight() && current == parent->GetLeft()) {
      return parent->GetRight();
    }

    current = parent;
    parent = current->GetParent();
  }

  return tree_->GetEnd();
}

bialger::PreOrder::PreOrder(bialger::PreOrder&& other) noexcept : tree_(nullptr) {
  std::swap(tree_, other.tree_);
}

bialger::PreOrder& bialger::PreOrder::operator=(bialger::PreOrder&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  tree_ = nullptr;
  std::swap(tree_, other.tree_);
  return *this;
}

bialger::PreOrder::PreOrder(const bialger::PreOrder& other) : tree_(other.tree_) {}

bialger::PreOrder& bialger::PreOrder::operator=(const bialger::PreOrder& other) {
  if (this == &other) {
    return *this;
  }

  tree_ = other.tree_;
  return *this;
}
