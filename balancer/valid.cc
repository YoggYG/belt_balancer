#include "balancer.ih"

bool Balancer::valid()
{
	vector<Lane> lanes;
	for (size_t idx = (d_rows - 1) * d_cols; idx < d_rows * d_cols; ++idx)
		if (d_matrix[idx] == BN)
		{
			Lane lane(d_matrix, idx, d_rows, d_cols, d_power, d_underground_length);
			if (!lane.valid(d_matrix))
			{
				cerr << "Balancer::valid() false: individual lane not valid\n";
				return false;
			}
			lanes.push_back(lane);
		}

	for (size_t idx1 = 0; idx1 < lanes.size() - 1; ++idx1)
		for (size_t idx2 = idx1 + 1; idx2 < lanes.size(); ++idx2)
			if (sharedSplitters(lanes[idx1], lanes[idx2]) > 1)
			{
				// cerr << "Balancer::valid() false: more than one shared splitter between lanes\n";
				return false;
			}
	
	vector<Tile> secondVector(d_cols * d_rows, Tile());
	for (vector<Lane>::iterator it1 = lanes.begin(); it1 != lanes.end(); ++it1)
		for (vector<Triple>::iterator it2 = it1->d_path.begin(); it2 != it1->d_path.end(); ++it2)
			if (secondVector[it2->y * d_cols + it2->x].item == 0)
				secondVector[it2->y * d_cols + it2->x].item = it2->item;
			else
			{
				cerr << "Balancer::valid() false: seperate lanes join in on each other\n";
				return false;
			}
	
	if (d_matrix != secondVector)
	{
		// cerr << "Balancer::valid() false: balancer had useless extra stuff\n";
		return false;
	}

	return true;
}