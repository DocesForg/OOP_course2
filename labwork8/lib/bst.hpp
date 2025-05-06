#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <set>

template <typename T>
struct Node {
    T data_;
    Node<T>* left_;
    Node<T>* right_;
    Node<T>* parent_;

    Node()
        : data_(), left_(nullptr), right_(nullptr), parent_(nullptr) {}
    Node(T& data)
        : data_(data), left_(nullptr), right_(nullptr), parent_(nullptr) {}
};

template <typename T, typename Compare, typename Allocator>
class BST {
   public:
    using NodeAllocator = typename std::allocator_traits<
        Allocator>::template rebind_alloc<Node<T>>;

   private:
    Node<T>* root_;
    Compare comp_;
    NodeAllocator alloc_;

    void clear_(Node<T>*& node) {
        if (node == nullptr) {
            return;
        }
        clear_(node->left_);
        clear_(node->right_);
        std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
        alloc_.deallocate(node, 1);
        node = nullptr;
    }

    Node<T>* insert_(Node<T>*& node, T data, Node<T>* parent = nullptr) {
        if (node == nullptr) {
            node = alloc_.allocate(1);
            std::allocator_traits<NodeAllocator>::construct(alloc_, node, data);
            node->parent_ = parent;
            return node;
        }
        if (comp_(data, node->data_)) {
            return insert_(node->left_, data, node);
        } else {
            return insert_(node->right_, data, node);
        }
    }

    [[nodiscard]] Node<T>* find_(Node<T>* node, T data) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == data) {
            return node;
        }
        if (comp_(data, node->data_)) {
            return find_(node->left_, data);
        } else {
            return find_(node->right_, data);
        }
        return nullptr;
    }

    [[nodiscard]] Node<T>* lower_bound_(Node<T>* node, T data) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == data || !comp_(node->data_, data)) {
            Node<T>* temp = lower_bound_(node->left_, data);
            if (temp == nullptr) {
                return node;
            }
            return temp;
        }
        return lower_bound_(node->right_, data);
    }

    [[nodiscard]] Node<T>* upper_bound_(Node<T>* node, T data) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data_ == data || comp_(node->data_, data)) {
            return upper_bound_(node->right_, data);
        }
        Node<T>* temp = upper_bound_(node->left_, data);
        if (temp == nullptr) {
            return node;
        }
        return temp;
    }

    void swap(Node<T>* a, Node<T>* b) {
        if (a == b) {
            return;
        }

        if (a->parent_ == nullptr) {
            root_ = b;
        } else if (a->parent_->left_ == a) {
            a->parent_->left_ = b;
        } else {
            a->parent_->right_ = b;
        }

        if (b->parent_ == nullptr) {
            root_ = a;
        } else if (b->parent_->left_ == b) {
            b->parent_->left_ = a;
        } else {
            b->parent_->right_ = a;
        }

        std::swap(a->parent_, b->parent_);
        std::swap(a->left_, b->left_);
        std::swap(a->right_, b->right_);

        if (a->left_ != nullptr) {
            a->left_->parent_ = a;
        }
        if (a->right_ != nullptr) {
            a->right_->parent_ = a;
        }
        if (b->left_ != nullptr) {
            b->left_->parent_ = b;
        }
        if (b->right_ != nullptr) {
            b->right_->parent_ = b;
        }
    }

   public:
    BST() : root_(nullptr) {}
    ~BST() { clear_(root_); }

    Node<T>* insert(T data) { return insert_(root_, data); }

    void remove(T data) {
        Node<T>* node = find(data);
        remove_node(node);
    }
    void remove_node(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        if (node->left_ == nullptr && node->right_ == nullptr) {
            if (node->parent_ == nullptr) {
                root_ = nullptr;
                std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
                alloc_.deallocate(node, 1);
                return;
            }
            if (node->parent_->left_ == node) {
                node->parent_->left_ = nullptr;
            } else {
                node->parent_->right_ = nullptr;
            }
            std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
            alloc_.deallocate(node, 1);
            return;
        }
        if (node->left_ == nullptr) {
            if (node->parent_ == nullptr) {
                root_ = node->right_;
                node->right_->parent_ = nullptr;
                std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
                alloc_.deallocate(node, 1);
                return;
            }
            if (node->parent_->left_ == node) {
                node->parent_->left_ = node->right_;
            } else {
                node->parent_->right_ = node->right_;
            }
            node->right_->parent_ = node->parent_;
            std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
            alloc_.deallocate(node, 1);
            return;
        }
        if (node->right_ == nullptr) {
            if (node->parent_ == nullptr) {
                root_ = node->left_;
                node->left_->parent_ = nullptr;
                std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
                alloc_.deallocate(node, 1);
                return;
            }
            if (node->parent_->left_ == node) {
                node->parent_->left_ = node->left_;
            } else {
                node->parent_->right_ = node->left_;
            }
            node->left_->parent_ = node->parent_;
            std::allocator_traits<NodeAllocator>::destroy(alloc_, node);
            alloc_.deallocate(node, 1);
            return;
        }
        Node<T>* temp = node->right_;
        while (temp->left_ != nullptr) {
            temp = temp->left_;
        }
        swap(node, temp);
        remove_node(node);
    }

    void clear() { clear_(root_); }

    [[nodiscard]] Node<T>* find(T data) const { return find_(root_, data); }
    [[nodiscard]] Node<T>* lower_bound(T data) const { return lower_bound_(root_, data); }
    [[nodiscard]] Node<T>* upper_bound(T data) const { return upper_bound_(root_, data); }
    [[nodiscard]] Node<T>* root() const { return root_; }
};

