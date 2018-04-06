#include "balancer.ih"

bool Balancer::nextMatrix()
{
	size_t pos = d_matrix.size() - 1;
	++d_matrix[pos];
	return incrMatrixUntilOK(pos);
}