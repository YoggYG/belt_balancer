#include "clients.ih"

Clients::~Clients()
{
	if (!d_joined)
	    for (size_t beg = 0; beg < d_thread.size(); ++beg)
	        d_thread.at(beg).join();
}
