#include "producers.ih"

Producers::~Producers()
{
	if (!d_joined)
	    for (size_t beg = 0; beg < d_thread.size(); ++beg)
	        d_thread.at(beg).join();
}
