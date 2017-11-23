#ifndef INCLUDED_CLIENTS_
#define INCLUDED_CLIENTS_

#include <vector>
#include <thread>

#include "../client/client.h"

class SharedDataHandler;

class Clients
{
    std::vector<Client> d_client;
    std::vector<std::thread> d_thread;
    bool d_joined;

    public:
        Clients(SharedDataHandler &sdh, size_t nClients);
        ~Clients();
        void join();

        void run();
};
        
#endif
