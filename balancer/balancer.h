#ifndef BALANCER_H
#define BALANCER_H

#include <vector>
#include "../lane/lane.h"
#include "../tile/tile.h"
#include "../enum.h"

class Balancer
{
	std::vector<Tile> d_matrix;
	size_t d_rows;
	size_t d_cols;
	size_t d_n;
	size_t d_power;
	size_t d_underground_length = 10;
	size_t d_underground_cost_penalty = 15;

	public:
		Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power);
		bool valid();
		size_t cost();
		void print();
		void print2();
		bool operator==(Balancer const &rhs);
		bool nextMatrix();
		void setUndergroundLength(size_t len);
		bool incrMatrixUntilOK(size_t pos);
	private:
		char requiresHorizontalUndergroundBelt(size_t pos);
		size_t horizontalUndergroundBeltDistance(size_t pos);
		size_t numberOfOutputBelts();
		size_t numberOfInputBelts();
		void initMatrix(std::vector<char> &matrix);
		bool sharedSplitters(Lane const &lane1, Lane const &lane2);
		void shrinkBalancer();
		bool isEdgeCase(size_t pos);
		bool matrixOK(size_t pos);
		bool matrixOptimised(size_t pos);
		bool isSplitter(char val);
		bool isSplitter(Tile val);
		bool hasEastInput(Tile val);
		bool hasEastOutput(Tile val);
		bool hasNorthInput(Tile val);
		bool hasNorthOutput(Tile val);
		bool hasSouthInput(Tile val);
		bool hasSouthOutput(Tile val);
		bool hasWestInput(Tile val);
		bool hasWestOutput(Tile val);
		bool requiresNorthInput(Tile val);
		bool requiresEastInput(Tile val);
		bool requiresWestInput(Tile val);
		bool requiresSouthInput(Tile val);
		bool hasNorthUndergroundOutput(size_t pos);
		bool hasEastUndergroundInput(size_t pos);
		bool hasSouthUndergroundInput(size_t pos);
		bool hasWestUndergroundOutput(size_t pos);
		bool hasLoop(Tile val, Tile up, Tile upLeft, Tile left);
		std::vector<Triple> getPathOfTile(size_t pos);
};

inline Balancer::Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power)
:
	d_rows(rows),
	d_cols(cols),
	d_n(n),
	d_power(power)
{
	initMatrix(matrix);
}

inline bool Balancer::operator==(Balancer const &rhs)
{
	return d_matrix == rhs.d_matrix;
}

inline bool Balancer::isSplitter(char val)
{
	return (val == SPLN or val == SPRN or val == SPLE or val == SPRE or val == SPLW or val == SPRW or val == SPLS or val == SPRS);
}

inline bool Balancer::isSplitter(Tile val)
{
	return isSplitter(val.item);
}

inline void Balancer::setUndergroundLength(size_t len)
{
	d_underground_length = len;
}

inline bool Balancer::hasEastInput(Tile val)
{
	return (val == BN or val == BE or val == BS or val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasEastOutput(Tile val)
{
	return (val == BE or val == UBOE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasNorthInput(Tile val)
{
	return (val == BN or val == BE or val == BW or val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::hasNorthOutput(Tile val)
{
	return (val == BN or val == UBON or val == SPLN or val == SPRN);
}

inline bool Balancer::hasSouthInput(Tile val)
{
	return (val == BE or val == BW or val == BS or val == UBIS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasSouthOutput(Tile val)
{
	return (val == BS or val == UBOS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasWestInput(Tile val)
{
	return (val == BN or val == BW or val == BS or val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::hasWestOutput(Tile val)
{
	return (val == BW or val == UBOW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresNorthInput(Tile val)
{
	return (val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::requiresWestInput(Tile val)
{
	return (val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresEastInput(Tile val)
{
	return (val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::requiresSouthInput(Tile val)
{
	return (val == UBIS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasLoop(Tile val, Tile up, Tile upLeft, Tile left)
{
	if (val == BN)
	{
		if (up == BW)
		{
			if (upLeft == BS)
				return left == BW or left == BS or left == BE;

			return (upLeft == BN or upLeft == BW) and left == BE;
		}
		
		return (up == BN or up == BE) and upLeft == BS and left == BE;
	}
		
	if (val == BW)
	{
		if (up == BS)
		{
			if (upLeft == BE)
				return left == BS or left == BW or left == BN;

			return (upLeft == BN or upLeft == BW) and left == BN;
		}

		return (up == BE or up == BN) and upLeft == BE and left == BN;
	}

	return (val == BS or val == BE) and ((up == BS and upLeft == BE and left == BN) or (up == BW and upLeft == BS and left == BE));
}

#endif