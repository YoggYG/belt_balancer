#ifndef INCLUDED_OUTPUTHANDLER_H
#define INCLUDED_OUTPUTHANDLER_H

#include <mutex>
#include <random>

class SharedDataHandler;
class Balancer;

class OutputHandler
{
    static size_t s_id;
    static std::mutex s_cout;
    static std::mt19937 s_engine;   // used by pause
    static std::uniform_int_distribution<> s_dist;

    SharedDataHandler &d_sdh;
    size_t d_id;

    public:
        OutputHandler(SharedDataHandler &sdh);
        void operator()();

    private:
        void process(Balancer &b);
        void pause();
};
        
#endif

