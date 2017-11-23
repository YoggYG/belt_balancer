#ifndef BALANCER_H
#define BALANCER_H

#include <vector>
#include "../lane/lane.h"
#include "../enum.h"

class Balancer
{
	std::vector<char> d_matrix;
	std::vector<Lane> d_lanes;
	size_t d_rows;
	size_t d_cols;
	size_t d_n;
	size_t d_power;

	public:
		Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power);
		bool valid();
		size_t cost();
		void print();
		bool operator==(Balancer const &rhs);
	private:
		size_t sharedSplitters(Lane const &lane1, Lane const &lane2);
		void shrinkBalancer();
};

inline Balancer::Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power)
:
	d_matrix(matrix),
	d_rows(rows),
	d_cols(cols),
	d_n(n),
	d_power(power)
{}

inline bool Balancer::operator==(Balancer const &rhs)
{
	return d_matrix == rhs.d_matrix;
}

#endif