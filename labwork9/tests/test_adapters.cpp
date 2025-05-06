#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include "adapters.h"

// Базовые тесты для каждого адаптера
TEST(BasicAdapters, FilterOnly) {
    std::vector<int> v = {10, 20, 30, 40};
    auto result = v | filter([](int x) { return x > 25; });

    std::vector<int> expected{30, 40};
    std::vector<int> actual;
    for(int x : result) actual.push_back(x);
    ASSERT_EQ(expected, actual);
}

TEST(BasicAdapters, TransformOnly) {
    std::list<int> lst = {1, 2, 3};
    auto result = lst | transform([](int x) { return x * 10; });

    // Явное копирование через цикл
    std::vector<int> actual;
    for(int x : result) {
        actual.push_back(x);
    }

    std::vector<int> expected{10, 20, 30};
    ASSERT_EQ(expected, actual);
}

TEST(BasicAdapters, DropOnly) {
    std::vector<int> v = {100, 200, 300};
    auto result = v | drop(1);

    std::vector<int> actual;
    for(int x : result) actual.push_back(x);
    ASSERT_EQ((std::vector<int>{200, 300}), actual);
}

TEST(BasicAdapters, ReverseOnly) {
    std::list<std::string> lst = {"a", "b", "c"};
    auto reversed = lst | reverse();

    std::vector<std::string> actual(reversed.begin(), reversed.end());
    ASSERT_EQ((std::vector<std::string>{"c", "b", "a"}), actual);
}

// Тест для пограничных случаев

TEST(EdgeCases, DropAllElements) {
    std::list<int> lst = {10, 20};
    auto result = lst | drop(2);

    EXPECT_TRUE(result.begin() == result.end());
}

// Тесты для разных типов контейнеров
TEST(ContainerTypes, DequeWithTransform) {
    std::deque<int> dq = {3, 4, 5};
    auto result = dq | transform([](int x) { return x - 2; });

    std::vector<int> actual(result.begin(), result.end());
    ASSERT_EQ((std::vector<int>{1, 2, 3}), actual);
}

// Простые комбинации адаптеров
TEST(Combinations, FilterTransform) {
    std::vector<int> v = {1, 2, 3, 4};
    auto result = v | filter([](int x) { return x % 2 == 0; })
                   | transform([](int x) { return x / 2; });

    std::vector<int> actual(result.begin(), result.end());
    ASSERT_EQ((std::vector<int>{1, 2}), actual);
}

TEST(Combinations, DropTransform) {
    std::vector<int> v = {5, 4, 3, 2};
    auto result = v | drop(1) | transform([](int x) { return x * 10; });

    std::vector<int> actual(result.begin(), result.end());
    ASSERT_EQ((std::vector<int>{40, 30, 20}), actual);
}

// Тесты для строк
TEST(StringTests, TransformStrings) {
    std::vector<std::string> v = {"a", "bc", "def"};
    auto result = v | transform([](const std::string& s) { return s.size(); });

    std::vector<size_t> actual(result.begin(), result.end());
    ASSERT_EQ((std::vector<size_t>{1, 2, 3}), actual);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
