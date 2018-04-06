#ifndef BALANCER_H
#define BALANCER_H

#include <vector>
#include "../lane/lane.h"
#include "../enum.h"

class Balancer
{
	std::vector<char> d_matrix;
	std::vector<Lane> d_lanes;
	size_t d_rows;
	size_t d_cols;
	size_t d_n;
	size_t d_power;

	public:
		Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power);
		bool valid();
		size_t cost();
		void print();
		bool operator==(Balancer const &rhs);
		bool nextMatrix();
		bool incrMatrixUntilOK(size_t pos);
	private:
		size_t sharedSplitters(Lane const &lane1, Lane const &lane2);
		void shrinkBalancer();
		bool isEdgeCase(size_t pos);
		bool matrixOK(size_t pos);
		bool isSplitter(char val);
		bool hasEastInput(char val);
		bool hasEastOutput(char val);
		bool hasNorthInput(char val);
		bool hasNorthOutput(char val);
		bool hasSouthInput(char val);
		bool hasSouthOutput(char val);
		bool hasWestInput(char val);
		bool hasWestOutput(char val);
		bool requiresNorthInput(char val);
		bool requiresEastInput(char val);
		bool requiresWestInput(char val);
		bool requiresSouthInput(char val);
};

inline Balancer::Balancer(std::vector<char> &matrix, size_t rows, size_t cols, size_t n, size_t power)
:
	d_matrix(matrix),
	d_rows(rows),
	d_cols(cols),
	d_n(n),
	d_power(power)
{}

inline bool Balancer::operator==(Balancer const &rhs)
{
	return d_matrix == rhs.d_matrix;
}

inline bool Balancer::isSplitter(char val)
{
	return (val == SPLN or val == SPRN or val == SPLE or val == SPRE or val == SPLW or val == SPRW or val == SPLS or val == SPRS);
}

inline bool Balancer::hasEastInput(char val)
{
	return (val == BN or val == BE or val == BS or val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasEastOutput(char val)
{
	return (val == BE or val == UBOE or val == SPLE or val == SPRE);
}

inline bool Balancer::hasNorthInput(char val)
{
	return (val == BN or val == BE or val == BW or val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::hasNorthOutput(char val)
{
	return (val == BN or val == UBON or val == SPLN or val == SPRN);
}

inline bool Balancer::hasSouthInput(char val)
{
	return (val == BE or val == BW or val == BS or val == UBIS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasSouthOutput(char val)
{
	return (val == BS or val == UBOS or val == SPLS or val == SPRS);
}

inline bool Balancer::hasWestInput(char val)
{
	return (val == BN or val == BW or val == BS or val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::hasWestOutput(char val)
{
	return (val == BW or val == UBOW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresNorthInput(char val)
{
	return (val == UBIN or val == SPLN or val == SPRN);
}

inline bool Balancer::requiresWestInput(char val)
{
	return (val == UBIW or val == SPLW or val == SPRW);
}

inline bool Balancer::requiresEastInput(char val)
{
	return (val == UBIE or val == SPLE or val == SPRE);
}

inline bool Balancer::requiresSouthInput(char val)
{
	return (val == UBIS or val == SPLS or val == SPRS);
}

#endif