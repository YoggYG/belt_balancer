#include "balancer.ih"

bool Balancer::hasEastUndergroundInput(size_t pos)
{
	pos -= 2;
	if (pos % d_cols == d_cols - 1)
		return false;
	
	for (size_t length = 2; length <= d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIE)
			return true;
		if (d_matrix[pos] == UBOW)
			return false;
		if (d_matrix[pos] == UBOE)
			return false;
		if (pos % d_cols == 0)
			return false;
		--pos;
	}
	return false;
}