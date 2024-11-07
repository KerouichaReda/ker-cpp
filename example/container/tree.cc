#include <ker/container/tree.h>

#include <iostream>

int main(int argc, char const* argv[]) {
    ker::container::tree<std::int64_t> tree_;
    for(int i = 0 ; i < 5 ; i++){
    tree_.insert(i);
}

    tree_.print();
    return 0;
}
