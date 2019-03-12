#include "balancer.ih"

bool Balancer::sharedSplitters(Lane const &lane1, Lane const &lane2)
{
	size_t splitterNumberL1 = 0;
	size_t res = 0;
	for (size_t idx1 = 0; idx1 < lane1.d_path.size(); ++idx1)
	{
		if (not isSplitter(lane1.d_path[idx1].tile.item))
			continue;

		++splitterNumberL1;
		size_t splitterNumberL2 = 0;

		for (size_t idx2 = 0; idx2 < lane2.d_path.size(); ++idx2)
		{
			if (not isSplitter(lane2.d_path[idx2].tile.item)) //not a splitter
				continue;

			++splitterNumberL2;

			if (lane2.d_path[idx2].tile.item == lane1.d_path[idx1].tile.item) //the same half of splitter
				continue;
			
			if ((lane2.d_path[idx2].tile.item + 1) / 2 != (lane1.d_path[idx1].tile.item + 1) / 2) //non-complementary halves
				continue;
			
			int xOffset = 0;
			int yOffset = 0;

			switch (lane1.d_path[idx1].tile.item) //the two splitters are complementary by their halves
			{
				case SPLN:
				case SPRS:
					xOffset = -1;
					break;
				case SPRN:
				case SPLS:
					xOffset = 1;
					break;
				case SPLE:
				case SPRW:
					yOffset = -1;
					break;
				case SPRE:
				case SPLW:
					yOffset = 1;
					break;
			}

			if (lane1.d_path[idx1].y == lane2.d_path[idx2].y + yOffset)
				if (lane1.d_path[idx1].x == lane2.d_path[idx2].x + xOffset)
				{
					if (splitterNumberL1 != splitterNumberL2)
						return false;
					
					if (res > 0)
						return false;
					
					++res;					
				}
		}
	}

	if (res > 1)
	{
		cerr << "Impossible statement in sharedSplitters\n";
		return false;
	}

	return true;
}