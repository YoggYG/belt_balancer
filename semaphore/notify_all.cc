#include "semaphore.ih"

void Semaphore::notify_all()
{
    lock_guard<mutex> lg(d_mut);
    if (d_cnt++ == 0)
        d_con.notify_all();
}