template <typename T>
class PreOrder {
   public:
    [[nodiscard]] static Node<T>* next(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            return node;
        }
        if (node->left_ != nullptr) {
            return node->left_;
        }
        if (node->right_ != nullptr) {
            return node->right_;
        }
        Node<T>* parent = node->parent_;
        while (parent != nullptr) {
            if (node == parent->left_ && parent->right_ != nullptr) {
                return parent->right_;
            }
            node = parent;
            parent = parent->parent_;
        }
        return nullptr;
    }

    [[nodiscard]] static Node<T>* prev(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            while (node->right_ != nullptr || node->left_ != nullptr) {
                if (node->right_ != nullptr) {
                    node = node->right_;
                } else {
                    node = node->left_;
                }
            }
            return node;
        }
        if (node == root) {
            return nullptr;
        }
        Node<T>* parent = node->parent_;
        if (parent->right_ == node && parent->left_ != nullptr) {
            node = parent->left_;
            while (node->right_ != nullptr || node->left_ != nullptr) {
                if (node->right_ != nullptr) {
                    node = node->right_;
                } else {
                    node = node->left_;
                }
            }
            return node;
        }
        return parent;
    }
};

template <typename T>
class InOrder {
   public:
    [[nodiscard]] static Node<T>* next(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            while (node->left_ != nullptr) {
                node = node->left_;
            }
            return node;
        }
        if (node->right_ != nullptr) {
            node = node->right_;
            while (node->left_ != nullptr) {
                node = node->left_;
            }
            return node;
        }
        Node<T>* parent = node->parent_;
        while (parent != nullptr && node == parent->right_) {
            node = parent;
            parent = parent->parent_;
        }
        return parent;
    }

    [[nodiscard]] static Node<T>* prev(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            while (node->right_ != nullptr) {
                node = node->right_;
            }
            return node;
        }
        if (node->left_ != nullptr) {
            node = node->left_;
            while (node->right_ != nullptr) {
                node = node->right_;
            }
            return node;
        }
        Node<T>* parent = node->parent_;
        while (parent != nullptr && node == parent->left_) {
            node = parent;
            parent = parent->parent_;
        }
        return parent;
    }
};

template <typename T>
class PostOrder {
   public:
    [[nodiscard]] static Node<T>* next(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            while (node->left_ != nullptr || node->right_ != nullptr) {
                if (node->left_ != nullptr) {
                    node = node->left_;
                } else {
                    node = node->right_;
                }
            }
            return node;
        }
        if (node == root) {
            return nullptr;
        }
        Node<T>* parent = node->parent_;
        if (parent->right_ == node || parent->right_ == nullptr) {
            return parent;
        }
        node = parent->right_;
        while (node->left_ != nullptr || node->right_ != nullptr) {
            if (node->left_ != nullptr) {
                node = node->left_;
            } else {
                node = node->right_;
            }
        }
        return node;
    }

    [[nodiscard]] static Node<T>* prev(Node<T>* node, Node<T>* root) {
        if (root == nullptr) {
            return nullptr;
        }
        if (node == nullptr) {
            node = root;
            return node;
        }
        if (node->right_ != nullptr) {
            return node->right_;
        }
        if (node->left_ != nullptr) {
            return node->left_;
        }
        Node<T>* parent = node->parent_;
        while (parent != nullptr) {
            if (node == parent->right_ && parent->left_ != nullptr) {
                return parent->left_;
            }
            node = parent;
            parent = parent->parent_;
        }
        return nullptr;
    }
};