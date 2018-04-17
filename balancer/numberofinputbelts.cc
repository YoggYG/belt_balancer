#include "balancer.ih"

size_t Balancer::numberOfInputBelts()
{
	size_t res = 0;

	for (size_t idx = d_matrix.size() - d_cols; idx < d_matrix.size(); ++idx)
		if (d_matrix[idx] == BN)
			++res;

	return res;
}