#include "balancer.ih"

bool Balancer::isCompletePath(vector<Triple> path)
{
	if (isSplitter(path.front().tile) and isSplitter(path.back().tile))
		return true;

	if (isSplitter(path.front().tile) and path.back().y == 0)
		return true;

	if (path.front().y == d_rows - 1 and isSplitter(path.back().tile))
		return true;

	return false;
}