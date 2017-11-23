#ifndef INCLUDED_SEMAPHORE_
#define INCLUDED_SEMAPHORE_

#include <mutex>
#include <condition_variable>

class Semaphore
{
    std::mutex d_mut;
    std::condition_variable d_con;
    size_t d_cnt;

    public:
        Semaphore(size_t cnt);

        void wait();
        void notify();
        void notify_all();
        void set(size_t cnt = 0);
        size_t size() const;        
};

inline size_t Semaphore::size() const
{
    return d_cnt;
} 

#endif
