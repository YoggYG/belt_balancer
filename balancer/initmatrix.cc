#include "balancer.ih"

void Balancer::initMatrix()
{
	size_t idx = d_cols - 1;
	
	for (size_t beltsToPlace = d_n; beltsToPlace > 0; --beltsToPlace)
		d_matrix[idx--] = BN;

	incrMatrixUntilOK(0);
}