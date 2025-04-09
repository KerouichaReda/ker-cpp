/// @file tree.h
/// @author Reda KEROUCIHA <kerouicha_reda@outlook.com>
/// @section LICENSE
/// MIT License
///
/// Copyright (c) 2024 Reda Kerouicha <kerouicha_reda@outlook.com>
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to
/// deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE
/// SOFTWARE.
///
/// https://www.geeksforgeeks.org/introduction-to-red-black-tree/

#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

#ifndef KER_CONTAINER_TREE_H
#define KER_CONTAINER_TREE_H
namespace ker {
namespace container {

enum class color : bool { red = false, black = true };
template <class data>
struct tree_node {
    tree_node* parent_;
    tree_node* left_;
    tree_node* right_;
    color color_ = color::red;
    data data_{};
    tree_node(tree_node* NIL) : parent_(NIL), left_(NIL), right_(NIL) {}
    tree_node(const data& val, tree_node* parent, tree_node* NIL)
        : parent_(parent), left_(NIL), right_(NIL), data_(val) {}
    tree_node(const data& val, tree_node* parent, tree_node* left, tree_node* right)
        : data_(val), parent_(parent), left_(left), right_(right) {}
    tree_node(tree_node* parent, tree_node* left, tree_node* right) : parent_(parent), left_(left), right_(right) {}
};
template <class data>
class tree {
   public:
    tree();
    void insert(const data& val);
    void print();
    bool is_balanced();

   private:
    tree_node<data>* allocate(const data&, tree_node<data>* parrent);
    void deallocate(tree_node<data>*);
    tree_node<data>* insert_impl(tree_node<data>*, tree_node<data>*, tree_node<data>*&);
    void in_order(tree_node<data>* root);
    void pre_order(tree_node<data>* root);
    tree_node<data>* update_header(tree_node<data>*);

    std::int64_t get_height(tree_node<data>*);
    bool is_balanced_impl(tree_node<data>*);
    tree_node<data>* insert_fixup(tree_node<data>*);
    tree_node<data>* rotate_left(tree_node<data>*&);
    tree_node<data>* rotate_right(tree_node<data>*&);
    color get_color(tree_node<data>*);

