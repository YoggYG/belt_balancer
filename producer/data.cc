#include "producer.ih"

size_t  Producer::s_id;
mutex   Producer::s_cout;

mt19937 Producer::s_engine(
            system_clock::now().time_since_epoch().count()
        );
uniform_int_distribution<> Producer::s_dist(0, 0.5);