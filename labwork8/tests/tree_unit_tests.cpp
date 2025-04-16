#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "test_functions.hpp"
#include "TreeUnitTestSuite.hpp"

using namespace bialger;

TEST_F(TreeUnitTestSuite, EmptyTreeTest) {
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, InsertTreeTest1) {
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest2) {
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst_str.Insert(value, &value);
  }

  ASSERT_EQ(bst_str.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest3) {
  std::vector<std::string> values{"test", "test1", "t", "test", "_", "", "r"};

  for (std::string& value : values) {
    bst_str_dupl.Insert(value, &value);
  }

  ASSERT_EQ(bst_str_dupl.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeTest4) {
  std::vector<int32_t> values = values_random;

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest5) {
  std::vector<int32_t> values(size);

  for (int32_t i = 0; i < size; ++i) {
    values[i] = i;
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    std::pair<IntTree::NodeType*, bool> new_node = bst.Insert(value, &value);
    ASSERT_EQ(new_node.first, bst.FindFirst(value));
    ASSERT_EQ(new_node.second, true);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeTest6) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  size_t unique = bst.GetSize();
  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    std::pair<IntTree::NodeType*, bool> new_node = bst.Insert(value, &value);
    ASSERT_EQ(new_node.first, bst.FindFirst(value));
    ASSERT_EQ(new_node.second, false);
  }

  ASSERT_EQ(bst.GetSize(), unique);
}

TEST_F(TreeUnitTestSuite, InsertTreeTest7) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  size_t unique = bst.GetSize();
  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  ASSERT_EQ(bst.GetSize(), unique);
}

TEST_F(TreeUnitTestSuite, InsertTreeTest8) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst_dupl.Insert(value, &value);
  }

  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst_dupl.Insert(value, &value);
  }

  ASSERT_EQ(bst_dupl.GetSize(), 3 * size);
}

TEST_F(TreeUnitTestSuite, CopyTreeTest1) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  IntTree bst2 = bst;

  for (int32_t& value : values) {
    ASSERT_TRUE(bst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(bst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, CopyTreeTest2) {
  IntTree bst2{};
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  bst2 = bst;

  for (int32_t& value : values) {
    ASSERT_TRUE(bst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(bst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest1) {
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    bst_str.Insert(value, &value);
  }

  for (std::string& value : values) {
    bst_str.Delete(bst_str.FindFirst(value));
  }

  ASSERT_EQ(bst_str.GetRoot(), nullptr);
  ASSERT_EQ(bst_str.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest2) {
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "r", "abcdef", "1"};

  for (std::string& value : values) {
    bst_str.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (std::string& value : values) {
    bst_str.Delete(bst_str.FindFirst(value));
  }

  ASSERT_EQ(bst_str.GetRoot(), nullptr);
  ASSERT_EQ(bst_str.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest3) {
  std::vector<int32_t> values{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest4) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::reverse(values.begin(), values.end());

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest5) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst.Delete(bst.FindFirst(value));
  }

  ASSERT_EQ(bst.GetRoot(), nullptr);
  ASSERT_EQ(bst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteTreeTest6) {
  std::vector<int32_t> values(values_random);
  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst_dupl.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    bst_dupl.Delete(bst_dupl.FindFirst(value));
  }

  ASSERT_EQ(bst_dupl.GetRoot(), nullptr);
  ASSERT_EQ(bst_dupl.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, FindNextTreeTest1) {
  std::vector<int32_t> values(values_unique);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_lower = std::lower_bound(values.begin(), values.end(), i);
    auto* bst_find = dynamic_cast<IntTree::NodeType*>(bst.FindFirst(i));
    auto* bst_next = dynamic_cast<IntTree::NodeType*>(bst.FindNext(i));
    if (vector_lower == values.end()) {
      ASSERT_EQ(bst_find, bst.GetEnd());
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else if (bst_find != nullptr) {
      ASSERT_EQ(bst_find->key, *vector_lower);
    } else {
      ASSERT_EQ(bst_next->key, *vector_lower);
    }
  }
}

TEST_F(TreeUnitTestSuite, FindNextTreeTest2) {
  std::vector<int32_t> values(values_unique);

  for (int32_t& value : values) {
    bst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_upper = std::upper_bound(values.begin(), values.end(), i);
    auto* bst_next = dynamic_cast<IntTree::NodeType*>(bst.FindNext(i));
    if (vector_upper == values.end()) {
      ASSERT_EQ(bst_next, bst.GetEnd());
    } else {
      ASSERT_EQ(bst_next->key, *vector_upper);
    }
  }
}

TEST_F(TreeUnitTestSuite, InsertUnstrictTreeTest1) {
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r"};

  for (std::string& value : values) {
    ubst_str.Insert(value, &value);
  }

  ASSERT_EQ(ubst_str.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertUnstrictTreeTest2) {
  std::vector<std::string> values{"test", "test1", "t", "r", "test", "_", "", "r"};

  for (std::string& value : values) {
    ubst_str_dupl.Insert(value, &value);
  }

  ASSERT_EQ(ubst_str_dupl.GetSize(), values.size());
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest3) {
  std::vector<int32_t> values(size);

  for (int32_t i = 0; i < size; ++i) {
    values[i] = i;
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    std::pair<IntTree::NodeType*, bool> new_node = ubst.Insert(value, &value);
    ASSERT_EQ(new_node.first, ubst.FindFirst(value));
    ASSERT_EQ(new_node.second, true);
  }
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest4) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    std::pair<IntTree::NodeType*, bool> new_node = ubst.Insert(value, &value);
    ASSERT_EQ(new_node.first, ubst.FindFirst(value));
    ASSERT_EQ(new_node.second, false);
  }

  ASSERT_EQ(ubst.GetSize(), size);
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest5) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  ASSERT_EQ(ubst.GetSize(), size);
}

TEST_F(TreeUnitTestSuite, InsertTreeUnstrictTest6) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    ubst_dupl.Insert(value, &value);
  }

  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ubst_dupl.Insert(value, &value);
  }

  ASSERT_EQ(ubst_dupl.GetSize(), 3 * size);
}

