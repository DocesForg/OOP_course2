#ifndef TREEUNITTESTSUITE_HPP_
#define TREEUNITTESTSUITE_HPP_

#include <vector>
#include <string>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include "lib/tree/BinarySearchTree.hpp"
#include "lib/tree/InOrder.hpp"
#include "lib/tree/PreOrder.hpp"
#include "lib/tree/PostOrder.hpp"

using namespace bialger;

using IntTree = BinarySearchTree<int32_t, const int32_t*, std::less<>, std::allocator<int32_t>>;
using StringTree = BinarySearchTree<std::string,
                                    const std::string*,
                                    std::less<std::string>,
                                    std::allocator<std::string>>;

using UnstrictIntTree = BinarySearchTree<int32_t, const int32_t*, std::less_equal<>, std::allocator<int32_t>>;
using UnstrictStringTree = BinarySearchTree<std::string,
                                            const std::string*,
                                            std::less_equal<std::string>,
                                            std::allocator<std::string>>;

struct TreeUnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const size_t size = 1000;
  const size_t distance = 5;
  std::vector<int32_t> values_random;
  std::vector<int32_t> values_unique;
  std::random_device dev;
  std::mt19937 rng{dev()};
  std::uniform_int_distribution<std::mt19937::result_type> dist{0, std::numeric_limits<uint32_t>::max()};
  IntTree bst;
  IntTree bst_dupl{true};
  UnstrictIntTree ubst;
  UnstrictIntTree ubst_dupl{true};
  StringTree bst_str;
  StringTree bst_str_dupl{true};
  UnstrictStringTree ubst_str;
  UnstrictStringTree ubst_str_dupl{true};
};

#endif //TREEUNITTESTSUITE_HPP_
