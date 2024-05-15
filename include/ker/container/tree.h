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
    void balance_helper();

   private:
    tree_node<data>* allocate(const data&, tree_node<data>* parrent);
    void deallocate(tree_node<data>*);
    tree_node<data>* insert_impl(tree_node<data>*, tree_node<data>*, const data&);
    void print_impl(tree_node<data>* root);
    tree_node<data>* update_header(tree_node<data>*);

    std::int64_t get_height(tree_node<data>*);
    bool is_balanced_impl(tree_node<data>*);
    void balance(tree_node<data>*&);
    tree_node<data>* rotate_left(tree_node<data>*&);
    tree_node<data>* rotate_right(tree_node<data>*&);
    color get_color(tree_node<data>*);

   private:
    tree_node<data> header_;
    tree_node<data>* NIL = &header_;
    std::function<bool(data, data)> compare_ = [](data a, data b) { return a < b; };
};
template <class data>
tree<data>::tree() : header_(&header_){};
template <class data>
void tree<data>::insert(const data& val) {
    header_.parent_ = insert_impl(header_.parent_, &header_, val);
}
template <class data>
typename tree_node<data>* tree<data>::insert_impl(tree_node<data>* root, tree_node<data>* parent, const data& val) {
    if (root == NIL) {
        root = update_header(allocate(val, parent));
    }
    if (compare_(val, root->data_)) {
        root->left_ = insert_impl(root->left_, root, val);
    } else if (compare_(root->data_, val)) {
        root->right_ = insert_impl(root->right_, root, val);
    }
    balance(root);
    return root;
}

template <class data>
void tree<data>::balance(tree_node<data>*& root) {
    if(
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
    print_impl(header_.parent_);
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
void tree<data>::print_impl(tree_node<data>* root) {
    if (root == NIL) return;
    print_impl(root->left_);
    std::cout << root->data_ << " ";
    print_impl(root->right_);
}
template <class data>
bool tree<data>::is_balanced_impl(tree_node<data>* root) {
    return root == NIL ? true
                       : is_balanced_impl(root->left_) && is_balanced_impl(root->right_) &&
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
    tree_node<data>* temp = root->right_->left_;
    tree_node<data>* right = root->right_;
    right->left_ = root;
    right->parent_ = parent;
    root->right_ = temp;
    root->parent_ = right;
    return right;
}
template <class data>
tree_node<data>* tree<data>::rotate_right(tree_node<data>*& root) {
    tree_node<data>* parent = root->parent_;
    tree_node<data>* temp = root->left_->right_;
    tree_node<data>* left = root->left_;
    left->right_ = root;
    left->parent_ = parent;
    root->left_ = temp;
    root->parent_ = left;
    return left;
}

template <class data>
void tree<data>::balance_helper() {
    balance(header_.parent_);
}
template <class data>
color tree<data>::get_color(tree_node<data>* root) {
    return root == NIL || root->color_ == color::black ? color::black : color::red;
}
}  // namespace container
}  // namespace ker
#endif  // KER_CONTAINER_TREE_H
