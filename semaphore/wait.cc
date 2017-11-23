#include "semaphore.ih"

void Semaphore::wait()
{
    unique_lock<mutex> ul(d_mut);
    while (d_cnt == 0)
        d_con.wait(ul);
    --d_cnt;
}
