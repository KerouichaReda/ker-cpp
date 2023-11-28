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
#include <functional>
#include <vector>
namespace ker {
template <class T, class A = std::allocator<T>>
class circular_queue {
   public:
    circular_queue(const size_t _buffer_size) : buffer_size_(_buffer_size) { buffer_ = new T[buffer_size_]; }
    ~circular_queue() {}
    void push(T _item) {
        size_ = std::max(++size_, buffer_size_);
        buffer_[end_index++] = _item;
        end_index_ %= buffer_size_;
    }
    void pop() { start_index_ = (start_index_ + 1) % buffer_size_; }
    T front() { return buffer_[start_index_]; }
    std::vector<T> last_formatted() {
        std::vector<T> last_;
        for (std::size_t start = start_index_, end = end_index_ + size_; start < end; ++start) {
            last_.push_back(buffer_[start % buffer_size_]);
        }
        return last_;
    }

   private:
    T* buffer_{nullptr};
    std::size_t buffer_size_{0};
    std::size_t start_index_{0};
    std::size_t end_index_{0};
    std::size_t size_{};
}
}

#endif  // KER_CONTAINER_CIRCULAR_QUEUE_H