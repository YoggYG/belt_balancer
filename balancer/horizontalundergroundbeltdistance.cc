#include "balancer.ih"

size_t Balancer::horizontalUndergroundBeltDistance(size_t pos)
{
	for (size_t distance = 2; distance < d_underground_length or (pos - distance) % d_cols != 0; ++distance)
		if (d_matrix[pos - distance] == UBIE or d_matrix[pos - distance] == UBOW)
			return distance;
	
	return 0;
}