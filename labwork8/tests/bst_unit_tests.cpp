#include <sstream>

#include <vector>
#include <set>
#include <gtest/gtest.h>

#include "BstUnitTestSuite.hpp"

using namespace bialger;

TEST_F(BstUnitTestSuite, EmptyTest) {
  BST<int32_t> empty_bst;
  empty_bst.insert({});
  empty_bst.insert(values.end(), values.end());
  empty_bst.insert(custom_bst);
  ASSERT_EQ(empty_bst.max_size(), std::numeric_limits<BST<int32_t>::difference_type>::max());
  ASSERT_EQ(empty_bst, bst);
  ASSERT_EQ(empty_bst.size(), 0);
  ASSERT_TRUE(empty_bst.empty());
  ASSERT_FALSE(empty_bst.contains(0));
}

TEST_F(BstUnitTestSuite, NonEmptyTest) {
  bst.insert(0);
  ASSERT_EQ(bst, bst);
  ASSERT_EQ(bst.size(), 1);
  ASSERT_FALSE(bst.empty());
}

TEST_F(BstUnitTestSuite, NonEmptyNonTrivialTest) {
  BST<std::vector<int32_t>> vector_bst;
  vector_bst.insert(values);
  ASSERT_EQ(vector_bst, vector_bst);
  ASSERT_EQ(vector_bst.size(), 1);
  ASSERT_FALSE(vector_bst.empty());
}

TEST_F(BstUnitTestSuite, BeginTest) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);
  ASSERT_TRUE(string_bst.begin() == string_bst.begin<InOrder>());
  ASSERT_TRUE(string_bst.cbegin() == string_bst.cbegin<InOrder>());
  ASSERT_TRUE(string_bst.rbegin() == string_bst.rbegin<InOrder>());
  ASSERT_TRUE(string_bst.crbegin() == string_bst.crbegin<InOrder>());
  ASSERT_EQ(*string_bst.begin(), element);
  ASSERT_EQ(*string_bst.begin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.begin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.cbegin(), element);
  ASSERT_EQ(*string_bst.cbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.cbegin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.rbegin(), element);
  ASSERT_EQ(*string_bst.rbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.rbegin<PostOrder>(), element);
  ASSERT_EQ(*string_bst.crbegin(), element);
  ASSERT_EQ(*string_bst.crbegin<PreOrder>(), element);
  ASSERT_EQ(*string_bst.crbegin<PostOrder>(), element);
}

TEST_F(BstUnitTestSuite, EndTest) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);
  ASSERT_TRUE(string_bst.end() == string_bst.end<InOrder>());
  ASSERT_TRUE(string_bst.cend() == string_bst.cend<InOrder>());
  ASSERT_TRUE(string_bst.rend() == string_bst.rend<InOrder>());
  ASSERT_TRUE(string_bst.crend() == string_bst.crend<InOrder>());
  ASSERT_THROW(*string_bst.end(), std::out_of_range);
  ASSERT_THROW(*string_bst.end<PreOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.end<PostOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.cend(), std::out_of_range);
  ASSERT_THROW(*string_bst.cend<PreOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.cend<PostOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.rend(), std::out_of_range);
  ASSERT_THROW(*string_bst.rend<PreOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.rend<PostOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.crend(), std::out_of_range);
  ASSERT_THROW(*string_bst.crend<PreOrder>(), std::out_of_range);
  ASSERT_THROW(*string_bst.crend<PostOrder>(), std::out_of_range);
}

TEST_F(BstUnitTestSuite, IteratorTest1) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);

  auto current = string_bst.begin();
  auto next = string_bst.end();
  ASSERT_TRUE(next == current.next());
  ASSERT_TRUE(next.prev() == current);
  ASSERT_TRUE(next.prev() == current++);
  ASSERT_TRUE(next == current);
  ASSERT_EQ(*--current, element);
  ASSERT_EQ(current->size(), element.size());
  ASSERT_EQ(current++->size(), element.size());
}

TEST_F(BstUnitTestSuite, IteratorTest2) {
  BST<std::string> string_bst;
  std::string element = "str";
  string_bst.insert(element);

  auto current = string_bst.begin();
  auto next = string_bst.end();
  ASSERT_TRUE(*current-- == element);
  ASSERT_THROW(current++, std::out_of_range);
  ASSERT_THROW(++current, std::out_of_range);
  ASSERT_TRUE(--current == string_bst.begin());
  ASSERT_TRUE(--current == next);
}

