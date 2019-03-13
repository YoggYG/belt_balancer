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

		Tile(size_t value);
		bool operator==(Tile const &rhs) const;
		bool operator==(size_t const &rhs) const;
		bool operator!=(Tile const &rhs) const;
		bool operator!=(size_t const &rhs) const;
		void operator++();
		void operator++(int);
};

inline Tile::Tile(size_t value) : item(value)
{
	ugN = 0;
	ugE	= 0;
	ugS = 0;
	ugW = 0;
}

inline bool Tile::operator==(Tile const &rhs) const
{
	return item == rhs.item/* and ugN == rhs.ugN and ugE == rhs.ugE and ugS == rhs.ugS and ugW == rhs.ugW*/;
}

inline bool Tile::operator==(size_t const &rhs) const
{
	return item == rhs;
}

inline bool Tile::operator!=(Tile const &rhs) const
{
	return !this->operator==(rhs);
}

inline bool Tile::operator!=(size_t const &rhs) const
{
	return !this->operator==(rhs);
}

inline void Tile::operator++()
{
	++item;
}

inline void Tile::operator++(int)
{
	item++;
}

#endif