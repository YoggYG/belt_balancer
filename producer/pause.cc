#include "producer.ih"

void Producer::pause()
{
    this_thread::sleep_for(seconds(s_dist(s_engine)));
}