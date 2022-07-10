/// @file circular_queue.h
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

#ifndef KER_CONTAINER_CIRCULAR_QUEUE_H
#define KER_CONTAINER_CIRCULAR_QUEUE_H
#include <memory>
template <class T, class A = std::allocator<T>> class circular_queue{
public:
    circular_queue(size_t _buffer_size) : buffer_size_(_buffer_size){
        buffer_ = new T[buffer_size_];
    }
    ~circular_queue();
    void push(T _item){
        buffer_[end_index++] = _item;
        end_index %= buffer_size_;
    }
    void pop(){
        start_index = (start_index + 1) % buffer_size_;
    }
    T front(){
        return buffer_[start_index];
    }

private:
    T* buffer_{nullptr};
    size_t buffer_size_{0};
    size_t start_index{0};
    size_t end_index{0};
}


#endif // KER_CONTAINER_CIRCULAR_QUEUE_H