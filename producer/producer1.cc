#include "producer.ih"

Producer::Producer(SharedDataHandler &sdh, size_t numIncr, size_t startNumber)
:
	d_sdh(sdh),
	d_id(++s_id),
	d_numIncrements(numIncr),
	d_startNumber(startNumber)
{}
