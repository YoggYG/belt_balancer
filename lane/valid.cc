#include "lane.ih"

bool Lane::valid(vector<Tile> &matrix)
{
	size_t numSplit = 0;
	for (vector<Triple>::iterator it = d_path.begin(); it != d_path.end(); ++it)
		if (it->item > MAXVAL)
			++numSplit;

	if (numSplit != d_power)
		return false;
	
	return true;
}