#include "InOrder.hpp"

bialger::InOrder::InOrder(const bialger::ITree& tree): tree_(&tree) {}

bialger::ITreeNode* bialger::InOrder::GetFirst() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  return GetMin(tree_->GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetLast() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  return GetMax(tree_->GetRoot());
}

bialger::ITreeNode* bialger::InOrder::GetEnd() const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  return tree_->GetEnd();
}

bialger::ITreeNode* bialger::InOrder::GetPredecessor(bialger::ITreeNode* current) const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  if (current == GetFirst()) {
    return tree_->GetEnd();
  } else if (current == tree_->GetEnd()) {
    return GetLast();
  }

  if (current->HasLeft()) {
    return GetMax(current->GetLeft());
  }

  ITreeNode* parent = current->GetParent();
  ITreeNode* predecessor = current;

  while (parent != nullptr && predecessor == parent->GetLeft()) {
    predecessor = parent;
    parent = parent->GetParent();
  }

  return parent;
}

bialger::ITreeNode* bialger::InOrder::GetSuccessor(bialger::ITreeNode* current) const {
  if (tree_ == nullptr) {
    return nullptr;
  }

  if (current == tree_->GetEnd()) {
    return GetFirst();
  } else if (current == GetLast()) {
    return tree_->GetEnd();
  }

  if (current->HasRight()) {
    return GetMin(current->GetRight());
  }

  ITreeNode* parent = current->GetParent();
  ITreeNode* successor = current;

  while (parent != nullptr && successor == parent->GetRight()) {
    successor = parent;
    parent = parent->GetParent();
  }

  return parent;
}

bialger::ITreeNode* bialger::InOrder::GetMin(bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasLeft()) {
    current = current->GetLeft();
  }

  return current;
}

bialger::ITreeNode* bialger::InOrder::GetMax(bialger::ITreeNode* current) {
  if (current == nullptr) {
    return current;
  }

  while (current->HasRight()) {
    current = current->GetRight();
  }

  return current;
}

bialger::InOrder::InOrder(bialger::InOrder&& other) noexcept : tree_(nullptr) {
  std::swap(tree_, other.tree_);
}

bialger::InOrder& bialger::InOrder::operator=(bialger::InOrder&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  tree_ = nullptr;
  std::swap(tree_, other.tree_);
  return *this;
}

bialger::InOrder::InOrder(const bialger::InOrder& other) : tree_(other.tree_) {}

bialger::InOrder& bialger::InOrder::operator=(const bialger::InOrder& other) {
  if (this == &other) {
    return *this;
  }

  tree_ = other.tree_;
  return *this;
}
