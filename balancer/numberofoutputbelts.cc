#include "balancer.ih"

size_t Balancer::numberOfOutputBelts()
{
	size_t res = 0;

	for (size_t idx = 0; idx < d_cols; ++idx)
		if (d_matrix[idx] == BN)
			++res;

	return res;
}