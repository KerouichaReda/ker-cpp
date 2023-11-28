#include <iostream>
#include "../../ker/memory/shared_ptr.h"
class share_ptr_test {
   private:
    /* data */
   public:
    int data_1;
    int data_2;
    int data_3;
    share_ptr_test() : data_1(0), data_2(1), data_3(2) {}
    ~share_ptr_test();
};

int main(int argc, char const* argv[]) {
    ker::shared_ptr<share_ptr_test> ptr;
    std::cout << ptr.use_count() << std::endl;
    ker::shared_ptr<share_ptr_test> test_1(new share_ptr_test());
    std::cout << test_1.use_count() << std::endl;
    ker::shared_ptr<share_ptr_test> test_2(test_1);
    std::cout << test_1.use_count() << std::endl;
    std::cout << test_1.use_count() << std::endl;
    ker::shared_ptr<share_ptr_test> test_3 = ker::make_shared<share_ptr_test>();

    return 0;
}
