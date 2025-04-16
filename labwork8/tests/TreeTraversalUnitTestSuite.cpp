#include "TreeTraversalUnitTestSuite.hpp"
#include "test_functions.hpp"

void TreeTraversalUnitTestSuite::SetUp() {
  values = GetRandomNumbers(size);
  push_node = [&](IntTree::NodeType* node) -> void {
    real_traverse.push_back(node->key);
  };
}

void TreeTraversalUnitTestSuite::TearDown() {
  ASSERT_EQ(real_traverse, class_traverse);
}
