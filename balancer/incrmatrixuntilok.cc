#include "balancer.ih"

void Balancer::incrMatrixUntilOK(size_t pos)
{
	char maxVal = 21;
	if (pos < d_cols or pos >= (d_rows - 1) * d_cols)
		maxVal = 2;

	while (d_matrix[pos] < maxVal and not matrixOK(pos))
		do
			++d_matrix[pos];
		while (isEdgeCase(pos));

	if (d_matrix[pos] >= maxVal and pos > 0)
	{
		size_t prevPos = pos - 1;

		while (prevPos > 0 and isSplitter(d_matrix[prevPos]))
			--prevPos;

		do
			++d_matrix[prevPos];
		while (isEdgeCase(prevPos));

		d_matrix[pos] = EMPTY;
		incrMatrixUntilOK(prevPos);
	}

	if (pos + 1 < d_matrix.size())
	{
		size_t nextPos = pos + 1;

		while (nextPos + 1 < d_matrix.size() and isSplitter(d_matrix[nextPos]))
			++nextPos;

		incrMatrixUntilOK(nextPos);
	}
}