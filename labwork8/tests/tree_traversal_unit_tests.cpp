#include <sstream>

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "TreeTraversalUnitTestSuite.hpp"
#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

using namespace bialger;

TEST_F(TreeTraversalUnitTestSuite, InOrderTraverseTreeTest0) {
  std::vector<std::string> real_traverse_str;
  std::vector<std::string> class_traverse_str;
  StringTree bst_str{};
  InOrder in_order_str(bst_str);
  ITraversal& traversal = in_order_str;
  std::vector<std::string> values_str{"test", "test1", "t", "_", "", "r", "abcdef", "1"};

  for (std::string& value : values_str) {
    bst_str.Insert(value, &value);
  }

  bst_str.Traverse<InOrder>([&](StringTree::NodeType* node) -> void {
    real_traverse_str.push_back(node->key);
  });

  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst_str.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse_str.push_back(dynamic_cast<StringTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse_str, class_traverse_str);
}

TEST_F(TreeTraversalUnitTestSuite, InOrderTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  InOrder in_order(bst);
  ITraversal& traversal = in_order;
  bst.Traverse<InOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }
}

TEST_F(TreeTraversalUnitTestSuite, InOrderReversedTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  InOrder in_order(bst);
  ITraversal& traversal = in_order;
  bst.Traverse<InOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}

TEST_F(TreeTraversalUnitTestSuite, PreOrderTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;
  bst.Traverse<PreOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }
}

TEST_F(TreeTraversalUnitTestSuite, PreOrderReversedTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;
  bst.Traverse<PreOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}

TEST_F(TreeTraversalUnitTestSuite, PostOrderTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  PostOrder post_order(bst);
  ITraversal& traversal = post_order;
  bst.Traverse<PostOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }
}

TEST_F(TreeTraversalUnitTestSuite, PostOrderReversedTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  PostOrder post_order(bst);
  ITraversal& traversal = post_order;
  bst.Traverse<PostOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}

TEST_F(TreeTraversalUnitTestSuite, InOrderFullTraverseTreeTest) {
  std::vector<int32_t> values_ = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};

  for (int32_t& value : values_) {
    bst.Insert(value, &value);
  }

  InOrder in_order(bst);
  ITraversal& traversal = in_order;
  bst.Traverse<InOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.Traverse<InOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}

TEST_F(TreeTraversalUnitTestSuite, PreOrderFullTraverseTreeTest) {
  std::vector<int32_t> values_ = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};

  for (int32_t& value : values_) {
    bst.Insert(value, &value);
  }

  PreOrder pre_order(bst);
  ITraversal& traversal = pre_order;
  bst.Traverse<PreOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.Traverse<PreOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}

TEST_F(TreeTraversalUnitTestSuite, PostOrderFullTraverseTreeTest) {
  std::vector<int32_t> values_ = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                                 44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                                 83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};

  for (int32_t& value : values_) {
    bst.Insert(value, &value);
  }

  PostOrder post_order(bst);
  ITraversal& traversal = post_order;
  bst.Traverse<PostOrder>(push_node);
  ITreeNode* begin = traversal.GetFirst();
  ITreeNode* end = bst.GetEnd();

  for (ITreeNode* it = begin; it != end; it = traversal.GetSuccessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  ASSERT_EQ(real_traverse, class_traverse);
  real_traverse.clear();
  class_traverse.clear();

  bst.Traverse<PostOrder>(push_node);
  ITreeNode* rbegin = traversal.GetLast();
  ITreeNode* rend = bst.GetEnd();

  for (ITreeNode* it = rbegin; it != rend; it = traversal.GetPredecessor(it)) {
    class_traverse.push_back(dynamic_cast<IntTree::NodeType*>(it)->key);
  }

  std::reverse(real_traverse.begin(), real_traverse.end());
}
