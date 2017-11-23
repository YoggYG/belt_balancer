#include "producer.ih"

Producer::Producer(SharedDataHandler &sdh, bool noSouthBelts, bool onlyNUGS, size_t numIncr, size_t startNumber)
:
	d_sdh(sdh),
	d_id(++s_id),
	d_noSouthBelts(noSouthBelts),
	d_onlyNorthUGS(onlyNUGS),
	d_numIncrements(numIncr),
	d_startNumber(startNumber)
{}
