// https://github.com/rigtorp/MPMCQueue
// A bounded multi-producer multi-consumer concurrent queue written in C++11.
// https://www.youtube.com/watch?v=_qaKkHuHYE0

#ifndef KER_CONCURRENCY_CONCURRENT_MPMC_QUEUE_H
#define KER_CONCURRENCY_CONCURRENT_MPMC_QUEUE_H
namespace ker {
namespace concurrency {
class mpmc_queue {
   private:
    /* data */
   public:
    mpmc_queue(/* args */);
    ~mpmc_queue();
};

mpmc_queue::mpmc_queue(/* args */) {}

mpmc_queue::~mpmc_queue() {}
}
}

#endif