#include "semaphore.ih"

void Semaphore::set(size_t cnt)
{
    lock_guard<mutex> lg(d_mut);
    d_cnt = cnt;
}
