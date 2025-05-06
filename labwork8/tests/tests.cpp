#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#include "lib/container.hpp"

using namespace std;

template <typename T>
class simple_bst {
    struct Node {
        T data;
        Node *left, *right;
        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };
    Node *root;
    void insert(Node *&node, T data) {
        if (node == nullptr) {
            node = new Node(data);
            return;
        }
        if (data < node->data) {
            insert(node->left, data);
        } else {
            insert(node->right, data);
        }
    }
    void inorder(Node *node, vector<T> &v) {
        if (node == nullptr) return;
        inorder(node->left, v);
        v.push_back(node->data);
        inorder(node->right, v);
    }
    void preorder(Node *node, vector<T> &v) {
        if (node == nullptr) return;
        v.push_back(node->data);
        preorder(node->left, v);
        preorder(node->right, v);
    }
    void postorder(Node *node, vector<T> &v) {
        if (node == nullptr) return;
        postorder(node->left, v);
        postorder(node->right, v);
        v.push_back(node->data);
    }
    void remove(Node *&node, T data) {
        if (node == nullptr) return;
        if (data < node->data) {
            remove(node->left, data);
        } else if (data > node->data) {
            remove(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node *temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                Node *temp = node;
                node = node->left;
                delete temp;
            } else {
                Node *temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->data = temp->data;
                remove(node->right, temp->data);
            }
        }
    }
    void clear(Node *node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

   public:
    simple_bst() : root(nullptr) {}
    void insert(T data) { insert(root, data); }
    vector<T> inorder() {
        vector<T> v;
        inorder(root, v);
        return v;
    }
    vector<T> preorder() {
        vector<T> v;
        preorder(root, v);
        return v;
    }
    vector<T> postorder() {
        vector<T> v;
        postorder(root, v);
        return v;
    }
    void remove(T data) { remove(root, data); }
    void clear() {
        clear(root);
        root = nullptr;
    }
    ~simple_bst() { clear(); }
};

vector<int32_t> randomize_vector(size_t n, int32_t l = 0, int32_t r = std::numeric_limits<int32_t>::max()) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(l, r);
    std::vector<int32_t> result(n);

    for (int32_t &element : result) {
        element = dist(rng);
    }

    return result;
}

// Traversal tests
TEST(Traversal, InOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.inorder());
}

TEST(Traversal, PreOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin<PreOrder<int32_t>>();
         it != bst.end<PreOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.preorder());
}

TEST(Traversal, PostOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin<PostOrder<int32_t>>();
         it != bst.end<PostOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.postorder());
}

TEST(Traversal, ReverseInOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.rbegin(); it != bst.rend(); it++) {
        v2.push_back(*it);
    }
    vector<int> v3 = bst2.inorder();
    reverse(v3.begin(), v3.end());
    ASSERT_EQ(v2, v3);
}

TEST(Traversal, ReversePreOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.rbegin<PreOrder<int32_t>>();
         it != bst.rend<PreOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    vector<int> v3 = bst2.preorder();
    reverse(v3.begin(), v3.end());
    ASSERT_EQ(v2, v3);
}

TEST(Traversal, ReversePostOrder) {
    OrderedTree<int32_t> bst{50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                             44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                             83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    simple_bst<int> bst2;
    vector<int> v = {50, 40, 30, 20, 10, 31, 39, 38, 37, 36, 45, 43,
                     44, 42, 41, 47, 46, 48, 60, 70, 80, 90, 81, 82,
                     83, 84, 85, 69, 68, 55, 57, 56, 58, 53, 52, 51};
    for (auto i : v) {
        bst2.insert(i);
    }
    stringstream in;
    for (auto it = bst.rbegin<PostOrder<int32_t>>();
         it != bst.rend<PostOrder<int32_t>>(); it++) {
        in << *it << " ";
    }
    vector<int> v2;
    for (auto it = bst.rbegin<PostOrder<int32_t>>();
         it != bst.rend<PostOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    vector<int> v3 = bst2.postorder();
    reverse(v3.begin(), v3.end());
    ASSERT_EQ(v2, v3);
}

// Methods tests
TEST(OrderedTree, Insert) {
    vector<int> v = {3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    OrderedTree<int> bst;
    for (auto i : v) {
        bst.insert(i);
    }
    stringstream in;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 3 3 4 5 5 5 5 6 9 ");
}

TEST(OrderedTree, Insert2) {
    OrderedTree<int> bst{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto it = bst.insert(0);
    ASSERT_EQ(it, bst.begin());
}

TEST(OrderedTree, Insert3) {
    vector<int> v2 = {3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    OrderedTree<int> bst2;
    bst2.insert(v2.begin(), v2.end());
    stringstream in2;
    for (auto it = bst2.begin(); it != bst2.end(); it++) {
        in2 << *it << " ";
    }
    ASSERT_EQ(in2.str(), "1 2 3 3 4 5 5 5 5 6 9 ");
}

TEST(OrderedTree, Size) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    ASSERT_EQ(bst.size(), 11);
}

TEST(OrderedTree, Clear) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    bst.clear();
    ASSERT_EQ(bst.size(), 0);
}

TEST(OrderedTree, Erase) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    auto pair = bst.equal_range(5);
    bst.erase(pair.first, pair.second);
    stringstream in;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 3 3 4 6 9 ");
}

TEST(OrderedTree, Erase2) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    bst.erase(3);
    stringstream in;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 4 5 5 5 5 6 9 ");
}

TEST(OrderedTree, Count) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    ASSERT_EQ(bst.count(5), 4);
    ASSERT_EQ(bst.count(10), 0);
}

