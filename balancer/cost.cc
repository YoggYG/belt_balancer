#include "balancer.ih"

size_t Balancer::cost()
{
	size_t cost = 0;
	for (vector<Tile>::iterator it = d_matrix.begin(); it != d_matrix.end(); ++it)
		switch ((*it).item)
		{
			case BN:
			case BE:
			case BW:
			case BS:
			case SPLN:
			case SPRN:
			case SPLE:
			case SPRE:
			case SPLW:
			case SPRW:
			case SPLS:
			case SPRS: ++cost; break;
			case UBIN:
			case UBON:
			case UBIE:
			case UBOE:
			case UBIW:
			case UBOW:
			case UBIS:
			case UBOS: cost += 10; break;
		}
	cost *= d_rows * d_cols;
	return cost;
}