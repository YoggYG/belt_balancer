#include "balancer.ih"

bool Balancer::hasSouthUndergroundInput(size_t pos)
{
	size_t count = 0;

	pos -= d_cols;
	for (size_t length = 1; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIS)
			if (count > 0)
				return true;
		if (d_matrix[pos] == UBON)
			return false;
		if (d_matrix[pos] == UBOS)
			return false;
		if (pos < d_cols)
			return false;

		if (d_matrix[pos] != EMPTY)
			++count;

		pos -= d_cols;
	}
	return false;
}