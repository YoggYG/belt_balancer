#ifndef TILE_H
#define TILE_H
#include <cstddef>

struct Tile
{
	size_t item;
	size_t ugN;
	size_t ugE;
	size_t ugS;
	size_t ugW;

	bool operator==(Tile const &rhs);
};

inline bool Tile::operator==(Tile const &rhs)
{
	return item == rhs.item and ugN == rhs.ugN and ugE == rhs.ugE and ugS == rhs.ugS and ugW == rhs.ugW;
}

#endif