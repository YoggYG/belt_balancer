#include "balancer.ih"

bool Balancer::hasNorthUndergroundOutput(size_t pos)
{
	pos -= 2 * d_cols;
	for (size_t length = 2; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBON)
			return true;
		if (d_matrix[pos] == UBIS)
			return false;
		if (d_matrix[pos] == UBIN)
			return false;
		if (pos < d_cols)
			return false;
		pos -= d_cols;
	}
	return false;
}