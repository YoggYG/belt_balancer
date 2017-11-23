#include "outputhandler.ih"

void OutputHandler::process(Balancer &b)
{   // Work!
    //pause();

    if (!d_sdh.contains(b))
    {
        b.print();
        d_sdh.addToVector(b);
    }
}
