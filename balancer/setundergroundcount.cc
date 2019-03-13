#include "balancer.ih"

void Balancer::setUndergroundCount(size_t pos)
{
	if ((d_matrix[pos - d_cols].ugN > 0 or d_matrix[pos - d_cols].item == UBON) and d_matrix[pos - d_cols].item != UBIN)
		d_matrix[pos].ugN = d_matrix[pos - d_cols].ugN + 1;	
	if ((d_matrix[pos - 1].ugE > 0 or d_matrix[pos - 1].item == UBIE) and d_matrix[pos - 1].item != UBOE)
		d_matrix[pos].ugE = d_matrix[pos - 1].ugE + 1;
	if ((d_matrix[pos - 1].ugW > 0 or d_matrix[pos - 1].item == UBOW) and d_matrix[pos - 1].item != UBIW)
		d_matrix[pos].ugW = d_matrix[pos - 1].ugW + 1;
	if ((d_matrix[pos - d_cols].ugS > 0 or d_matrix[pos - d_cols].item == UBIS) and d_matrix[pos - d_cols].item != UBOS)
		d_matrix[pos].ugS = d_matrix[pos - d_cols].ugS + 1;		
}