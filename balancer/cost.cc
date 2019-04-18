#include "balancer.ih"

size_t Balancer::cost()
{
	size_t cost = 0;
	for (vector<Tile>::iterator it = d_matrix.begin(); it != d_matrix.end(); ++it)
		switch (it->item)
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
			case 12: cost += d_underground_cost_penalty; break;
		}

	size_t emptyRows;
	size_t emptyCols;

	for (emptyCols = 0; emptyCols < d_cols; ++emptyCols)
	{
		bool empty = true;
		for (size_t idx = d_cols - 1 - emptyCols; idx < d_matrix.size(); idx += d_cols)
		{
			if (d_matrix[idx] != EMPTY)
			{
				empty = false;
				break;
			}
		}
		if (empty == false)
			break;
	}	

	for (emptyRows = 0; emptyRows < d_cols; ++emptyRows)
	{
		bool empty = true;
		for (size_t idx = d_matrix.size() - d_cols * (emptyRows + 1); idx < d_matrix.size() - d_cols * emptyRows; ++idx)
		{
			if (d_matrix[idx] != EMPTY and d_matrix[idx] != BN)
			{
				empty = false;
				break;
			}
		}
		if (empty == false)
			break;
	}	

	cost *= (d_rows - emptyRows) * (d_cols - emptyCols);
	return cost;
}