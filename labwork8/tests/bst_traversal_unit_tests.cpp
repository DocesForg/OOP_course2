#include "BstTraversalUnitTestSuite.hpp"
#include "test_functions.hpp"

using namespace bialger;

TEST_F(BstTraversalUnitTestSuite, InOrderTraverseTreeTest1) {
  bst.PrintToStream(real_traversal);

  for (auto it = bst.begin(); it != bst.end(); ++it) {
    iterator_traversal << *it << ' ';
  }
}

TEST_F(BstTraversalUnitTestSuite, InOrderReversedTraverseTreeTest1) {
  std::string reversed_real_traversal;
  bst.PrintToStream(real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());
  real_traversal.str("");

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstTraversalUnitTestSuite, InOrderTraverseTreeBothWaysTest1) {
  for (auto it = bst.rbegin(); it != bst.rend(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end(); it != bst.end(); --it) {
    iterator_traversal << *it << ' ';
  }
}

TEST_F(BstTraversalUnitTestSuite, InOrderFirstAndLastTraverseTreeTest1) {
  auto it = bst.end();
  auto reverse_it = bst.rend();

  ASSERT_EQ(*--it, *bst.rbegin());
  ASSERT_EQ(*--reverse_it, *bst.begin());
}

TEST_F(BstTraversalUnitTestSuite, PreOrderTraverseTreeTest1) {
  bst.PrintToStream<PreOrder>(real_traversal);

  for (auto it = bst.begin<PreOrder>(); it != bst.end<PreOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }
}

TEST_F(BstTraversalUnitTestSuite, PreOrderReversedTraverseTreeTest1) {
  std::string reversed_real_traversal;
  bst.PrintToStream<PreOrder>(real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());
  real_traversal.str("");

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin<PreOrder>(); it != bst.rend<PreOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstTraversalUnitTestSuite, PreOrderFirstAndLastTraverseTreeTest1) {
  for (int32_t& value : values) {
    bst.insert(value);
  }

  auto it = bst.end<PreOrder>();
  auto reverse_it = bst.rend<PreOrder>();

  ASSERT_EQ(*--it, *bst.rbegin<PreOrder>());
  ASSERT_EQ(*--reverse_it, *bst.begin<PreOrder>());
}

TEST_F(BstTraversalUnitTestSuite, PreOrderTraverseTreeBothWaysTest1) {
  for (auto it = bst.rbegin<PreOrder>(); it != bst.rend<PreOrder>(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end<PreOrder>(); it != bst.end<PreOrder>(); --it) {
    iterator_traversal << *it << ' ';
  }
}

TEST_F(BstTraversalUnitTestSuite, PostOrderTraverseTreeTest1) {
  bst.PrintToStream<PostOrder>(real_traversal);

  for (auto it = bst.begin<PostOrder>(); it != bst.end<PostOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }
}

TEST_F(BstTraversalUnitTestSuite, PostOrderReversedTraverseTreeTest1) {
  std::string reversed_real_traversal;
  bst.PrintToStream<PostOrder>(real_traversal);
  std::vector<std::string> reversed_vector = SplitString(real_traversal.str());
  std::reverse(reversed_vector.begin(), reversed_vector.end());
  real_traversal.str("");

  for (const std::string& value : reversed_vector) {
    reversed_real_traversal += value + " ";
  }

  for (auto it = bst.rbegin<PostOrder>(); it != bst.rend<PostOrder>(); ++it) {
    iterator_traversal << *it << ' ';
  }

  ASSERT_EQ(reversed_real_traversal, iterator_traversal.str());
}

TEST_F(BstTraversalUnitTestSuite, PostOrderFirstAndLastTraverseTreeTest1) {
  auto it = bst.end<PostOrder>();
  auto reverse_it = bst.rend<PostOrder>();

  ASSERT_EQ(*--it, *bst.rbegin<PostOrder>());
  ASSERT_EQ(*--reverse_it, *bst.begin<PostOrder>());
}

TEST_F(BstTraversalUnitTestSuite, PostOrderTraverseTreeBothWaysTest1) {
  for (auto it = bst.rbegin<PostOrder>(); it != bst.rend<PostOrder>(); ++it) {
    reversed_traversal << *it << ' ';
  }

  for (auto it = --bst.end<PostOrder>(); it != bst.end<PostOrder>(); --it) {
    iterator_traversal << *it << ' ';
  }
}
