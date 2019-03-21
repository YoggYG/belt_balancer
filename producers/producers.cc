#include "producers.ih"

Producers::Producers(SharedDataHandler &sdh, size_t nProducers)
:
    d_thread(nProducers)
{
	d_joined = false;
	size_t stepSize = nProducers;
    for (; nProducers--; )                        
        d_producers.push_back(Producer(sdh, stepSize, nProducers));   
}