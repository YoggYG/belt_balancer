#include "balancer.ih"

size_t Balancer::eastUndergroundInputDistance(size_t pos)
{
	pos -= 2;
	if (pos % d_cols == d_cols - 1)
		return 0;
	
	for (size_t length = 2; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIE)
			return length;
		if (d_matrix[pos] == UBOW)
			return 0;
		if (d_matrix[pos] == UBOE)
			return 0;
		if (d_matrix[pos] == UBIW)
			return 0;
		if (pos % d_cols == 0)
			return 0;
		--pos;
	}
	return 0;
}