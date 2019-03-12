#include "balancer.ih"

Balancer::Balancer(vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power)
:
	d_rows(rows),
	d_cols(cols),
	d_n(n),
	d_power(power)
{
	for (size_t idx = 0; idx < matrix.size(); ++idx)
		d_matrix.push_back(Tile((size_t)matrix[idx]));	

	// print();
}