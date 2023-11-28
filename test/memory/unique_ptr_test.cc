#include <iostream>
#include "../../ker/memory/unique_ptr.h"

class unique_ptr_test {
   public:
    unique_ptr_test() : data_1(0), data_2(1), data_3(2) {}
    ~unique_ptr_test()  = default;

   private:
    int data_1;
    int data_2;
    int data_3;
};

int main(int argc, char const *argv[])
{
    ker::unique_ptr<unique_ptr_test> ptr(new unique_ptr_test);
    ker::unique_ptr<unique_ptr_test> ptr_array(new unique_ptr_test[5]);
    ker::unique_ptr<unique_ptr_test> ptr_test = std::move(ptr) ;
    return 0;
}

