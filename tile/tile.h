#ifndef TILE_H
#define TILE_H
#include <cstddef>

class Tile
{
	public:
		size_t item;
		size_t ugN;
		size_t ugE;
		size_t ugS;
		size_t ugW;

		bool operator==(Tile const &rhs) const;
		bool operator!=(Tile const &rhs) const;

		bool operator==(size_t const &rhs) const;
		bool operator!=(size_t const &rhs) const;
		
		Tile &operator++();
		Tile operator++(int);
};

inline bool Tile::operator==(Tile const &rhs) const
{
	return item == rhs.item;
}

inline bool	Tile::operator!=(Tile const	&rhs) const
{
	return !(*this == rhs);
}

inline bool Tile::operator==(size_t const &rhs) const
{
	return item == rhs;
}

inline bool Tile::operator!=(size_t const &rhs) const
{
	return !(*this == rhs);
}

inline Tile &Tile::operator++()
{
	++(this->item);
	return *this;
}

inline Tile Tile::operator++(int)
{
	Tile temp = *this;
	++(this->item);
	return temp;
}

#endif