TEST(OrderedTree, Find) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    auto it = bst.find(4);
    ASSERT_EQ(*it, 4);
    auto it2 = bst.find(10);
    ASSERT_EQ(it2 == bst.end(), true);
}

TEST(OrderedTree, Contains) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    ASSERT_EQ(bst.contains(5), true);
    ASSERT_EQ(bst.contains(10), false);
}

TEST(OrderedTree, Merge) {
    OrderedTree<int> bst1{4, 5, 6};
    OrderedTree<int> bst2{1, 2, 4, 8, 9};
    bst1.merge(bst2);
    stringstream in;
    for (auto it = bst1.begin(); it != bst1.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 4 4 5 6 8 9 ");
}

TEST(OrderedTree, Equal) {
    OrderedTree<int> bst1{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    OrderedTree<int> bst2{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    OrderedTree<int> bst3{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5, 7};
    ASSERT_EQ(bst1 == bst2, true);
    ASSERT_EQ(bst1 == bst3, false);
}

TEST(OrderedTree, CopyConstructor) {
    OrderedTree<int> bst1{4, 5, 6};
    OrderedTree<int> bst2(bst1);
    stringstream in;
    for (auto it = bst2.begin(); it != bst2.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "4 5 6 ");
}

TEST(OrderedTree, CopyAssignment) {
    OrderedTree<int> bst{3, 1, 4, 5, 5, 9, 2, 6, 5, 3, 5};
    OrderedTree<int> bst2;
    bst2 = bst;
    stringstream in;
    for (auto it = bst2.begin(); it != bst2.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 3 3 4 5 5 5 5 6 9 ");
}

TEST(OrderedTree, Swap) {
    OrderedTree<int> bst1{4, 5, 6};
    OrderedTree<int> bst2{1, 2, 4, 8, 9};
    swap(bst1, bst2);
    stringstream in;
    for (auto it = bst1.begin(); it != bst1.end(); it++) {
        in << *it << " ";
    }
    ASSERT_EQ(in.str(), "1 2 4 8 9 ");
    stringstream in2;
    for (auto it = bst2.begin(); it != bst2.end(); it++) {
        in2 << *it << " ";
    }
    ASSERT_EQ(in2.str(), "4 5 6 ");
}

// Randomized tests
TEST(Randomized, InOrder) {
    vector<int> v = randomize_vector(10000);
    OrderedTree<int> bst;
    simple_bst<int> bst2;
    for (auto i : v) {
        bst.insert(i);
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.inorder());
}

TEST(Randomized, PreOrder) {
    vector<int> v = randomize_vector(10000);
    OrderedTree<int> bst;
    simple_bst<int> bst2;
    for (auto i : v) {
        bst.insert(i);
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin<PreOrder<int32_t>>();
         it != bst.end<PreOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.preorder());
}

TEST(Randomized, PostOrder) {
    vector<int> v = randomize_vector(10000);
    OrderedTree<int> bst;
    simple_bst<int> bst2;
    for (auto i : v) {
        bst.insert(i);
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin<PostOrder<int32_t>>();
         it != bst.end<PostOrder<int32_t>>(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.postorder());
}

TEST(Randomized, Insert) {
    vector<int> v = randomize_vector(10000);
    OrderedTree<int> bst;
    simple_bst<int> bst2;
    for (auto i : v) {
        bst.insert(i);
        bst2.insert(i);
    }
    vector<int> v2;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.inorder());
}

TEST(Randomized, Erase) {
    vector<int> v = randomize_vector(10000, 10, 20);
    OrderedTree<int> bst;
    simple_bst<int> bst2;
    for (auto i : v) {
        bst.insert(i);
        if (i != 12) {
            bst2.insert(i);
        }
    }
    auto pair = bst.equal_range(12);
    bst.erase(pair.first, pair.second);
    vector<int> v2;
    for (auto it = bst.begin(); it != bst.end(); it++) {
        v2.push_back(*it);
    }
    ASSERT_EQ(v2, bst2.inorder());
}