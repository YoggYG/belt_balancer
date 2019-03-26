#include "balancer.ih"

bool Balancer::isExitPath(vector<Triple> path)
{
	if (path.back().y == 0)
		return true;

	return false;
}