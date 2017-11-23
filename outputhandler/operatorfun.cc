#include "outputhandler.ih"

void OutputHandler::operator()()
{
    while (true)
    {
        SharedDataHandler::Spec spec = d_sdh.getRes();     // get the next job

        if (spec.done)
            break;

        process(spec.bal);
    }
}