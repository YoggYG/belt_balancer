#include "balancer.ih"

bool Balancer::undergroundUsefulNorth(size_t pos)
{
	for (size_t idx = pos - (d_matrix[pos].ugN - 1) * d_cols; idx < pos; idx += d_cols)
		if (d_matrix[idx].item)
			return true;

	return false;
}

bool Balancer::undergroundUsefulEast(size_t pos)
{
	for (size_t idx = pos - (d_matrix[pos].ugE - 1); idx < pos; ++idx)
		if (d_matrix[idx].item)
			return true;

	return false;
}

bool Balancer::undergroundUsefulWest(size_t pos)
{
	for (size_t idx = pos - (d_matrix[pos].ugW - 1); idx < pos; ++idx)
		if (d_matrix[idx].item)
			return true;

	return false;
}

bool Balancer::undergroundUsefulSouth(size_t pos)
{
	for (size_t idx = pos - (d_matrix[pos].ugS - 1) * d_cols; idx < pos; idx += d_cols)
		if (d_matrix[idx].item)
			return true;

	return false;
}