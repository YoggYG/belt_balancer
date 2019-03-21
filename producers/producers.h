#ifndef INCLUDED_PRODUCERS_
#define INCLUDED_PRODUCERS_

#include <vector>
#include <thread>

#include "../producer/producer.h"

class SharedDataHandler;

class Producers
{
    std::vector<Producer> d_producers;
    std::vector<std::thread> d_thread;
    bool d_joined;

    public:
        Producers(SharedDataHandler &sdh, size_t nProducers);
        ~Producers();
        void join();

        void run(size_t n, size_t power, size_t rows, size_t cols, size_t undergroundLength);
};
        
#endif
