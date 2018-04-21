#include "balancer.ih"

Balancer::Balancer(Balancer const &other)
:
	d_matrix(vector<Tile>(other.d_matrix.size())),
	d_rows(other.d_rows),
	d_cols(other.d_cols),
	d_n(other.d_n),
	d_power(other.d_power),
	d_underground_length(other.d_underground_length)
{
	for (size_t idx = 0; idx < d_matrix.size(); ++idx)
		d_matrix[idx] = other.d_matrix[idx];
}