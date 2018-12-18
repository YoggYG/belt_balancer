#include "lane.ih"

bool Lane::hasLoops(vector<Tile> &matrix)
{
	for (size_t idx = 0; idx < d_path.size() - 1; ++idx)
		for (size_t neighbour = idx + 1; neighbour < d_path.size(); ++neighbour)
		{
			switch (d_path[idx].item)
			{
				case BN:
					break;
			}
		}

	return false;
}