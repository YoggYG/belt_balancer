#include "balancer.ih"

size_t Balancer::cost()
{
	size_t cost = 0;
	for (vector<char>::iterator it = d_matrix.begin(); it != d_matrix.end(); ++it)
		switch (*it)
		{
			case 1:
			case 2:
			case 3:
			case 4:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20: ++cost; break;
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12: cost += 10; break;
		}
	cost *= d_rows * d_cols;
	return cost;
}