   private:
    tree_node<data> header_;
    tree_node<data>* NIL = &header_;
    std::function<bool(data, data)> compare_ = [](data a, data b) { return a < b; };
};
template <class data>
tree<data>::tree()
    : header_(&header_) {
    header_.data_ = data{};
};
template <class data>
void tree<data>::insert(const data& val) {
    tree_node<data>* node = allocate(val, NIL);
    header_.parent_ = insert_impl(header_.parent_, NIL, node);
    header_.parent_ = insert_fixup(node);
}
template <class data>
typename tree_node<data>* tree<data>::insert_impl(tree_node<data>* root, tree_node<data>* parent,
                                                  tree_node<data>*& node) {
    if (root == NIL) {
        root = node;
        root->parent_ = parent;
    } else if (compare_(node->data_, root->data_)) {
        root->left_ = insert_impl(root->left_, root, node);
    } else if (compare_(root->data_, node->data_)) {
        root->right_ = insert_impl(root->right_, root, node);
    } else {
        deallocate(node);
        node = NIL;
    }
    return root;
}

template <class data>
typename tree_node<data>* tree<data>::insert_fixup(tree_node<data>* node) {
    tree_node<data>* root = header_.parent_;
    while (node != NIL && get_color(node->parent_) == color::red) {
        tree_node<data>* parent = node->parent_;
        tree_node<data>* grandpa = node->parent_->parent_;
        bool is_parent_left_child = grandpa->left_ == parent;
        tree_node<data>* uncle = is_parent_left_child ? grandpa->right_ : grandpa->left_;
        if (is_parent_left_child) {
            if (get_color(uncle) == color::red) {
                parent->color_ = color::black;
                uncle->color_ = color::black;
                grandpa->color_ = color::red;
                node = grandpa;
            } else {
                if (node == parent->right_) {
                    node = rotate_left(parent);
                }
                parent = rotate_right(grandpa);
                parent->color_ = color::black;
                grandpa->color_ = color::red;
                root = parent;
            }
        } else {
            if (get_color(uncle) == color::red) {
                parent->color_ = color::black;
                uncle->color_ = color::black;
                grandpa->color_ = color::red;
                root = grandpa;
            } else {
                if (root == parent->left_) {
                    node = rotate_right(parent);
                }
                parent = rotate_left(grandpa);
                parent->color_ = color::black;
                grandpa->color_ = color::red;
                root = parent;
            }
        }
    }
    header_.parent_->color_ = color::black;
    return root;
}

template <class data>
typename tree_node<data>* tree<data>::allocate(const data& data_, tree_node<data>* parent) {
    return new tree_node(data_, parent, NIL);
}
template <class data>
void tree<data>::deallocate(tree_node<data>* root) {
    delete root;
}
template <class data>
void tree<data>::print() {
    pre_order(header_.parent_);
    std::cout << '\n';
    in_order(header_.parent_);
    std::cout << '\n';
}

template <class data>
tree_node<data>* tree<data>::update_header(tree_node<data>* new_node) {
    if (header_.left_ == NIL || compare_(new_node->data_, header_.left_->data_)) {
        header_.left_ = new_node;
    }
    if (header_.right_ == NIL || compare_(header_.right_->data_, new_node->data_)) {
        header_.right_ = new_node;
    }
    return new_node;
}
template <class data>
void tree<data>::in_order(tree_node<data>* root) {
    if (root == NIL) return;
    in_order(root->left_);
    std::cout << root->data_ << " ";
    in_order(root->right_);
}
template <class data>
void tree<data>::pre_order(tree_node<data>* root) {
    if (root == NIL) return;
    std::cout << root->data_ << " ";
    pre_order(root->left_);
    pre_order(root->right_);
}

template <class data>
bool tree<data>::is_balanced_impl(tree_node<data>* root) {
    return root == NIL ? true : is_balanced_impl(root->left_) && is_balanced_impl(root->right_) &&
                                    std::abs(get_height(root->left_) - get_height(root->right_)) <= 1;
}
template <class data>
bool tree<data>::is_balanced() {
    return is_balanced_impl(header_.parent_);
}
template <class data>
std::int64_t tree<data>::get_height(tree_node<data>* root) {
    return root == NIL ? 0 : 1 + std::max(get_height(root->left_), get_height(root->right_));
}

template <class data>
tree_node<data>* tree<data>::rotate_left(tree_node<data>*& root) {
    tree_node<data>* parent = root->parent_;
    tree_node<data>* right = root->right_;
    tree_node<data>* temp = right->left_;
    right->left_ = root;
    right->parent_ = parent;
    if (parent != NIL && parent->left_ == root) {
        parent->left_ = right;
    } else if (parent != NIL && parent->right_ == root) {
        parent->right_ = right;
    }
    root->right_ = temp;
    root->parent_ = right;
    return right;
}
template <class data>
tree_node<data>* tree<data>::rotate_right(tree_node<data>*& root) {
    tree_node<data>* parent = root->parent_;
    tree_node<data>* left = root->left_;
    tree_node<data>* temp = left->right_;
    left->right_ = root;
    left->parent_ = parent;
    if (parent != NIL && parent->left_ == root) {
        parent->left_ = left;
    } else if (parent != NIL && parent->right_ == root) {
        parent->right_ = left;
    }
    root->left_ = temp;
    root->parent_ = left;
    return left;
}

template <class data>
color tree<data>::get_color(tree_node<data>* root) {
    return root == NIL || root->color_ == color::black ? color::black : color::red;
}
}  // namespace container
}  // namespace ker
#endif  // KER_CONTAINER_TREE_H
