#include "../../ker/concurrency/concurrent_queue.h"

#include <iostream>
#include <string>


int main(int argc, char const* argv[]) {
    ker::concurrent_queue<std::string> cq_;
        cq_.push(std::string{"3"});
    std::cout << cq_.front() << std::endl;
    return 0;
}