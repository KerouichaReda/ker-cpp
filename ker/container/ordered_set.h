#ifndef KER_CONTAINER_ORDERED_SET_H
#define KER_CONTAINER_ORDERED_SET_H
#include <set>
#include <list>
namespace ker {
template <class T>
class linear_set {
    linear_set(const std::size_t capacity,const  std::size_t eviction_size) : capacity_(capacity), eviction_size_(eviction_size) {}
    ~linear_set() {}
    void insert(const T& value) {
        std::set<T>::iterator itr = set_.insert(value);
        list_.push_back(itr);
        if (set_.size() > capacity_) {
            evict();
        }
    }
    bool contains(const T& value) { return set_.find(value) != set_.end(); }

   private:
    void evict() {
        std::set<T>::iterator itr = list_.front();
        set_.erase(list_.front(), list_.front() + eviction_size_);
        list_.erase(list_.begin(), list_.begin() + eviction_size_);
    }
    std::set<T> set_;
    std::list<std::set<T>::iterator> list_;
    const std::size_t eviction_size_;
    const std::size_t capacity_;
}
}

#endif  // KER_CONTAINER_ORDERED_MAP_H