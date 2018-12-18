#include "balancer.ih"

bool Balancer::hasNorthUndergroundOutput(size_t pos)
{
	size_t count = 0;

	pos -= d_cols;	
	for (size_t length = 1; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBON)
			if (count > 0)
				return true;
		if (d_matrix[pos] == UBIS)
			return false;
		if (d_matrix[pos] == UBIN)
			return false;
		if (pos < d_cols)
			return false;

		if (d_matrix[pos] != EMPTY)
			++count;

		pos -= d_cols;
	}
	return false;
}