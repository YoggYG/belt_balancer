#include "balancer.ih"

void Balancer::shrinkBalancer()
{
	// size_t startingRow = 0;
	// size_t endingRow = d_rows;
	// for (size_t idx = d_cols; idx < d_matrix.size(); ++idx)
	// 	if (d_matrix[idx].item > 1)
	// 	{
	// 		startingRow = idx / d_cols - 1;
	// 		break;
	// 	}
	// for (size_t idx = d_matrix.size() - d_cols - 1; idx > 0; --idx)
	// 	if (d_matrix[idx].item > 1)
	// 	{
	// 		endingRow = idx / d_cols + 2;
	// 		break;
	// 	}
	// if (startingRow == 0 and endingRow == d_rows)
	// 	return;

	// cerr << "startingRow: " << startingRow << ", endingRow: " << endingRow << endl;

	// cerr << "d_matrix.size(): " << d_matrix.size() << endl;
	// vector<Tile> newMatrix;
	// for (size_t idx = startingRow * d_cols; idx < endingRow * d_cols; ++idx)
	// 	newMatrix.push_back(d_matrix[idx]);

	// cerr << "d_matrix.size(): " << d_matrix.size() << endl;
	// d_matrix = newMatrix;
	// cerr << "d_matrix.size(): " << d_matrix.size() << ", newMatrix.size(): " << newMatrix.size() << endl;
	// d_rows = endingRow - startingRow;

// NEW VERSION BELOW

	bool rowNecessary[d_rows];
	bool colNecessary[d_cols];

	rowNecessary[0] = true;
	rowNecessary[d_rows - 1] = true;

	size_t amountNecessaryRows = 2;
	size_t amountNecessaryCols = 0;

	for (size_t row = 1; row < d_rows - 1; ++row)
	{
		size_t idx = row * d_cols;
		rowNecessary[row] = false;
		for (size_t col = 0; col < d_cols; ++col)
		{
			if (d_matrix[idx].item != EMPTY and d_matrix[idx].item != BN and d_matrix[idx].item != BS)
			{
				rowNecessary[row] = true;
				++amountNecessaryRows;
				break;
			}
			++idx;
		}
	}

	for (size_t col = 0; col < d_cols; ++col)
	{
		size_t idx = col;
		colNecessary[col] = false;
		for (size_t row = 0; row < d_rows; ++row)
		{
			if (d_matrix[idx].item != EMPTY and d_matrix[idx].item != BE and d_matrix[idx].item != BW)
			{
				colNecessary[col] = true;
				++amountNecessaryCols;
				break;
			}
			idx += d_cols;
		}
	}

	if (amountNecessaryCols == d_cols and amountNecessaryRows == d_rows)
		return;

	vector<Tile> newMatrix;
	for (size_t row = 0; row < d_rows; ++row)
		if (rowNecessary[row])
			for (size_t col = 0; col < d_cols; ++col)
				if (colNecessary[col])
					newMatrix.push_back(d_matrix[row * d_cols + col]);

	d_cols = amountNecessaryCols;
	d_rows = amountNecessaryRows;
	d_matrix = newMatrix;
}