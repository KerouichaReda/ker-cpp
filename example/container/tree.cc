#include <ker/container/tree.h>

#include <iostream>

int main(int argc, char const* argv[]) {
    ker::container::tree<std::int64_t> tree_;
    tree_.insert(1);
    std::cout << "MIN : " << tree_.min() << " MAX : " << tree_.max() << std::endl; 
    tree_.insert(2);
    std::cout << "MIN : " << tree_.min() << " MAX : " << tree_.max() << std::endl; 
    tree_.insert(3);
    std::cout << "MIN : " << tree_.min() << " MAX : " << tree_.max() << std::endl; 
    tree_.insert(-1);
    std::cout << "MIN : " << tree_.min() << " MAX : " << tree_.max() << std::endl; 
    tree_.print();
    return 0;
}
