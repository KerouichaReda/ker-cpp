/// @file dynamic_array.h
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

#ifndef KER_CONTAINER_DYNAMIC_ARRAY_H
#define KER_CONTAINER_DYNAMIC_ARRAY_H

#include <memory>

namespace ker {
constexpr std::size_t max_size_{0xFFFFFFFFFFFFFFF};
template <class T, class A = std::allocator<T>>
class dynamic_array {
   public:
    dynamic_array() { allocate(); }
    ~dynamic_array() { delete[] first_; }
    void push_back(const T& element) {
        if (last_ == end_) {
            allocate();
        }
        *last_ = element;
        ++last_;
    }
    std::size_t max_size() const { return max_size_; }
    void push_back(T element) {
        if (last_ == end_) {
            allocate();
        }
        *last_ = element;
        ++end;
    }
    void pop_back(){
        if(first_ == last_){
            //assert
        }
        --last_;
    }
    std::size_t size() { return last_ - first_; }
    void empty();
    void resize();

    /// itrerator
   private:
    void allocate() {
        T* temp = first_;
        std::size_t current_size_ = size();
        std::size_t new_size_ = current_size_ << 1;
        first_ = new T[new_size_];
        last_ = first_ + current_size_;
        end_ = first_ + new_size_;
        std::copy(temp, temp + current_size_, first_);
        delete[] temp;
    }
    void deallocate() {}
    T* first_ = nullptr;
    T* last_ = nullptr;
    T* end_ = nullptr;  // end of the allocated storage
    
};

}  // end ker namespace

#endif  // KER_CONTAINER_DYNAMIC_ARRAY_H