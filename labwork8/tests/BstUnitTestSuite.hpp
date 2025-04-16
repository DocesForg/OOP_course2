#ifndef BSTUNITTESTSUITE_HPP_
#define BSTUNITTESTSUITE_HPP_

#include <vector>
#include <sstream>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include "lib/bst/BST.hpp"
#include "custom_classes.hpp"

struct BstUnitTestSuite : public testing::Test { // special test structure
  void SetUp() override; // method that is called at the beginning of every test

  void TearDown() override; // method that is called at the end of every test

 protected:
  const size_t size = 1000;
  const size_t distance = 5;
  std::random_device dev;
  std::mt19937 rng{dev()};
  std::uniform_int_distribution<std::mt19937::result_type> dist{0, std::numeric_limits<uint32_t>::max()};
  std::vector<int32_t> values;
  std::vector<int32_t> values_unique;
  std::vector<int32_t> sample_values;
  std::vector<int32_t> data_inorder;
  bialger::BST<int32_t> bst;
  bialger::BST<int32_t, bialger::LessContainer<void>> custom_comparator_bst;
  bialger::BST<int32_t, std::less<>, bialger::CountingAllocator<int32_t>> custom_allocator_bst;
  bialger::BST<int32_t, bialger::LessContainer<void>, bialger::CountingAllocator<int32_t>> custom_bst;
  std::less<> default_comparator{};
  std::allocator<int32_t> default_allocator{};
  bialger::LessContainer<void> custom_comparator{};
  bialger::CountingAllocator<int32_t> custom_allocator{};
};

#endif //BSTUNITTESTSUITE_HPP_
