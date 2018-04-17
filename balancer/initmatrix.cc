#include "balancer.ih"

bool Balancer::initMatrix()
{
	size_t idx = d_cols;

	size_t beltsToPlace = d_n - numberOfOutputBelts();
	
	while (beltsToPlace > 0)
	{
		while (d_matrix[--idx] == BN); // decrement idx until an empty spot is reached
		d_matrix[idx] = BN;
		--beltsToPlace;
	}

	return incrMatrixUntilOK(0);
}