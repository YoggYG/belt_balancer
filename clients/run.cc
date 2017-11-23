#include "clients.ih"

void Clients::run()
{
    for (size_t idx = d_client.size(); idx--; )     // start the client
        d_thread[idx] = thread(ref(d_client[idx])); // threads
}
