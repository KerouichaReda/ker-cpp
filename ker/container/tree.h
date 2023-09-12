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
/// Link:
/// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
/// https://devblogs.microsoft.com/oldnewthing/20230807-00/?p=108562
#include <memory>
#include <iterator>
namespace ker {
enum class rb_tree_color : bool { black = true, red = false };
struct rb_tree_node_base {
    // typedef
    typedef rb_tree_node_base* base_ptr;
    typedef const rb_tree_node_base* const_base_ptr;

    base_ptr s_minimum(base_ptr node);
    const_base_ptr s_minimum(const_base_ptr node);
    rb_tree_color color_;
    rb_tree_node_base* parent_;
    rb_tree_node_base* left_;
    rb_tree_node_base* right_;
};

template <class key_compare>
struct rb_tree_key_compare {
    key_compare key_compare_;
    rb_tree_key_compare() : key_compare_() {}
    rb_tree_key_compare(const key_compare& other_key_compare) : key_compare_(other_key_compare) {}
};

struct rb_tree_header {
    rb_tree_node_base header_;
    std::size_t node_count_;
    rb_tree_header() {
        header_.color_ = rb_tree_color::red;
        reset();
    }
    void reset() {
        header_.parent_ = nullptr;
        header_.left_ = &header_;
        header_.right_ = &header_;
    }
};

template <class val>
struct rb_tree_node : rb_tree_node_base {
    val value_;
    val* valptr() { return &value; }
};

class rb_tree {
   private:
    rb_tree_node_base header_;
    std::size_t size_;
};

//---------------------------------DECLARATION-----------------------------------------
typename rb_tree_node_base::base_ptr rb_tree_node_base::s_minimum(rb_tree_node_base::base_ptr node) { return node; }
typename rb_tree_node_base::const_base_ptr rb_tree_node_base::s_minimum(rb_tree_node_base::const_base_ptr node) {
    return node;
}
}