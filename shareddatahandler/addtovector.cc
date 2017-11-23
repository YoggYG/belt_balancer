#include "shareddatahandler.ih"

void SharedDataHandler::addToVector(Balancer const &balancer)
{
	d_balancers.push_back(balancer);
}