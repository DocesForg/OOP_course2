#include <iostream>
#include <vector>

#include "../lib/container.hpp"

template <typename T, typename = T::iterator>
void print(const T& container) {
    for (auto it = container.begin(); it != container.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    OrderedTree<int> bst;
    bst = {3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};

    auto it0 = bst.lower_bound(5);
    if (it0 != bst.end()) {
        std::cout << "Lower bound: " << *it0 << std::endl;
    }

    auto pair = bst.equal_range(5);
    std::cout << "Count: " << bst.count(5) << std::endl;
    bst.erase(pair.first, pair.second);

    for (auto it = bst.begin(); it != bst.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Count: " << bst.count(3) << std::endl;
    bst.erase(3);
    for (auto it = bst.begin(); it != bst.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << bst.size() << std::endl;

    OrderedTree<int> bst1{4, 5, 6};
    OrderedTree<int> bst2{1, 2, 4, 8, 9};
    bst1.merge(bst2);
    
    for (auto it = bst1.begin(); it != bst1.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << bst1.size() << std::endl;

    auto it = bst1.upper_bound(8);
    if (it != bst1.end()) {
        std::cout << "Upper bound: " << *it << std::endl;
    }

    auto it1 = bst1.begin<PreOrder<int>>();
    auto it2 = bst1.end<PreOrder<int>>();
    it2--;
    it2--;
    it1++;
    bst1.erase(it2, it1);
    for (auto it = bst1.begin(); it != bst1.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    OrderedTree<int> bst3{1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(bst3);
    return 0;
}