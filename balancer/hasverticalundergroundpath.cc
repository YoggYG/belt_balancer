#include "balancer.ih"

bool Balancer::hasVerticalUndergroundPath(size_t pos)
{
	pos -= d_cols;	
	for (size_t length = 1; length < d_underground_length; ++length)
	{
		if (pos < d_cols)
			return false;
		
		if (d_matrix[pos] == UBON or d_matrix[pos] == UBIS)
			return true;
		
		if (d_matrix[pos] == UBIN or d_matrix[pos] == UBOS)
			return false;

		pos -= d_cols;
	}
	return false;
}