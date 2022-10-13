/// @file concurent_queue.h
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

#ifndef KER_CONCURRENT_QUEUE_H
#define KER_CONCURRENT_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>

namespace ker {
template <class Data>
class concurrent_queue {
   public:
    void push(Data const& _data) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(_data);
        lock.unlock();
        condition_variable_.notify_one();
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    bool try_pop(Data& popped_value) {
        // replace with optional
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        popped_value = queue_.front();
        queue_.pop();
        return true;
    }

    void wait_and_pop(Data& popped_value) {
        std::lock_guard<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            condition_variable_.wait(lock);
        }
        popped_value = queue_.front();
        queue_.pop();
    }

   private:
    std::queue<Data> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_variable_;
};
}

#endif