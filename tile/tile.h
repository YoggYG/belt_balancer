#ifndef TILE_H
#define TILE_H
#include <cstddef>
#include <iostream>

class Tile
{
	//maybe add "immutable" field or method, and a list to every tile with the possible belt types of that specific tile. "Add/Next" operator to increment to the next possible value.

	public:
		size_t item;
		size_t ugN;
		size_t ugE;
		size_t ugS;
		size_t ugW;
		size_t lane;

		Tile();
		Tile(size_t it);
		Tile(size_t it, size_t uN, size_t uE, size_t uS, size_t uW, size_t laneArg);
		Tile(Tile const &other);

		void operator=(Tile const &other);

		bool operator==(Tile const &rhs) const;
		bool operator!=(Tile const &rhs) const;

		bool operator==(size_t const &rhs) const;
		bool operator!=(size_t const &rhs) const;
		
		Tile &operator++();
		Tile operator++(int);
};

inline Tile::Tile()
:
	item(0),
	ugN(0),
	ugE(0),
	ugS(0),
	ugW(0),
	lane(0)
{}

inline Tile::Tile(size_t it)
:
	item(it),
	ugN(0),
	ugE(0),
	ugS(0),
	ugW(0),
	lane(0)
{}

inline Tile::Tile(size_t it, size_t uN, size_t uE, size_t uS, size_t uW, size_t laneArg)
:
	item(it),
	ugN(uN),
	ugE(uE),
	ugS(uS),
	ugW(uW),
	lane(laneArg)
{
	std::cerr << "Tile constructor with all individual arguments called\n";
}

inline Tile::Tile(Tile const &other)
:
	item(other.item),
	ugN(other.ugN),
	ugE(other.ugE),
	ugS(other.ugS),
	ugW(other.ugW),
	lane(other.lane)
{}

inline void Tile::operator=(Tile const &other)
{
	item = other.item;
	ugN = other.ugN;
	ugE = other.ugE;
	ugS = other.ugS;
	ugW = other.ugW;
	lane = other.lane;
}

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