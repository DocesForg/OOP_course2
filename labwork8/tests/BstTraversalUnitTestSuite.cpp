#include "BstTraversalUnitTestSuite.hpp"
#include "test_functions.hpp"

void BstTraversalUnitTestSuite::SetUp() {
  values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    bst.insert(value);
  }
}

void BstTraversalUnitTestSuite::TearDown() {
  if (!real_traversal.str().empty()) {
    ASSERT_EQ(real_traversal.str(), iterator_traversal.str());
  } else if (!reversed_traversal.str().empty()) {
    ASSERT_EQ(reversed_traversal.str(), iterator_traversal.str());
  }
}
