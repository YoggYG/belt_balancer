#include "balancer.ih"

bool Balancer::isEdgeCase(size_t idx)
{
	if (idx < 2 * d_cols)
		if (d_matrix[idx] == UBIN or d_matrix[idx] == UBOS)
			return true;

	if (idx > (d_rows - 2) * d_cols - 1)
		if (d_matrix[idx] == BS or d_matrix[idx] == UBON or d_matrix[idx] == UBIS)
			return true;

	if (idx % d_cols < 3)
	{
		if (d_matrix[idx] == UBIW or d_matrix[idx] == UBOE)
			return true;
		
		if (idx % d_cols == 0)
			if (d_matrix[idx] == BW or d_matrix[idx] == UBOW or d_matrix[idx] == UBIE)
				return true;
	}

	if (idx % d_cols > d_cols - 4)
	{
		if (d_matrix[idx] == UBIE or d_matrix[idx] == UBOW)
			return true;

		if (idx % d_cols == d_cols - 1)
			if (d_matrix[idx] == BE or d_matrix[idx] == UBIW or d_matrix[idx] == UBOE)
				return true;
	}

	return false;
}