TEST_F(BstUnitTestSuite, BadComparatorTest) {
  BST<int32_t, std::less_equal<>> bad_bst;
  ASSERT_THROW(bad_bst.insert(0), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(bad_bst.end(), 0), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert({1}), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(values_unique.begin(), values_unique.end()), std::invalid_argument);
  ASSERT_THROW(bad_bst.insert(values_unique), std::invalid_argument);
}

TEST_F(BstUnitTestSuite, ConstructTest1) {
  BST<int32_t> bst2(default_comparator, default_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(default_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest2) {
  BST<int32_t> bst2 = {1, 2, 3, 4, 5};

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, ConstructTest3) {
  BST<int32_t> bst2(sample_values.begin(), sample_values.end());

  ASSERT_EQ(bst2.size(), sample_values.size());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest1) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2(custom_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest2) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2({1, 2, 3, 4, 5}, custom_comparator, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_comparator, bst2.value_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest3) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2({1, 2, 3, 4, 5}, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest4) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2({1, 2, 3, 4, 5}, custom_comparator, custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest5) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2(sample_values.begin(), sample_values.end(), custom_allocator);

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualComparatorAllocatorTest6) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>>
      bst2(sample_values.begin(), sample_values.end(), custom_comparator, custom_allocator);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_comparator, bst2.key_comp());
  ASSERT_EQ(custom_allocator, bst2.get_allocator());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest1) {
  for (int32_t& value : sample_values) {
    custom_bst.insert(value);
  }

  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2 = custom_bst;

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest2) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  custom_bst.insert(-1);

  for (int32_t& value : sample_values) {
    bst2.insert(value);
  }

  custom_bst = bst2;

  ASSERT_EQ(custom_bst.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : custom_bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, CopyTest3) {
  std::vector<int32_t> data_preorder;
  std::vector<int32_t> data_preorder2;
  BST<int32_t> bst2;
  bst.insert(100000000);

  for (int32_t& value : values_unique) {
    bst2.insert(value);
  }

  bst = bst2;

  ASSERT_EQ(bst.size(), values_unique.size());

  for (auto it = bst.begin<PreOrder>(); it != bst.end<PreOrder>(); ++it) {
    data_preorder.push_back(*it);
  }

  for (auto it = bst2.begin<PreOrder>(); it != bst2.end<PreOrder>(); ++it) {
    data_preorder2.push_back(*it);
  }

  ASSERT_EQ(data_preorder, data_preorder2);
}

