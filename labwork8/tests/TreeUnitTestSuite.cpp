#include "TreeUnitTestSuite.hpp"
#include "test_functions.hpp"

using namespace bialger;

void TreeUnitTestSuite::SetUp() {
  values_random = GetRandomNumbers(size);
  values_unique = std::vector<int32_t>(size);

  for (int32_t i = 0; i < distance * size; i += static_cast<int32_t>(distance)) {
    values_unique[i / distance] = i + std::abs(static_cast<int32_t>(values_random[i / distance] % distance));
  }
}

void TreeUnitTestSuite::TearDown() {
  Test::TearDown();
}
