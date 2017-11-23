#include "producers.ih"

void Producers::join()
{
	d_joined = true;
    for (size_t idx = d_producers.size(); idx--; )     // join the client
        d_thread[idx].join(); // threads
}
