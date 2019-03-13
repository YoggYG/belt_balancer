#include "balancer.ih"

void Balancer::resetUndergroundCount(size_t pos)
{
	d_matrix[pos].ugN = 0;
	d_matrix[pos].ugE = 0;
	d_matrix[pos].ugW = 0;
	d_matrix[pos].ugS = 0;	
}