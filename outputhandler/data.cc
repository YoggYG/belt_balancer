#include "outputhandler.ih"

size_t  OutputHandler::s_id;
mutex   OutputHandler::s_cout;

mt19937 OutputHandler::s_engine(
            system_clock::now().time_since_epoch().count()
        );
uniform_int_distribution<> OutputHandler::s_dist(0, 0.5);