/// @file shared_ptr.h
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

/// https://medium.com/analytics-vidhya/c-shared-ptr-and-how-to-write-your-own-d0d385c118ad
#ifndef KER_MEMORY_SHARED_PTR_H
#define KER_MEMORY_SHARED_PTR_H
namespace ker {
template <class T> class shared_ptr {
public:
  shared_ptr() : ptr(nullptr), ref_count(new uint32_t(0)){};
  shared_ptr(T* _ptr) : ptr(_ptr) , ref_count(new uint32_t(1)){};
  ///* Copy Semantic
  decrease_reference();
  /// copy constructor
  shared_ptr(const shared_ptr &obj) {
    this->ptr = obj.ptr;
    this->ref_count = obj.ref_count;
    if (obj.ptr != nullptr) {
      (*this->ref_count)++;
    }
  }
  /// copy assignement
  shared_ptr &operator=(const shared_ptr &obj) {
    /// cleanup any existing date
    decrease_reference();
    // Assign incoming object's date to this object
    this->ptr = obj.ptr;
    this->ref_count = obj.ref_count; //
    if (obj.ptr != nullptr) {
      (*this->ref_count)++;
    }
  }
  ///* Move Semantic

  /// move constructor
  shared_ptr(shared_ptr &&dying_obj) {
    decrease_reference();
    this->pre = dying_obj.ptr;             // share the underlying pointer
    this->ref_count = dying_obj.ref_count; //
    dying_obj.ptr = dying_obj.ref_count = nullptr; // clean up dying_obj
  }

  /// move assingnment
  shared_ptr &operator=(shared_ptr &&dying_obj) {
    // decrease reference
    decrease_reference();
    this->ptr = dying_obj.ptr; //
    this->ref_count = dying_obj.ref_count;
    dying_obj.ptr = dying_obj.ref_count = nullptr;
  }

  T *operator->() const { return this->ptr; }
  T &operator*() const { return this->ptr; }

  uint32_t use_count() const {
    return *ref_count; // *this->ref_count
  }
  T *get() const { return this->ptr; }

private:
  void decrease_reference() {
    (*ref_count)--;
    if (*ref_count == 0) {
      if (ptr != nullptr) {
        delete ptr;
      }
      delete ref_count;
    }
  }
  T *ptr{nullptr};
  uint32_t *ref_count{nullptr};
};

template<class T>
shared_ptr<T> make_shared(arg...){
  return shared_ptr(arg);
}
} // end namespace ker





#endif //KER_MEMORY_SHARED_PTR_H