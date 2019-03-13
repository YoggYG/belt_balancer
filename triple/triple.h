#ifndef TRIPLE_H
#define TRIPLE_H
#include <cstddef>
#include "../tile/tile.h"

struct Triple
{
	size_t x;
	size_t y;
	Tile tile;
	bool operator==(Triple const &rhs) const;
	bool operator!=(Triple const &rhs) const;
};

inline bool Triple::operator==(Triple const &rhs) const
{
	return x == rhs.x and y == rhs.y and tile == rhs.tile;
}

inline bool Triple::operator!=(Triple const &rhs) const
{
	return not this->operator==(rhs);
}

#endif