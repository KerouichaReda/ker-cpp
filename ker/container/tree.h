/// @file tree.h
/// @author Reda KEROUCIHA <kerouicha_reda@outlook.com>
/// @section LICENSE
/// MIT License
///
/// Copyright (c) 2023 Reda Kerouicha <kerouicha_reda@outlook.com>
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

#include <memory>
#include <iterator>

#ifndef KER_CONTAINER_TREE_H
#define KER_CONTAINER_TREE_H
namespace ker {
enum class color : bool { red = false, black = true };

template <class payload>
struct tree_node {
    tree_node* parent_ = nullptr;
    tree_node* left_ = nullptr;
    tree_node* right_ = nullptr;
    color color_ = color::red;
    payload data_{};
    tree_node() {}
    tree_node(const payload& val, tree_node* parent) : parent_(parent), data_(val) {}
    tree_node(const payload& val, tree_node* parent, tree_node* left, tree_node* right)
        : data_(val), parent_(parent), left_(left), right_(right) {}
    tree_node(tree_node* parent, tree_node* left, tree_node* right) : parent_(parent), left_(left), right_(right) {}
};

template <class payload, class compare = std::less<payload>>
class tree {
   public:
    typedef tree_node<payload> node;
    tree();
    void insert(const payload& val);

   private:
    node* allocate(const payload&);
    void deallocate(node*);
    node* update_header(node* root);
    node* insert_impl(node*, const payload&);

   private:
    tree_node<payload> header_;
    std::size_t size_{0};
    compare compare_;
};
template <class payload, class compare>
tree<payload, compare>::tree() {
    header_.left_ = &header_;
    header_.right_ = &header_;
};
template <class payload, class compare>
typename tree<payload, compare>::node* tree<payload, compare>::update_header(tree<payload, compare>::node* root) {
    return root;
}

template <class payload, class compare>
typename tree<payload, compare>::node* tree<payload, compare>::insert_impl(tree<payload, compare>::node* root,
                                                                           const payload& val) {
    if (root == nullptr) return update_header(new tree_node<payload>(val, root));
    if (compare_(val, root->data_)) {
        root->left_ = insert_impl(root->left_, val);
    } else if (compare_(root->data_, val)) {
        root->right_ = insert_impl(root->right_, val);
    }
    return root;
}
template <class payload, class compare>
void tree<payload, compare>::insert(const payload& val) {
    header_.parent_ = insert_impl(header_.parent_, val);
}
template <class payload, class compare>
typename tree<payload, compare>::node* tree<payload, compare>::allocate(const payload& data) {
    return new tree_node(data);
}
template <class payload, class compare>
void tree<payload, compare>::deallocate(tree<payload, compare>::node* root) {
    root->data_.~payload();
    delete root;
}
}
#endif  // KER_CONTAINER_DYNAMIC_ARRAY_H
