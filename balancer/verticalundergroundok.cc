#include "balancer.ih"

bool Balancer::verticalUndergroundOK(size_t pos)
{
	return (d_matrix[pos].ugN == 0 or (d_matrix[pos].ugN < d_underground_length and (pos + 2 * d_cols) < d_matrix.size()))
			and (d_matrix[pos].ugS == 0 or (d_matrix[pos].ugS < d_underground_length and (pos + 3 * d_cols) < d_matrix.size()));
}