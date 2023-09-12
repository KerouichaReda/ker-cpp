// https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/include/bits/stl_set.h#L133
#include <tree.h>
#include <functional>
namespace ker {
template <class Key, class Compare = std::less<Key>>
class set {
   public:
    // typedef:
    typedef key key_type;
    set(/* args */);
    ~set();

   private:
    /* data */
};
template <class Key, class Compare>
set<Key, Compare>::set() {}
template <class Key, class Compare>
set<Key, Compare>::~set() {}

}  // namespace ker
