#ifndef LANE_H
#define LANE_H

#include <vector>
#include "../triple/triple.h"
#include "../tile/tile.h"

class Lane 
{
	size_t d_rows;
	size_t d_cols;
	size_t d_power;

	public:
		std::vector<Triple> d_path;
		Lane(std::vector<Tile> &matrix, size_t idx, size_t rows, size_t cols, size_t power, size_t underground_distance);
		bool valid(std::vector<Tile> &matrix);
};

#endif