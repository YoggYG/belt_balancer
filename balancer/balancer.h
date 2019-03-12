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

	public:
		Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power);
		Balancer(Balancer const &other);
		bool valid();
		size_t cost();
		void print();
		void print2();
		bool operator==(Balancer const &rhs);
		bool nextMatrix();
		void setUndergroundLength(size_t len);
		void shrinkBalancer();
		void initMatrix();

		//size_t size() {return d_matrix.size();};
	private:
		void setUndergroundValues(size_t pos);
		size_t getMinPosOfBadLane();
		bool verticalUndergroundOK(size_t pos);
		bool horizontalUndergroundOK(size_t pos);
		bool undergroundUsefulNorth(size_t pos);
		bool undergroundUsefulEast(size_t pos);
		bool undergroundUsefulWest(size_t pos);
		bool undergroundUsefulSouth(size_t pos);
		size_t numberOfOutputBelts();
		size_t numberOfInputBelts();
		size_t sharedSplitters(Lane const &lane1, Lane const &lane2);
		bool matrixOK(size_t pos);
		bool incrMatrixUntilOK(size_t pos);
		bool isSplitter(size_t val);
		bool hasEastInput(size_t val);
		bool hasEastOutput(size_t val);
		bool hasNorthInput(size_t val);
		bool hasNorthOutput(size_t val);
		bool hasSouthInput(size_t val);
		bool hasSouthOutput(size_t val);
		bool hasWestInput(size_t val);
		bool hasWestOutput(size_t val);
		bool requiresNorthInput(size_t val);
		bool requiresEastInput(size_t val);
		bool requiresWestInput(size_t val);
		bool requiresSouthInput(size_t val);
};

inline bool Balancer::operator==(Balancer const &rhs)
{
	return d_matrix == rhs.d_matrix;
}

inline bool Balancer::isSplitter(size_t val)
{
	return val > MAXVAL;
	//return (val == SPLN or val == SPRN or val == SPLE or val == SPRE or val == SPLW or val == SPRW or val == SPLS or val == SPRS);
}

inline void Balancer::setUndergroundLength(size_t len)
{
	d_underground_length = len;
}

inline void Balancer::initMatrix()
{
	if (d_matrix.size())
		incrMatrixUntilOK(0);
}

inline bool Balancer::hasEastInput(size_t val)
{
	return (val == BN or val == BE or val == BS or val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasEastOutput(size_t val)
{
	return (val == BE or val == UBOE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasNorthInput(size_t val)
{
	return (val == BN or val == BE or val == BW or val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::hasNorthOutput(size_t val)
{
	return (val == BN or val == UBON or val == SPLN or val == SPRN);
}

inline bool Balancer::hasSouthInput(size_t val)
{
	return (val == BE or val == BW or val == BS or val == UBIS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasSouthOutput(size_t val)
{
	return (val == BS or val == UBOS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasWestInput(size_t val)
{
	return (val == BN or val == BW or val == BS or val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::hasWestOutput(size_t val)
{
	return (val == BW or val == UBOW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresNorthInput(size_t val)
{
	return (val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::requiresWestInput(size_t val)
{
	return (val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresEastInput(size_t val)
{
	return (val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::requiresSouthInput(size_t val)
{
	return (val == UBIS or val == SPLS or val == SPRS);
}

#endif