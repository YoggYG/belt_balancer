#ifndef INCLUDED_PRODUCER_
#define INCLUDED_PRODUCER_

#include <mutex>
#include <random>

class SharedDataHandler;
class Balancer;

struct Producer
{
    static size_t s_id;
    static std::mutex s_cout;
    static std::mt19937 s_engine;   // used by pause
    static std::uniform_int_distribution<> s_dist;

    SharedDataHandler &d_sdh;
    size_t d_id;

    public:
        Producer(SharedDataHandler &sdh);
        void operator()(size_t n, size_t power, size_t rows, size_t cols);

    private:
        void pause();
        // bool possiblyValid(std::vector<char> &matrix, size_t n, size_t power);
        // bool getNextMatrix(std::vector<char> &matrix, size_t n, size_t rows, size_t cols);
        // void incrementMatrix(std::vector<char> &matrix, size_t idx, size_t incr);
        // bool edgeCase(std::vector<char> &matrix, size_t idx, size_t rows, size_t cols);
        void placeSplitter(std::vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace);
};
        
#endif
