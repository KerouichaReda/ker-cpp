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
#include <iterator>
#include <memory>

#ifndef KER_CONTAINER_TREE_H
#define KER_CONTAINER_TREE_H
namespace ker {
namespace container {

struct tree_node {
    enum class color : bool { red = false, black = true };
    tree_node* parent_ = nullptr;
    tree_node* left_ = nullptr;
    tree_node* right_ = nullptr;
    color color_ = color::red;
    std::int64_t data_{};
    tree_node() {}
    tree_node(const std::int64_t& val, tree_node* parent) : parent_(parent), data_(val) {}
    tree_node(const std::int64_t& val, tree_node* parent, tree_node* left, tree_node* right)
        : data_(val), parent_(parent), left_(left), right_(right) {}
    tree_node(tree_node* parent, tree_node* left, tree_node* right) : parent_(parent), left_(left), right_(right) {}
};

class tree {
   public:
    tree();
    void insert(const std::int64_t& val);

   private:
    tree_node* allocate(const std::int64_t&, tree_node* parrent);
    void deallocate(tree_node*);
    tree_node* update_header(tree_node* root);
    tree_node* insert_impl(tree_node*, const std::int64_t&);

   private:
    tree_node header_;
    std::size_t size_{0};
    std::function<bool(std::int64_t, std::int64_t)> compare_ = [](std::int64_t a, std::int64_t b) { return a < b; };
};

tree::tree() {
    header_.left_ = &header_;
    header_.right_ = &header_;
};

tree_node* tree::update_header(tree_node* root) { return root; }

tree_node* tree::insert_impl(tree_node* root, const std::int64_t& val) {
    if (root == nullptr) return update_header(allocate(val, root));
    if (compare_(val, root->data_)) {
        root->left_ = insert_impl(root->left_, val);
    } else if (compare_(root->data_, val)) {
        root->right_ = insert_impl(root->right_, val);
    }
    return root;
}

void tree::insert(const std::int64_t& val) { header_.parent_ = insert_impl(header_.parent_, val); }

tree_node* tree::allocate(const std::int64_t& data,tree_node* parent) {
    return new tree_node(data,parent);
}

void tree::deallocate(tree_node* root) {
    //root->data_;
    delete root;
}
}  // namespace container
}  // namespace ker
#endif  // KER_CONTAINER_TREE_H
