#include "shareddatahandler.ih"

void SharedDataHandler::sortVector()
{
	sort(d_balancers.begin(), d_balancers.end(),
		[](Balancer &a, Balancer &b)
		{
			return a.cost() < b.cost();
		});
}