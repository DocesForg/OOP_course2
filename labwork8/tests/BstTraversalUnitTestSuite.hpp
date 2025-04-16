#ifndef BSTTRAVERSALUNITTESTSUITE_HPP_
#define BSTTRAVERSALUNITTESTSUITE_HPP_

#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "lib/bst/BST.hpp"

struct BstTraversalUnitTestSuite : public testing::Test {
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const size_t size = 10000;
  std::ostringstream real_traversal;
  std::ostringstream reversed_traversal;
  std::ostringstream iterator_traversal;
  std::vector<int32_t> values;
  bialger::BST<int32_t> bst;
};

#endif //BSTTRAVERSALUNITTESTSUITE_HPP_
