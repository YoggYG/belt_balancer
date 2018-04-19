#include "balancer.ih"

void Balancer::initMatrix(vector<char> matrix)
{
	for (size_t idx = 0; idx < matrix.size(); ++idx)
		d_matrix.push_back(Tile{matrix[idx], 0, 0, 0, 0});	
}