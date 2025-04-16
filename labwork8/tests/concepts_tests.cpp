#include <vector>
#include <set>

#include "lib/bst/BST.hpp"
#include <gtest/gtest.h>
#include "custom_classes.hpp"

using namespace bialger;

TEST(ConceptsTestSuite, IsIteratorTest1) {
  bool vector_it_int = InputIterator<std::vector<int32_t>::iterator, int32_t>;
  bool vector_cit_int = InputIterator<std::vector<int32_t>::const_iterator, int32_t>;
  bool set_it_int = InputIterator<std::set<int32_t>::iterator, int32_t>;
  bool set_cit_int = InputIterator<std::set<int32_t>::const_iterator, int32_t>;
  bool int_ptr = InputIterator<int32_t*, int32_t>;
  bool string_cptr = InputIterator<const std::string*, std::string>;
  ASSERT_TRUE(vector_it_int);
  ASSERT_TRUE(vector_cit_int);
  ASSERT_TRUE(set_it_int);
  ASSERT_TRUE(set_cit_int);
  ASSERT_TRUE(int_ptr);
  ASSERT_TRUE(string_cptr);
}

TEST(ConceptsTestSuite, IsIteratorTest2) {
  bool vector_it_int = Iterable<std::vector<int32_t>::iterator, int32_t>;
  bool int_int = Iterable<int32_t, int32_t>;
  bool set_it_int = Iterable<std::set<int32_t>::iterator, int32_t>;
  bool string_it_int = Iterable<std::string::iterator, int32_t>;
  ASSERT_FALSE(vector_it_int);
  ASSERT_FALSE(int_int);
  ASSERT_FALSE(set_it_int);
  ASSERT_FALSE(string_it_int);
}

TEST(ConceptsTestSuite, IsIteratorTest3) {
  bool bst_it = InputIterator<BST<int32_t>::iterator, int32_t>;
  bool bst_cit = InputIterator<BST<int32_t>::const_iterator, int32_t>;
  bool bst_rit = InputIterator<BST<int32_t>::reverse_iterator, int32_t>;
  bool bst_crit = InputIterator<BST<int32_t>::const_reverse_iterator, int32_t>;
  ASSERT_TRUE(bst_it);
  ASSERT_TRUE(bst_cit);
  ASSERT_TRUE(bst_rit);
  ASSERT_TRUE(bst_crit);
}

TEST(ConceptsTestSuite, IsIterableTest1) {
  bool vector_int = Iterable<std::vector<int32_t>, int32_t>;
  bool set_string = Iterable<std::set<std::string>, std::string>;
  bool string_char = Iterable<std::string, char>;
  ASSERT_TRUE(vector_int);
  ASSERT_TRUE(set_string);
  ASSERT_TRUE(string_char);
}

TEST(ConceptsTestSuite, IsIterableTest2) {
  bool vector_it = Iterable<std::vector<int32_t>::iterator, int32_t>;
  bool int_int = Iterable<int32_t, int32_t>;
  bool set_it = Iterable<std::set<int32_t>::iterator, int32_t>;
  ASSERT_FALSE(vector_it);
  ASSERT_FALSE(int_int);
  ASSERT_FALSE(set_it);
}

TEST(ConceptsTestSuite, IsIterableTest3) {
  bool bst_int = Iterable<BST<int32_t>, int32_t>;
  bool bst_string = Iterable<BST<std::string>, std::string>;
  ASSERT_TRUE(bst_int);
  ASSERT_TRUE(bst_string);
}

TEST(ConceptsTestSuite, IsComparatorTest1) {
  bool less_int = Comparator<std::less<>, int32_t>;
  bool equal_string = Comparator<std::equal_to<std::string>, std::string>;
  bool less_eq_set = Comparator<std::less_equal<>, std::set<int32_t>>;
  ASSERT_TRUE(less_int);
  ASSERT_TRUE(equal_string);
  ASSERT_TRUE(less_eq_set);
}

TEST(ConceptsTestSuite, IsComparatorTest2) {
  bool less_int_string = Comparator<std::less<int32_t>, std::string>;
  bool equal_string_charset = Comparator<std::equal_to<std::string>, std::set<char>>;
  bool int_int = Comparator<int32_t, int32_t>;
  ASSERT_FALSE(less_int_string);
  ASSERT_FALSE(equal_string_charset);
  ASSERT_FALSE(int_int);
}

TEST(ConceptsTestSuite, IsComparatorTest3) {
  bool less_eq_bst = Comparator<std::less_equal<>, BST<int32_t>>;
  ASSERT_TRUE(less_eq_bst);
}

TEST(ConceptsTestSuite, AreComparableTest1) {
  bool int_long_less = ComparableType<int64_t, int32_t, std::less<>>;
  bool char_size_less = ComparableType< char, size_t, std::less<>>;
  bool uint16_int64_equals = ComparableType<uint16_t, int64_t, std::equal_to<>>;
  bool strings_less_eq = ComparableType<std::string, std::string, std::less_equal<>>;
  bool container_int = ComparableType<std::vector<std::string>, int32_t, LessContainer<void>>;
  ASSERT_TRUE(int_long_less);
  ASSERT_TRUE(char_size_less);
  ASSERT_TRUE(uint16_int64_equals);
  ASSERT_TRUE(strings_less_eq);
  ASSERT_TRUE(container_int);
}

TEST(ConceptsTestSuite, AreComparableTest2) {
  bool ints_string_less = ComparableType<std::string, int32_t, std::less<int32_t>>;
  bool bst_vector_less = ComparableType<std::vector<char>, BST<std::string>, std::less<>>;
  bool string_int64_equals = ComparableType<int64_t, std::string, std::equal_to<>>;
  bool int_strings_less_eq = ComparableType<int32_t, int32_t, std::less_equal<std::string>>;
  ASSERT_FALSE(ints_string_less);
  ASSERT_FALSE(bst_vector_less);
  ASSERT_FALSE(string_int64_equals);
  ASSERT_FALSE(int_strings_less_eq);
}
