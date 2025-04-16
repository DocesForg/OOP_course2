#include "test_functions.hpp"
#include "BstUnitTestSuite.hpp"

void BstUnitTestSuite::SetUp() {
  values = GetRandomNumbers(size);
  values_unique = std::vector<int32_t>(size);
  sample_values = {1, 2, 3, 4, 5};

  for (int32_t i = 0; i < distance * size; i += static_cast<int32_t>(distance)) {
    values_unique[i / distance] = i + std::abs(static_cast<int32_t>(values[i / distance] % distance));
  }

  std::shuffle(values_unique.begin(), values_unique.end(), rng);
}

void BstUnitTestSuite::TearDown() {
  Test::TearDown();
}
