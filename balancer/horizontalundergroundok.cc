#include "balancer.ih"

bool Balancer::horizontalUndergroundOK(size_t pos)
{
	return (d_matrix[pos].ugE == 0 or (d_matrix[pos].ugE < d_underground_length and (pos + 1 % d_cols) == 0))
			and (d_matrix[pos].ugW == 0 or (d_matrix[pos].ugW < d_underground_length and (pos + 1 % d_cols) == 0));
}