#include "balancer.ih"

char Balancer::requiresHorizontalUndergroundBelt(size_t pos)
{
	if ((pos + 1) % d_cols < 4 or pos < d_cols or pos > d_matrix.size() - d_cols) // actually pos >= d_matrix.size() - d_cols, but the equals is made redundant by the first clause.
		return EMPTY;

	size_t distance = horizontalUndergroundBeltDistance(pos);

	if (distance == 0)
		return EMPTY;

	size_t len = 0;
	do
	{
		if ((pos + len + 1) % d_cols == 0 or distance + len + 1 == d_underground_length)
		{
			if (d_matrix[pos - distance] == UBIE)
				return UBOE;
			else
				return UBIW;
		}
		++len;
	} while (isSplitter(d_matrix[pos + len]));

	return EMPTY;
}