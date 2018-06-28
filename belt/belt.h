#ifndef BELT_H
#define BELT_H

class Belt
{
	bool d_fixed;

	bool d_hasNorthInput;
	bool d_hasEastInput;
	bool d_hasSouthInput;
	bool d_hasWestInput;

	bool d_hasNorthOutput;
	bool d_hasEastOutput;
	bool d_hasSouthOutput;
	bool d_hasWestOutput;

	bool d_requiresNorthInput;
	bool d_requiresEastInput;
	bool d_requiresSouthInput;
	bool d_requiresWestInput;

	public:
		Belt();
		bool isFixed();
		void setFixed(bool fixed);

		bool hasNorthInput();
		bool hasEastInput();
		bool hasSouthInput();
		bool hasWestInput();

		bool hasNorthOutput();
		bool hasEastOutput();
		bool hasSouthOutput();
		bool hasWestOutput();

		bool requiresNorthInput();
		bool requiresEastInput();
		bool requiresSouthInput();
		bool requiresWestInput();

}

inline bool Belt::isFixed()
{
	return d_fixed;
}

inline void Belt::setFixed(bool fixed)
{
	d_fixed = fixed;
}

#endif