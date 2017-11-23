#include "clients.ih"

Clients::Clients(SharedDataHandler &sdh, size_t nClients)
:
    d_thread(nClients)
{
	d_joined = false;
    for (; nClients--; )                        // create the clients: clients
        d_client.push_back(Client(sdh));   		// need to access the
}                                               // sdh.

