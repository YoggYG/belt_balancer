#include "balancer.ih"

size_t Balancer::southUndergroundInputDistance(size_t pos)
{
	pos -= 2 * d_cols;
	for (size_t length = 2; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIS)
			return length;
		if (d_matrix[pos] == UBON)
			return 0;
		if (d_matrix[pos] == UBOS)
			return 0;
		if (d_matrix[pos] == UBIN)
			return 0;
		if (pos < d_cols)
			return 0;
		pos -= d_cols;
	}
	return 0;
}