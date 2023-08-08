/// @file linear_set.h
/// @author Reda KEROUCIHA <kerouicha_reda@outlook.com>
/// @section LICENSE
/// MIT License
///
/// Copyright (c) 2022 Reda Kerouicha <kerouicha_reda@outlook.com>
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

#ifndef KER_CONTAINER_LINEAR_SET_H
#define KER_CONTAINER_LINEAR_SET_H

#include <functional>
#include <vector>
#include <iterator>
#include <algorithm>
namespace ker {
/// -----------------------------------------------------------------------------
/// ker::linear_set
/// -----------------------------------------------------------------------------
///
/// An 'ker::linear_set<T>' is an ordered set, that use linear search to
/// insert,search and erase
/// adviced to be used for small number of elements to outperform other type set
/// .
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///
///

template <class T> class linear_set  {

public:
  linear_set() {};

  ~linear_set() {};

  void insert(T _element) {
    auto itr = std::find(linear_set_.begin(), linear_set_.end(), [&](T e){return e == _element;});
    if (itr != linear_set_.end()) {
      return;
    }
    linear_set_.push_back(_element);
  }
  /*
  std::size_t count(T &_element) {
    auto itr = std::find(linear_set_.begin(), linear_set_.end(), _element);
    return std::static_cast<std::size_t>(itr != linear_set_.end());
  }
  void erase(T &_element) {
    auto itr = std::find(linear_set_.begin(), linear_set_.end(), _element);
    if (itr != linear_set_.end()) {
      linear_set_.erase(itr);
    }
  }
  void erase(const T &_element) {
    auto itr = std::find(linear_set_.begin(), linear_set_.end(), _element);
    if (itr != linear_set_.end()) {
      linear_set_.erase(itr);
    }
  }
  std::size_t size() { return linear_set_.size(); }
  void clear() { linear_set_.clear(); }
  bool contains(T &_element) {
    return std::find(linear_set_.begin(), linear_set_.end(), _element) !=
           linear_set_.end();
  }
  */
private:
  std::vector<T> linear_set_;
};
}
#endif // KER_CONTAINER_LINEAR_MAP_H