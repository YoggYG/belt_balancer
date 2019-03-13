#include "balancer.ih"

bool Balancer::incrMatrixUntilOK(size_t pos)
{
	if (d_matrix[0].item > 1)
		return false;

	size_t maxVal = 13;
	if (pos < d_cols or pos >= (d_rows - 1) * d_cols)
		maxVal = 2;

	while (d_matrix[pos].item < maxVal and (not matrixOK(pos) or not matrixOptimised(pos)))
		do
			++d_matrix[pos];
		while (isEdgeCase(pos));

	if (d_matrix[pos].item >= maxVal and pos > 0)
	{
		size_t prevPos = pos;

		do
		{
			resetUndergroundCount(prevPos);
			--prevPos;
		}
		while (prevPos > 0 and isSplitter(d_matrix[prevPos]));

		do
			++d_matrix[prevPos];
		while (isEdgeCase(prevPos));

		d_matrix[pos].item = EMPTY;
		return incrMatrixUntilOK(prevPos);
	}
	
	if (pos + 1 < d_matrix.size())
	{
		size_t nextPos = pos;

		do
		{
			++nextPos;
			if (nextPos > d_cols)
				setUndergroundCount(nextPos);
		}
		while (nextPos + 1 < d_matrix.size() and isSplitter(d_matrix[nextPos]));

		return incrMatrixUntilOK(nextPos);
	}

	if (d_matrix[0].item > 1)
	{
		cerr << "incrMatrixUntilOK returned false at second check\n";
		return false;
	}

	return true;
}