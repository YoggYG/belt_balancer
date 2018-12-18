#include "balancer.ih"

size_t Balancer::horizontalUndergroundBeltDistance(size_t pos)
{
	for (size_t distance = 2; distance < d_underground_length or (pos - distance) % d_cols != 0; ++distance)
		if (d_matrix[pos - distance].item == UBIE or d_matrix[pos - distance].item == UBOW)
			return distance;
	
	return 0;
}