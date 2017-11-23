#ifndef LANE_H
#define LANE_H

#include <vector>
#include "../triple/triple.h"

class Lane {
	size_t d_rows;
	size_t d_cols;
	size_t d_power;

	public:
		std::vector<Triple> d_path;
		Lane(std::vector<char> &matrix, size_t idx, size_t rows, size_t cols, size_t power);
		bool valid(std::vector<char> &matrix);
};

#endif