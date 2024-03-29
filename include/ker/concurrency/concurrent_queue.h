/// @file concurent_queue.h
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

#ifndef KER_CONCURRENT_QUEUE_H
#define KER_CONCURRENT_QUEUE_H
#include <queue>
#include <mutex>

namespace ker {
template <class T>
class concurrent_queue {
   public:
    void push(const T&);
    T& front();
    void pop();
    std::size_t size();
    bool empty();

   private:
    std::queue<T> queue_;
    std::mutex mutex_;
};

template <class T>
void concurrent_queue<T>::push(const T& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
}
template <class T>
T& concurrent_queue<T>::front() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.front();
}

template <class T>
void concurrent_queue<T>::pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) return;
    queue_.pop();
}
std::size_t concurrent_queue<T>::size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
}
template <class T>
bool concurrent_queue<T>::empty() {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}
}

#endif