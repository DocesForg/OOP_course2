#pragma once

#include <cstdint>
#include <initializer_list>
#include <limits>
#include <utility>

#include "bst.hpp"
#include "iterator.hpp"

template <typename T, typename DefaultTraversal, typename Compare,
          typename Allocator, typename>
class OrderedTree {
   public:
    using key_type = T;
    using value_type = T;
    using node_type = Node<value_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using key_compare = Compare;
    using value_compare = Compare;
    using allocator_type = Allocator;

    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    using default_traversal = DefaultTraversal;

    using iterator = TreeIterator<default_traversal, OrderedTree>;
    using const_iterator = TreeIterator<default_traversal, OrderedTree>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    template <typename Traversal>
    using template_iterator = TreeIterator<Traversal, OrderedTree>;
    template <typename Traversal>
    using reverse_template_iterator =
        std::reverse_iterator<template_iterator<Traversal>>;

   private:
    BST<value_type, value_compare, allocator_type> bst_;
    size_t size_ = 0;
    value_compare comp_;
    allocator_type alloc_;

   public:
    OrderedTree() = default;
    OrderedTree(std::initializer_list<value_type> il) {
        for (const auto& data : il) {
            insert(data);
        }
    }
    OrderedTree(const OrderedTree& other) {
        for (auto it = other.cbegin<PreOrder<value_type>>();
             it != other.cend<PreOrder<value_type>>(); it++) {
            insert(*it);
        }
    }
    template <typename InputIt>
    OrderedTree(InputIt first, InputIt last) {
        for (auto it = first; it != last; it++) {
            insert(*it);
        }
    }
    ~OrderedTree() = default;

    template <typename Traversal = default_traversal>
    template_iterator<Traversal> insert(const value_type& data) {
        ++size_;
        return template_iterator<Traversal>(bst_.insert(data), &bst_);
    }
    void insert(std::initializer_list<value_type> il) {
        for (const auto& data : il) {
            insert(data);
        }
    }
    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (auto it = first; it != last; it++) {
            insert(*it);
        }
    }
    size_type erase(const value_type& data) {
        size_type erased = 0;
        while (contains(data)) {
            bst_.remove(data);
            ++erased;
        }
        size_ -= erased;
        return erased;
    }
    template <typename Traversal = default_traversal>
    template_iterator<Traversal> erase(template_iterator<Traversal> position) {
        auto next = position;
        ++next;
        --size_;
        bst_.remove_node(position.node_);
        return next;
    }
    template <typename Traversal = default_traversal>
    template_iterator<Traversal> erase(template_iterator<Traversal> first,
                                       template_iterator<Traversal> last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }
    void merge(OrderedTree& other) {
        for (auto it = other.cbegin<PreOrder<value_type>>();
             it != other.cend<PreOrder<value_type>>(); it++) {
            insert(*it);
        }
        other.clear();
    }
    void clear() {
        bst_.clear();
        size_ = 0;
    }

    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> find(
        const value_type& data) const {
        return template_iterator<Traversal>(bst_.find(data), &bst_);
    }
    [[nodiscard]] bool contains(const value_type& data) {
        return bst_.find(data) != nullptr;
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> lower_bound(
        const value_type& data) const {
        return template_iterator<Traversal>(bst_.lower_bound(data), &bst_);
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> upper_bound(
        const value_type& data) const {
        return template_iterator<Traversal>(bst_.upper_bound(data), &bst_);
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] std::pair<template_iterator<Traversal>,
                            template_iterator<Traversal>>
    equal_range(const value_type& data) const {
        return std::make_pair(lower_bound<Traversal>(data),
                              upper_bound<Traversal>(data));
    }
    [[nodiscard]] size_type count(const value_type& data) const {
        auto pair = equal_range<InOrder<value_type>>(data);
        return std::distance(pair.first, pair.second);
    }

    OrderedTree& swap(OrderedTree& other) {
        std::swap(*this, other);
        return *this;
    }

    [[nodiscard]] size_type size() const { return size_; }
    [[nodiscard]] size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    [[nodiscard]] value_compare key_comp() const { return comp_; }
    [[nodiscard]] value_compare value_comp() const { return comp_; }
    [[nodiscard]] allocator_type get_allocator() const { return alloc_; }

    OrderedTree& operator=(std::initializer_list<value_type> il) {
        clear();
        for (const auto& data : il) {
            insert(data);
        }
        return *this;
    }
    OrderedTree& operator=(const OrderedTree& other) {
        if (this == &other) {
            return *this;
        }
        clear();
        for (auto it = other.cbegin<PreOrder<value_type>>();
             it != other.cend<PreOrder<value_type>>(); it++) {
            insert(*it);
        }
        return *this;
    }
    bool operator==(const OrderedTree& other) const {
        if (size_ != other.size_) {
            return false;
        }
        auto it1 = cbegin<PreOrder<value_type>>();
        auto it2 = other.cbegin<PreOrder<value_type>>();
        while (it1 != cend<PreOrder<value_type>>() &&
               it2 != other.cend<PreOrder<value_type>>()) {
            if (*it1 != *it2) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }
    bool operator!=(const OrderedTree& other) const {
        return !(*this == other);
    }

    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> begin() const {
        return template_iterator<Traversal>(
            Traversal::next(nullptr, bst_.root()), &bst_);
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> end() const {
        return template_iterator<Traversal>(nullptr, &bst_);
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] reverse_template_iterator<Traversal> rbegin() const {
        return reverse_template_iterator<Traversal>(end<Traversal>());
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] reverse_template_iterator<Traversal> rend() const {
        return reverse_template_iterator<Traversal>(begin<Traversal>());
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> cbegin() const {
        return (*this).template begin<Traversal>();
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] template_iterator<Traversal> cend() const {
        return (*this).template end<Traversal>();
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] reverse_template_iterator<Traversal> crbegin() const {
        return (*this).template rbegin<Traversal>();
    }
    template <typename Traversal = default_traversal>
    [[nodiscard]] reverse_template_iterator<Traversal> crend() const {
        return (*this).template rend<Traversal>();
    }
};

template <typename T, typename DefaultTraversal, typename Compare,
          typename Allocator>
void swap(OrderedTree<T, DefaultTraversal, Compare, Allocator>& lhs,
          OrderedTree<T, DefaultTraversal, Compare, Allocator>& rhs) {
    lhs.swap(rhs);
}