TEST_F(TreeUnitTestSuite, CopyUnstrictTreeTest1) {
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  UnstrictIntTree bst2 = ubst;

  for (int32_t& value : values) {
    ASSERT_TRUE(ubst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(ubst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, CopyTreeUnstrictTest2) {
  UnstrictIntTree bst2{};
  std::vector<int32_t> values(values_random);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  bst2 = ubst;

  for (int32_t& value : values) {
    ASSERT_TRUE(ubst.Contains(value));
    ASSERT_TRUE(bst2.Contains(value));
    ASSERT_NE(ubst.FindFirst(value), bst2.FindFirst(value));
  }
}

TEST_F(TreeUnitTestSuite, DeleteTreeUnstrictTest1) {
  std::vector<std::string> values{"test", "test1", "t", "_", "", "r", "r", "abcdef", "1"};

  for (std::string& value : values) {
    ubst_str.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (std::string& value : values) {
    ubst_str.Delete(ubst_str.FindFirst(value));
  }

  ASSERT_EQ(ubst_str.GetRoot(), nullptr);
  ASSERT_EQ(ubst_str.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteUnstrictTreeTest2) {
  size_t size = 10000;
  std::vector<int32_t> values = GetRandomNumbers(size);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ubst.Delete(ubst.FindFirst(value));
  }

  ASSERT_EQ(ubst.GetRoot(), nullptr);
  ASSERT_EQ(ubst.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, DeleteUnstrictTreeTest3) {
  std::vector<int32_t> values(values_random);
  values.insert(values.end(), values_random.begin(), values_random.end());
  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ubst_dupl.Insert(value, &value);
  }

  std::shuffle(values.begin(), values.end(), rng);

  for (int32_t& value : values) {
    ubst_dupl.Delete(ubst_dupl.FindFirst(value));
  }

  ASSERT_EQ(ubst_dupl.GetRoot(), nullptr);
  ASSERT_EQ(ubst_dupl.GetSize(), 0);
}

TEST_F(TreeUnitTestSuite, FindNextUnstrictTreeTest1) {
  std::vector<int32_t> values(values_unique);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_lower = std::lower_bound(values.begin(), values.end(), i);
    auto* bst_find = dynamic_cast<UnstrictIntTree::NodeType*>(ubst.FindFirst(i));
    auto* bst_next = dynamic_cast<UnstrictIntTree::NodeType*>(ubst.FindNext(i));
    if (vector_lower == values.end()) {
      ASSERT_EQ(bst_find, ubst.GetEnd());
      ASSERT_EQ(bst_next, ubst.GetEnd());
    } else if (bst_find != nullptr) {
      ASSERT_EQ(bst_find->key, *vector_lower);
    } else {
      ASSERT_EQ(bst_next->key, *vector_lower);
    }
  }
}

TEST_F(TreeUnitTestSuite, FindNextUnstrictTreeTest2) {
  std::vector<int32_t> values(values_unique);

  for (int32_t& value : values) {
    ubst.Insert(value, &value);
  }

  for (int32_t i = 0; i < 4 * size; ++i) {
    auto vector_upper = std::upper_bound(values.begin(), values.end(), i);
    auto* bst_next = dynamic_cast<UnstrictIntTree::NodeType*>(ubst.FindNext(i));
    if (vector_upper == values.end()) {
      ASSERT_EQ(bst_next, ubst.GetEnd());
    } else {
      std::cout << (bst_next->key == *vector_upper ? "" : std::to_string(i) + "\n");
      ASSERT_EQ(bst_next->key, *vector_upper);
    }
  }
}
