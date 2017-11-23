#include "clients.ih"

void Clients::join()
{
	d_joined = true;
    for (size_t idx = d_client.size(); idx--; )     // join the client
        d_thread[idx].join(); // threads
}