TEST_F(BstUnitTestSuite, CopyTest4) {
  bst.insert(values_unique);
  bst = {1, 2, 3, 4, 5};

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, SwapTest1) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  auto old_comp = custom_bst.key_comp();
  auto old_alloc = custom_bst.get_allocator();
  auto new_comp = bst2.key_comp();
  auto new_alloc = bst2.get_allocator();

  for (int32_t& value : sample_values) {
    custom_bst.insert(value);
  }

  bst2.swap(custom_bst);

  ASSERT_EQ(custom_bst.size(), 0);
  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), new_alloc);
  ASSERT_EQ(custom_bst.key_comp(), new_comp);
  ASSERT_EQ(old_alloc, bst2.get_allocator());
  ASSERT_EQ(old_comp, bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, SwapTest2) {
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  auto old_comp = custom_bst.key_comp();
  auto old_alloc = custom_bst.get_allocator();
  auto new_comp = bst2.key_comp();
  auto new_alloc = bst2.get_allocator();

  for (int32_t& value : sample_values) {
    custom_bst.insert(value);
  }

  swap(bst2, custom_bst);

  ASSERT_EQ(custom_bst.size(), 0);
  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), new_alloc);
  ASSERT_EQ(custom_bst.key_comp(), new_comp);
  ASSERT_EQ(old_alloc, bst2.get_allocator());
  ASSERT_EQ(old_comp, bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualCopyComparatorAllocatorTest1) {
  custom_bst.insert(sample_values.begin(), sample_values.end());

  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2 = custom_bst;
  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, EqualCopyComparatorAllocatorTest2) {
  custom_bst.insert(sample_values.begin(), sample_values.end());

  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  bst2 = custom_bst;

  ASSERT_EQ(bst2.size(), sample_values.size());
  ASSERT_EQ(custom_bst.get_allocator(), bst2.get_allocator());
  ASSERT_EQ(custom_bst.key_comp(), bst2.key_comp());

  for (const int32_t& val : bst2) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest1) {

  for (int32_t& value : sample_values) {
    bst.insert(value);
  }

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest2) {

  for (int32_t& value : sample_values) {
    bst.insert(bst.end(), value);
  }

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest3) {
  bst.insert({3, 5, 4, 5, 2, 5, 1});

  ASSERT_EQ(bst.size(), sample_values.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  ASSERT_EQ(sample_values, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest4) {
  for (int32_t& value : values_unique) {
    bst.insert(value);
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest5) {

  bst.insert(values_unique.begin(), values_unique.end());

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest6) {

  bst.insert(values_unique);

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertTest7) {

  std::vector<int32_t> data_inorder2;
  custom_bst.insert(values);
  BST<int32_t, LessContainer<void>, CountingAllocator<int32_t>> bst2;
  bst2.insert(custom_bst);

  ASSERT_EQ(bst2.size(), custom_bst.size());

  for (const int32_t& val : custom_bst) {
    data_inorder.push_back(val);
  }

  for (const int32_t& val : bst2) {
    data_inorder2.push_back(val);
  }

  ASSERT_EQ(data_inorder, data_inorder2);
}

TEST_F(BstUnitTestSuite, InsertTest8) {

  bst.insert(values_unique);

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, ClearTest) {
  bst.insert(values);

  bst.clear();

  ASSERT_EQ(bst.size(), 0);
}

TEST_F(BstUnitTestSuite, EraseTest1) {
  bst.insert(values);

  for (auto it = bst.begin(); it != bst.end();) {
    it = bst.erase(it);
  }

  ASSERT_EQ(bst.size(), 0);
}

TEST_F(BstUnitTestSuite, EraseTest2) {
  bst.insert(values_unique);
  size_t erase_count = 0;

  for (auto it = bst.begin(); it != bst.end();) {
    auto current = it++;

    if (dist(rng) % 2 == 0) {
      bst.erase(current);
      ++erase_count;
    }
  }

  ASSERT_EQ(bst.size(), size - erase_count);
}

TEST_F(BstUnitTestSuite, EraseTest3) {
  bst.insert(values_unique);
  const size_t erase_size = 250 + (dist(rng) % (size / 4));
  const size_t erase_start = (dist(rng) % (size / 2));
  const size_t erase_end = erase_start + erase_size;
  auto first = bst.begin();
  auto last = bst.begin();

  for (size_t i = 0; i < erase_start; ++i) {
    ++first;
  }

  for (size_t i = 0; i < erase_end; ++i) {
    ++last;
  }

  bst.erase(first, last);

  ASSERT_EQ(bst.size(), size - erase_size);
}

TEST_F(BstUnitTestSuite, EraseTest4) {
  bst.insert(values_unique);
  size_t erase_count = 0;

  for (int32_t value : values_unique) {
    ASSERT_EQ(bst.erase(value + 1000000), 0);
  }

  for (int32_t value : values_unique) {
    if (dist(rng) % 2 == 0) {
      ASSERT_EQ(bst.erase(value), 1);
      ++erase_count;
    }
  }

  ASSERT_EQ(bst.size(), size - erase_count);
}

TEST_F(BstUnitTestSuite, EraseIfTest) {
  bst.insert(values_unique);
  size_t erase_count = 0;

  erase_if(bst, [&](int32_t val) -> bool {
    if (dist(rng) % 2 == 0) {
      ++erase_count;
      return true;
    }

    return false;
  });

  ASSERT_EQ(bst.size(), size - erase_count);
}

TEST_F(BstUnitTestSuite, FindTest1) {
  bst.insert(values);

  for (int32_t value : values) {
    ASSERT_EQ(*bst.find(value), value);
    ASSERT_EQ(*bst.find<PreOrder>(value), value);
    ASSERT_EQ(*bst.find<PostOrder>(value), value);
  }
}

TEST_F(BstUnitTestSuite, FindTest2) {
  bst.insert(values_unique);

  for (int32_t value : values_unique) {
    ASSERT_TRUE(bst.find(value + 1000000) == bst.end());
    ASSERT_TRUE(bst.find<PreOrder>(value + 1000000) == bst.end<PreOrder>());
    ASSERT_TRUE(bst.find<PostOrder>(value + 1000000) == bst.end<PostOrder>());
  }
}

TEST_F(BstUnitTestSuite, InsertAndFindTest1) {

  for (int32_t& value : values_unique) {
    auto res = bst.insert(value);
    ASSERT_TRUE(res.first == bst.find(value));
    ASSERT_TRUE(res.second);
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PreOrder>(value);
    ASSERT_TRUE(res.first == bst.find<PreOrder>(value));
    ASSERT_FALSE(res.second);
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PostOrder>(value);
    ASSERT_TRUE(res.first == bst.find<PostOrder>(value));
    ASSERT_FALSE(res.second);
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, InsertAndFindTest2) {

  for (int32_t& value : values_unique) {
    auto res = bst.insert(bst.end(), value);
    ASSERT_TRUE(res == bst.find(value));
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PreOrder>(bst.end<PreOrder>(), value);
    ASSERT_TRUE(res == bst.find<PreOrder>(value));
  }

  for (int32_t& value : values_unique) {
    auto res = bst.insert<PostOrder>(bst.end<PostOrder>(), value);
    ASSERT_TRUE(res == bst.find<PostOrder>(value));
  }

  ASSERT_EQ(bst.size(), values_unique.size());

  for (const int32_t& val : bst) {
    data_inorder.push_back(val);
  }

  std::sort(values_unique.begin(), values_unique.end());

  ASSERT_EQ(values_unique, data_inorder);
}

TEST_F(BstUnitTestSuite, ContainsTest1) {
  bst.insert(values);

  for (int32_t value : values) {
    ASSERT_TRUE(bst.contains(value));
  }
}

TEST_F(BstUnitTestSuite, ContainsTest2) {
  bst.insert(values_unique);

  for (int32_t value : values_unique) {
    ASSERT_FALSE(bst.contains(value + 1000000));
  }
}

TEST_F(BstUnitTestSuite, CountTest1) {
  bst.insert(values);

  for (int32_t value : values) {
    ASSERT_EQ(bst.count(value), 1);
  }
}

TEST_F(BstUnitTestSuite, CountTest2) {
  bst.insert(values_unique);

  for (int32_t value : values_unique) {
    ASSERT_EQ(bst.contains(value + 1000000), 0);
  }
}

TEST_F(BstUnitTestSuite, LowerBoundTest1) {
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value <= distance * size; ++value) {
    auto vector_lower = std::lower_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_lower = bst.lower_bound(value);

    if (vector_lower != values_unique.end()) {
      ASSERT_EQ(*vector_lower, *bst_lower);
    } else {
      ASSERT_TRUE(bst_lower == bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, UpperBoundTest1) {
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value <= distance * size; ++value) {
    auto vector_upper = std::upper_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_upper = bst.upper_bound(value);

    if (vector_upper != values_unique.end()) {
      ASSERT_EQ(*vector_upper, *bst_upper);
    } else {
      ASSERT_TRUE(bst_upper == bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, EqualRangeTest1) {
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value <= distance * size; ++value) {
    auto vector_lower = std::lower_bound(values_unique.begin(), values_unique.end(), value);
    auto vector_upper = std::upper_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_lower = bst.lower_bound(value);
    auto bst_upper = bst.upper_bound(value);
    auto range = bst.equal_range(value);

    for (auto it = bst_lower; it != bst_upper && it != bst.end(); ++it) {
      ASSERT_EQ(*it, value);
    }

    ASSERT_TRUE(bst_lower == range.first);
    ASSERT_TRUE(bst_upper == range.second);

    if (vector_lower != values_unique.end()) {
      ASSERT_EQ(*vector_lower, *range.first);
    } else {
      ASSERT_TRUE(range.first == bst.end());
      ASSERT_TRUE(range.second == bst.end());
    }

    if (vector_upper != values_unique.end()) {
      ASSERT_EQ(*vector_upper, *range.second);
    } else {
      ASSERT_TRUE(range.first == bst.end() || range.first == --bst.end());
      ASSERT_TRUE(range.second == bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, TransparentTest1) {
  custom_bst.insert(values_unique);

  for (int32_t value : values_unique) {
    std::vector<bool> vec(static_cast<size_t>(value));
    ASSERT_EQ(*custom_bst.find(vec), value);
    ASSERT_EQ(*custom_bst.find<PreOrder>(vec), value);
    ASSERT_EQ(*custom_bst.find<PostOrder>(vec), value);
  }

  for (int32_t value : values_unique) {
    std::vector<bool> vec(static_cast<size_t>(value + distance * size));
    ASSERT_TRUE(custom_bst.find(vec) == custom_bst.end());
    ASSERT_TRUE(custom_bst.find<PreOrder>(vec) == custom_bst.end<PreOrder>());
    ASSERT_TRUE(custom_bst.find<PostOrder>(vec) == custom_bst.end<PostOrder>());
  }
}

TEST_F(BstUnitTestSuite, TransparentTest2) {
  custom_bst.insert(values_unique);

  for (int32_t value : values_unique) {
    std::vector<bool> vec(static_cast<size_t>(value));
    std::vector<bool> bad_vec(static_cast<size_t>(value + distance * size));
    ASSERT_TRUE(custom_bst.contains(vec));
    ASSERT_FALSE(custom_bst.contains(bad_vec));
  }
}

TEST_F(BstUnitTestSuite, TransparentTest3) {
  custom_bst.insert(values_unique);

  for (int32_t value : values_unique) {
    std::vector<bool> vec(static_cast<size_t>(value));
    std::vector<bool> bad_vec(static_cast<size_t>(value + distance * size));
    ASSERT_EQ(custom_bst.count(vec), 1);
    ASSERT_EQ(custom_bst.contains(bad_vec), 0);
  }
}

TEST_F(BstUnitTestSuite, TransparentTest4) {
  custom_bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = 0; value <= distance * size; ++value) {
    std::vector<bool> vec(static_cast<size_t>(value));
    auto vector_lower = std::lower_bound(values_unique.begin(), values_unique.end(), value);
    auto vector_upper = std::upper_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_lower = custom_bst.lower_bound(vec);
    auto bst_upper = custom_bst.upper_bound(vec);
    auto range = custom_bst.equal_range(vec);

    for (auto it = bst_lower; it != bst_upper && it != custom_bst.end(); ++it) {
      ASSERT_EQ(*it, value);
    }

    ASSERT_TRUE(bst_lower == range.first);
    ASSERT_TRUE(bst_upper == range.second);

    if (vector_lower != values_unique.end()) {
      ASSERT_EQ(*vector_lower, *range.first);
    } else {
      ASSERT_TRUE(range.first == custom_bst.end());
      ASSERT_TRUE(range.second == custom_bst.end());
    }

    if (vector_upper != values_unique.end()) {
      ASSERT_EQ(*vector_upper, *range.second);
    } else {
      ASSERT_TRUE(range.first == custom_bst.end() || range.first == --custom_bst.end());
      ASSERT_TRUE(range.second == custom_bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, StlCompatabilityTest1) {
  bst.insert(values);
  size_t mod3_counter = 0;
  size_t mod3_counter_stl = 0;

  for (int32_t value : bst) {
    mod3_counter += (value % 3 == 0) ? 1 : 0;
  }

  std::for_each(bst.begin(), bst.end(), [&](int32_t current) -> void {
    mod3_counter_stl += (current % 3 == 0) ? 1 : 0;
  });

  ASSERT_EQ(mod3_counter_stl, mod3_counter);
}

TEST_F(BstUnitTestSuite, StlCompatabilityTest2) {
  bst.insert(values);
  const size_t distance = 250 + (dist(rng) % (size / 4));
  const size_t range_start = (dist(rng) % (size / 2));
  const size_t range_end = range_start + distance;
  auto first = bst.begin();
  auto last = bst.begin();

  for (size_t i = 0; i < range_start; ++i) {
    ++first;
  }

  for (size_t i = 0; i < range_end; ++i) {
    ++last;
  }

  int64_t stl_distance = std::distance(first, last);

  ASSERT_EQ(stl_distance, distance);
}

TEST_F(BstUnitTestSuite, StlCompatabilityTest3) {
  bst.insert(values_unique);
  std::sort(values_unique.begin(), values_unique.end());

  for (int32_t value = static_cast<int32_t>((distance - 1) * size); value <= distance * size; ++value) {
    auto vector_lower = std::lower_bound(values_unique.begin(), values_unique.end(), value);
    auto bst_lower = std::lower_bound(bst.begin(), bst.end(), value);

    if (vector_lower != values_unique.end()) {
      ASSERT_EQ(*vector_lower, *bst_lower);
    } else {
      ASSERT_TRUE(bst_lower == bst.end());
    }
  }
}

TEST_F(BstUnitTestSuite, InsertAndAllocatorTest) {
  custom_bst.insert(values);

  ASSERT_EQ(custom_bst.get_allocator().GetAllocationsCount(), custom_bst.size());
  ASSERT_EQ(custom_bst.get_allocator().GetDeallocationsCount(), 0);
}

TEST_F(BstUnitTestSuite, EraseAndAllocatorTest) {
  custom_bst.insert(values);

  for (auto it = custom_bst.begin(); it != custom_bst.end();) {
    it = custom_bst.erase(it);
  }

  ASSERT_EQ(custom_bst.get_allocator().GetAllocationsCount(), custom_bst.get_allocator().GetDeallocationsCount());
  ASSERT_EQ(custom_bst.size(), 0);
}

TEST_F(BstUnitTestSuite, ClearAndAllocatorTest) {
  custom_bst.insert(values);

  custom_bst.clear();

  ASSERT_EQ(custom_bst.get_allocator().GetAllocationsCount(), custom_bst.get_allocator().GetDeallocationsCount());
  ASSERT_EQ(custom_bst.size(), 0);
}
