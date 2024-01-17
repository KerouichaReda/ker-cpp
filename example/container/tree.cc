#include <iostream>
#include <ker/container/tree.h>

int main(int argc, char const *argv[])
{

    ker::tree<int> tree_;
    tree_.insert(1);
    std::cout << "Hello tree" << std::endl;
    return 0;
}

