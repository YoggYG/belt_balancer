#include "client.ih"

void Client::operator()()
{
    while (true)
    {
        SharedDataHandler::Spec spec = d_sdh.getTask();     // get the next job

        if (spec.done)
            break;

        process(spec.bal);
    }
}