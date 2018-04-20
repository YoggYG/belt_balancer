#include "balancer.ih"

void Balancer::shrinkBalancer()
{
	size_t startingRow = 0;
	size_t endingRow = d_rows;
	for (size_t idx = 0; idx < d_matrix.size(); ++idx)
		if (d_matrix[idx].item > 1)
		{
			startingRow = idx / d_cols - 1;
			break;
		}
	for (size_t idx = d_matrix.size(); idx > 0; --idx)
		if (d_matrix[idx].item > 1)
		{
			endingRow = idx / d_cols + 2;
			break;
		}
	if (startingRow == 0 and endingRow == d_rows)
		return;

	vector<Tile> newMatrix;
	for (size_t idx = startingRow * d_cols; idx < endingRow * d_cols; ++idx)
		newMatrix.push_back(d_matrix[idx]);
	d_matrix = newMatrix;
	d_rows = endingRow - startingRow;
}