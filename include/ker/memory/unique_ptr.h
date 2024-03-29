/// @file unique_ptr.h
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
/// https://medium.com/@karankakwani/c-smart-pointers-and-how-to-write-your-own-c0adcbdce04f
// https://archive.is/20211025041014/https://medium.com/swlh/c-smart-pointers-and-how-to-write-your-own-c0adcbdce04f

#ifndef KER_MEMORY_UNIQUE_PTR_H
#define KER_MEMORY_UNIQUE_PTR_H
namespace ker {
namespace memory {
template <class T>
class unique_ptr {
   public:
    unique_ptr() : ptr_(nullptr) {}
    unique_ptr(T* ptr) : ptr_(ptr) {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& dyingObj) {
        this->ptr_ = dyingObj.ptr_;
        dyingObj.ptr_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& dyingObj) {
        clear();
        this->ptr_ = dyingObj.ptr_;
        dyingObj.ptr_ = nullptr;
    }

    T* operator->() { return this->ptr_; }
    T& operator*() { return *(this->ptr_); }
    ~unique_ptr() { clear(); }

   private:
    void clear() {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
    }
    T* ptr_ = nullptr;
};
template <class T>
class unique_ptr<T[]> {
   public:
    unique_ptr() : ptr_(nullptr) {}
    unique_ptr(T* ptr) : ptr_(ptr) {}
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    unique_ptr(unique_ptr&& dyingObj) {
        this->ptr_ = dyingObj.ptr_;
        dyingObj.ptr_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& dyingObj) {
        clear();
        this->ptr_ = dyingObj.ptr_;
        dyingObj.ptr_ = nullptr;
    }

    T* operator->() { return this->ptr_; }
    T& operator*() { return *(this->ptr_); }
    T& operator[](std::size_t index) { return this->ptr_[index]; }
    ~unique_ptr() { clear(); }

   private:
    void clear() {
        if (ptr_ != nullptr) {
            delete ptr_[];
        }
    }
    T* ptr_ = nullptr;
};
}
}  ///< end namespace ker

#endif  // KER_MEMORY_UNIQUE_PTR_H