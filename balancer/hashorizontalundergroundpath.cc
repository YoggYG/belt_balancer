#include "balancer.ih"

bool Balancer::hasHorizontalUndergroundPath(size_t pos)
{
	--pos;	
	for (size_t length = 1; length < d_underground_length; ++length)
	{
		if (pos % d_cols == 0)
			return false;
		
		if (d_matrix[pos] == UBOW or d_matrix[pos] == UBIE)
			return true;
		
		if (d_matrix[pos] == UBIW or d_matrix[pos] == UBOE)
			return false;

		--pos;
	}
	return false;
}