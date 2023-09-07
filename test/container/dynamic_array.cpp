#include <iostream>
#include "../../ker/container/dynamic_array.h"

int main(int argc, char const* argv[]) {
    ker::dynamic_array<int> array_(4);
    std::cout << "Size : " << array_.size() << std::endl;
    std::cout << "Capacity : " << array_.capacity() << std::endl;

    for(ker::dynamic_array<int>::iterator itr = array_.begin(), end = array_.end() ; itr != end ; ++itr ){
        std::cout << *itr << " ";
    }
    std::cout << std::endl;

    return 0;
}
