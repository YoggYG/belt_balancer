#include "producer.ih"

Producer::Producer(SharedDataHandler &sdh)
:
	d_sdh(sdh),
	d_id(++s_id)
{}
