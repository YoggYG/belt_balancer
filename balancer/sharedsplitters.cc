#include "balancer.ih"

size_t Balancer::sharedSplitters(Lane const &lane1, Lane const &lane2)
{
	size_t res = 0;
	for (size_t idx1 = 0; idx1 < lane1.d_path.size(); ++idx1)
	{
		if (not isSplitter(lane1.d_path[idx1].item))
			continue;
		
		for (size_t idx2 = 0; idx2 < lane2.d_path.size(); ++idx2)
		{
			if (not isSplitter(lane2.d_path[idx2].item)) //not a splitter
				continue;
			if (lane2.d_path[idx2].item == lane1.d_path[idx1].item) //the same half of splitter
				continue;
			if ((lane2.d_path[idx2].item) / 2 != (lane1.d_path[idx1].item) / 2) //non-complementary halves
				continue;
			switch (lane1.d_path[idx1].item) //the two splitters are complementary by their halves
			{
				case SPLN:
				case SPRS:
					if (lane1.d_path[idx1].y == lane2.d_path[idx2].y)
						if (lane1.d_path[idx1].x == lane2.d_path[idx2].x - 1)
							if (++res > 1)
								return res;
					break;
				case SPRN:
				case SPLS:
					if (lane1.d_path[idx1].y == lane2.d_path[idx2].y)
						if (lane1.d_path[idx1].x == lane2.d_path[idx2].x + 1)
							if (++res > 1)
								return res;
					break;
				case SPLE:
				case SPRW:
					if (lane1.d_path[idx1].y == lane2.d_path[idx2].y + 1)
						if (lane1.d_path[idx1].x == lane2.d_path[idx2].x)
							if (++res > 1)
								return res;
					break;
				case SPRE:
				case SPLW:
					if (lane1.d_path[idx1].y == lane2.d_path[idx2].y - 1)
						if (lane1.d_path[idx1].x == lane2.d_path[idx2].x)
							if (++res > 1)
								return res;
					break;
			}
		}
	}
	return res;
}