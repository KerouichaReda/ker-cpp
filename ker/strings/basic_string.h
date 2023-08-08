#ifndef KER_STRINGS_BASIC_STRING_H
#define KER_STRINGS_BASIC_STRING_H

#include <memory>
template<typename T>
struct basic_string
{
    T* ptr_;
    std::size_t size_;
    std::size_t capacity_;
};


#endif // KER_STRINGS_BASIC_STRING_H