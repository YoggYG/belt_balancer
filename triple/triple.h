#ifndef TRIPLE_H
#define TRIPLE_H
#include <cstddef>
#include "../tile/tile.h"

struct Triple
{
	size_t x;
	size_t y;
	Tile tile;
};

#endif