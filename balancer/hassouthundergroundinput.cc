#include "balancer.ih"

bool Balancer::hasSouthUndergroundInput(size_t pos)
{
	pos -= 2 * d_cols;
	for (size_t length = 2; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIS)
			return true;
		if (d_matrix[pos] == UBON)
			return false;
		if (d_matrix[pos] == UBOS)
			return false;
		if (pos < d_cols)
			return false;
		pos -= d_cols;
	}
	return false;
}