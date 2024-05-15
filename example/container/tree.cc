#include <ker/container/tree.h>

#include <iostream>

int main(int argc, char const* argv[]) {
    ker::container::tree<std::int64_t> tree_;
    tree_.insert(3);
    tree_.insert(2);    
    tree_.insert(1); 
    tree_.print();
    std::cout << (tree_.is_balanced() ? "Balanced" : "Not Balanced") << std::endl;
    tree_.balance_helper();
    tree_.print();
    std::cout << (tree_.is_balanced() ? "Balanced" : "Not Balanced") << std::endl;
    return 0;
}
