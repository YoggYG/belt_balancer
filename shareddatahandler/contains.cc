#include "shareddatahandler.ih"

bool SharedDataHandler::contains(Balancer &balancer) const
{
	for (size_t idx = 0; idx < d_balancers.size(); ++idx)
		if (balancer == d_balancers[idx])
			return true;
	return false;
}