#include "balancer.ih"

bool Balancer::isEntryPath(vector<Triple> path)
{
	if (path.front().y == d_rows - 1)
		return true;

	return false;
}