#include "balancer.ih"

bool Balancer::hasEastUndergroundInput(size_t pos)
{
	size_t count = 0;

	--pos;
	if (pos % d_cols == d_cols - 1)
		return false;
	
	for (size_t length = 1; length < d_underground_length; ++length)
	{
		if (d_matrix[pos] == UBIE)
			if (count > 0)
				return true;
		if (d_matrix[pos] == UBOW)
			return false;
		if (d_matrix[pos] == UBOE)
			return false;
		if (pos % d_cols == 0)
			return false;

		if (d_matrix[pos] != EMPTY)
			++count;

		--pos;
	}
	return false;
}