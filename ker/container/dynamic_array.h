/// @file dynamic_array.h
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

#ifndef KER_CONTAINER_DYNAMIC_ARRAY_H
#define KER_CONTAINER_DYNAMIC_ARRAY_H

#include <memory>
#include <iterator>

namespace ker {
const std::size_t max_size_{0xFFFFFFF};
template <class T>
class dynamic_array {
   public:
    // types :
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;

    dynamic_array();
    dynamic_array(std::size_t n);
    dynamic_array(std::size_t n, const T element);
    dynamic_array(const dynamic_array<T>& your_dynamic_array);
    dynamic_array(dynamic_array<T>&& your_dynamic_array);
    dynamic_array(iterator your_begin, iterator your_end);
    dynamic_array(std::initializer_list<T>);
    ~dynamic_array();
    void push_back(const T& element);
    std::size_t max_size() const;
    void pop_back();
    std::size_t size();
    std::size_t capacity();
    bool empty();
    void resize();
    T* data();
    iterator begin();
    iterator end();

    /// itrerator
   private:
    T* allocate(std::size_t n);
    void reallocate();
    void deallocate(T*);
    T* first_ = nullptr;
    T* last_ = nullptr;
    T* end_ = nullptr;  // end of the allocated storage
};
template <class T>
dynamic_array<T>::dynamic_array() {
    first_ = new T[1];
    last_ = first_;
    end_ = first_ + 1;
}

template <class T>
dynamic_array<T>::~dynamic_array() {
    iterator itr = begin();
    for (iterator itr = this->begin(), end = this->end(); itr != end; ++itr) {
    }
    first_->~T();
    deallocate(first_);
}

template <class T>
void dynamic_array<T>::push_back(const T& element) {
    if (last_ == end_) {
        rallocate();
    }
    *last_ = element;
    ++last_;
}

template <class T>
std::size_t dynamic_array<T>::max_size() const {
    return max_size_;
}

template <class T>
std::size_t dynamic_array<T>::size() {
    return last_ - first_;
}
template <class T>
std::size_t dynamic_array<T>::capacity() {
    return end_ - first_;
}

template <class T>
void dynamic_array<T>::pop_back() {
    if (first_ == last_) {
        // assert
    }
    --last_;
}

template <class T>
void dynamic_array<T>::reallocate() {
    T* temp = first_;
    std::size_t current_size_ = size();
    std::size_t new_size_ = current_size_ << 1;
    first_ = allocate(n);
    last_ = first_ + current_size_;
    end_ = first_ + new_size_;
    std::copy(temp, temp + current_size_, first_);
    deallocate(temp);
}
template <class T>
T* dynamic_array<T>::allocate(std::size_t n) {
    return new T[n];
}

template <class T>
dynamic_array<T>::dynamic_array(std::size_t n) {
    first_ = allocate(n);
    last_ = first_ + n;
    end_ = first_ + n;
    std::fill(first_, last_, T{});
}
template <class T>
dynamic_array<T>::dynamic_array(std::size_t n, const T element) {
    first_ = allocate(n);
    last_ = first_ + n;
    end_ = first_ + n;
    std::fill(first_, last_ + 1, element);
}
template <class T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& your_dynamic_array) {
    std::size_t size = your_dynamic_array.size();
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(your_dynamic_array.first_, your_dynamic_array.end_, first_);
}
template <class T>
dynamic_array<T>::dynamic_array(dynamic_array<T>&& your_dynamic_array) {
    std::size_t size = your_dynamic_array.size();
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(std::make_move_iterator(your_dynamic_array.first_), std::make_move_iterator(your_dynamic_array.end_),
              first_);
}
template <class T>
dynamic_array<T>::dynamic_array(dynamic_array<T>::iterator your_begin_itr, dynamic_array<T>::iterator your_end_itr) {
    std::size_t size = your_end_itr - your_begin_itr;
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(your_begin_itr, your_end_itr, first_);
}
template <class T>
dynamic_array<T>::dynamic_array(std::initializer_list<T> init_list) {
    std::size_t size = init_list.size();
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(init_list.begin(), init_list.end(), first_);
}
template <class T>
void dynamic_array<T>::deallocate(T* pointer) {
    delete[] pointer;
}
template <class T>
T* dynamic_array<T>::data() {
    return first_;
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::begin() {
    return first_;
}

template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::end() {
    return last_;
}
template <class T>
bool dynamic_array<T>::empty() {
    return first_ == last_;
}

}  // end ker namespace

#endif  // KER_CONTAINER_DYNAMIC_ARRAY_H