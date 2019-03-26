#include "balancer.ih"

size_t Balancer::getIdxOfComplementarySplitterHalf(size_t idx)
{
	if (d_matrix[idx] == SPLN or d_matrix[idx] == SPRS)
		return idx + 1;
	else if (d_matrix[idx] == SPRN or d_matrix[idx] == SPLS)
		return idx - 1;
	else if (d_matrix[idx] == SPLE or d_matrix[idx] == SPRW)
		return idx + d_cols;
	else
		return idx - d_cols;
}