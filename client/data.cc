#include "client.ih"

size_t  Client::s_id;
mutex   Client::s_cout;

mt19937 Client::s_engine(
            system_clock::now().time_since_epoch().count()
        );
uniform_int_distribution<> Client::s_dist(0, 0.5);