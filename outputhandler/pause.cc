#include "outputhandler.ih"

void OutputHandler::pause()
{
    this_thread::sleep_for(seconds(s_dist(s_engine)));
}