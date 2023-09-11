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
    // Member types :
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef pointer iterator;
    typedef const pointer const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // Member functions
    dynamic_array();
    dynamic_array(std::size_t);
    dynamic_array(std::size_t, const T);
    dynamic_array(const dynamic_array<T>&);
    dynamic_array(dynamic_array<T>&&);
    template <class InputIt>
    dynamic_array(InputIt, InputIt);
    dynamic_array(std::initializer_list<T>);
    ~dynamic_array();
    dynamic_array<T>& operator=(const dynamic_array<T>&);
    dynamic_array<T>& operator=(dynamic_array<T>&&);
    dynamic_array<T>& operator=(std::initializer_list<T>);
    // Element access
    reference at(std::size_t);
    reference operator[](std::size_t);
    reference back();
    reference front();
    pointer data();
    // Iterators
    iterator begin();
    const_iterator cbegin();
    iterator end();
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    reverse_iterator crend() const;

    // Capacity
    bool empty();
    std::size_t size();
    std::size_t max_size() const;
    void reserve(std::size_t);
    std::size_t capacity();
    void shrink_to_fit();

    // Modifiers
    void clear();
    iterator insert(const_iterator, const T&);
    iterator insert(const_iterator, T&&);
    iterator insert(const_iterator, size_type, const T&);
    template <class InputIt>
    iterator insert(const_iterator, InputIt, InputIt);
    iterator insert(const_iterator, std::initializer_list<T>);
    template <class... Args>
    reference emplace(const_iterator, Args&&...);
    iterator erase(iterator);    
    iterator erase(iterator, iterator);  
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    void swap(dynamic_array<T>&);
    void resize(size_type);

   private:
    pointer allocate(std::size_t n);
    void reallocate();
    void deallocate(pointer);
    pointer first_ = nullptr;
    pointer last_ = nullptr;
    pointer end_ = nullptr;  // end of the allocated storage
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
void dynamic_array<T>::push_back(T&& element) {
    if (last_ == end_) {
        rallocate();
    }
    *last_ = std::move(element);
    ++last_;
}
template <class T>
typename dynamic_array<T>::reference dynamic_array<T>::back() {
    return *(last - 1);
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
    (--last_)->~T();
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
dynamic_array<T>::dynamic_array(const dynamic_array<T>& other) {
    std::size_t size = other.size();
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(other.first_, other.end_, first_);
}
template <class T>
dynamic_array<T>::dynamic_array(dynamic_array<T>&& other) {
    std::size_t size = other.size();
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(std::make_move_iterator(other.first_), std::make_move_iterator(other.end_), first_);
}
template <class T>
template <class InputIt>
dynamic_array<T>::dynamic_array(InputIt first, InputIt last) {
    std::size_t size = first - last;
    first_ = allocate(size);
    last_ = first_ + size;
    end_ = last_;
    std::copy(first, last, first_);
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
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T>& your_dynamic_array) {
    if (this == &your_dynamic_array) return your_dynamic_array;
    std::size_t size = your_dynamic_array.size();
    if (size > this->size()) {
        deallocate(first_);
        first_ = allocate(size);
        end_ = last_ + size;
    }
    last_ = first_ + size;
    std::copy(your_dynamic_array.first_, your_dynamic_array.end_, first_);
}
template <class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T>&& your_dynamic_array) {
    std::size_t size = your_dynamic_array.size();
    if (size > this->size()) {
        deallocate(first_);
        first_ = allocate(size);
        end_ = last_ + size;
    }
    last_ = first_ + size;
    std::copy(std::make_move_iterator(your_dynamic_array.first_), std::make_move_iterator(your_dynamic_array.end_),
              first_);
}
template <class T>
dynamic_array<T>& dynamic_array<T>::operator=(std::initializer_list<T> your_list) {
    std::size_t size = your_list.size();
    if (size > this->size()) {
        deallocate(first_);
        first_ = allocate(size);
        end_ = last_ + size;
    }
    last_ = first_ + size;
    std::copy(your_list.first_, your_list.end_, first_);
}
template <class T>
void dynamic_array<T>::clear() {
    for (iterator itr = this->begin(), end = this->end(); itr != end; ++itr) {
        itr->~T();
    }
    last_ = first_;
}
template <class T>
void dynamic_array<T>::swap(dynamic_array<T>& your_dynamic_array) {
    std::swap(this->first_, your_dynamic_array.first_);
    std::swap(this->last_, your_dynamic_array.last_);
    std::swap(this->end, your_dynamic_array.end_);
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
template <class T>
typename dynamic_array<T>::reference dynamic_array<T>::at(std::size_t pos) {
    return *(first_ + pos);
}
template <class T>
typename dynamic_array<T>::reference dynamic_array<T>::operator[](std::size_t) {
    return *(first_ + pos);
}
template <class T>
typename dynamic_array<T>::reference dynamic_array<T>::front() {
    return *first_;
}
template <class T>
typename dynamic_array<T>::const_iterator dynamic_array<T>::cbegin() {
    return first_;
}
template <class T>
void dynamic_array<T>::resize(dynamic_array<T>::size_type) {}

template <class T>
typename dynamic_array<T>::const_iterator dynamic_array<T>::cend() const {
    return last_;
}
template <class T>
typename dynamic_array<T>::reverse_iterator dynamic_array<T>::rbegin() {
    return std::reverse_iterator(last_);
}
template <class T>
typename dynamic_array<T>::const_reverse_iterator dynamic_array<T>::crbegin() const {
    return std::reverse_iterator(last_);
}
template <class T>
typename dynamic_array<T>::reverse_iterator dynamic_array<T>::rend() {
    return std::reverse_iterator(first_);
}
template <class T>
typename dynamic_array<T>::reverse_iterator dynamic_array<T>::crend() const {
    return std::reverse_iterator(first_);
}
template <class T>
void dynamic_array<T>::reserve(std::size_t new_size) {
    std::size_t current_size = size();
    if (new_size < current_size) {
        // assert
    }
    pointer temp = first_;
    first_ = allocate(new_size);
    end_ = first_ + new_size;
    last_ = first_ + current_size;
    std::copy(temp, temp + current_size, first_);
    deallocate(temp);
}
template <class T>
void dynamic_array<T>::shrink_to_fit() {
    std::size_t current_size = size();
    pointer temp = first_;
    first_ = allocate(current_size);
    end_ = first_ + current_size;
    last_ = first_ + current_size;
    std::copy(temp, temp + current_size, first_);
    deallocate(temp);
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::insert(dynamic_array<T>::const_iterator pos, const T& element) {
    std::size_t pos_index = std::distance(first_, pos);
    std::size_t size = this->size();
    if (pos_index > size) {
        // assert
    }
    if (last_ == end_) {
        reallocate();
    }
    for (iterator itr = end_, stop = first_ + pos_index; itr != stop; --itr) {
        std::swap(*itr, *(itr - 1));
    }
    *(first_ + pos_index) = value;
    return first_ + pos_index;
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::insert(const_iterator pos, T&& value) {
    std::size_t pos_index = std::distance(first_, pos);
    std::size_t size = this->size();
    if (pos_index > size) {
        // assert
    }
    if (last_ == end_) {
        reallocate();
    }
    for (iterator itr = end_, stop = first_ + pos_index; itr != stop; --itr) {
        std::swap(*itr, *(itr - 1));
    }
    *(first_ + pos_index) = std::move(value);
    return first_ + pos_index;
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::insert(dynamic_array<T>::const_iterator pos, size_type count,
                                                             const T& value) {
    std::size_t pos_index = std::distance(first_, pos);
    std::size_t size = this->size();
    std::size_t capacity = this->capacity();
    if (pos_index > size) {
        // assert
    }
    if ((last_ + count) >= end_) {
        this->resize(capacity + count);
    }
    for (iterator itr = end_, stop = first_ + pos_index + count, itr != pos; --itr) {
        std::swap(*itr, *(itr - 1));
    }
    std::fill(first_ + pos_index, first_ + pos_index + count, value);
    return first_ + pos_index;
}
template <class T>
template <class InputIt>
typename dynamic_array<T>::iterator dynamic_array<T>::insert(dynamic_array<T>::const_iterator pos, InputIt first,
                                                             InputIt last) {
    std::size_t pos_index = std::distance(first_, pos);
    std::size_t count = std::distance(first, last);
    std::size_t size = this->size();
    std::size_t capacity = this->capacity();
    if (pos_index > size) {
        // assert
    }
    if ((last_ + count) >= end_) {
        this->resize(capacity + count);
    }
    for (iterator itr = end_, stop = first_ + pos_index + count, itr != pos; --itr) {
        std::swap(*itr, *(itr - 1));
    }
    std::copy(first, last, first_ + pos_index);
    return first_ + pos_index;
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::insert(dynamic_array<T>::const_iterator pos,
                                                             std::initializer_list<T> init) {
    std::size_t pos_index = std::distance(first_, pos);
    std::size_t count = init.size();
    std::size_t size = this->size();
    std::size_t capacity = this->capacity();
    if (pos_index > size) {
        // assert
    }
    if ((last_ + count) >= end_) {
        this->resize(capacity + count);
    }
    for (iterator itr = end_, stop = first_ + pos_index + count, itr != pos; --itr) {
        std::swap(*itr, *(itr - 1));
    }
    std::copy(init.begin(), init.end(), first_ + pos_index);
    return first_ + pos_index;
}

template <class T>
template <class... Args>
typename dynamic_array<T>::reference dynamic_array<T>::emplace(dynamic_array<T>::const_iterator, Args&&...) {
    if (last_ == end_) {
        reallocate();
    }
    *last_ = std::move(T(std::forward<Args>(args)...));
    return *last_;
}
template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::erase(dynamic_array<T>::iterator pos) {
    for (iterator itr = pos, end = last_ - 1; itr != end; ++itr) {
        std::swap(*itr, *(itr + 1));
    }
    last_->~T();
    last_--;
    return pos;
}

template <class T>
typename dynamic_array<T>::iterator dynamic_array<T>::erase(dynamic_array<T>::iterator first,
                                                            dynamic_array<T>::iterator last) {
    std::size_t count = std::distance(first, last);
    std::size_t pos for (iterator itr = last, end = last_; itr != end; ++itr, ++first) { std::swap(*itr, *(first)); }
    for (iterator itr = last_ - count; itr != last_; ++itr) {
        itr->~T();
    }
    last_ = last_ - count;
    return last_;
}


}  // end ker namespace

#endif  // KER_CONTAINER_DYNAMIC_ARRAY_H