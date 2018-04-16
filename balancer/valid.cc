#include "balancer.ih"

bool Balancer::valid()
{
	//shrinkBalancer();
	// size_t numberOfSplitters = 0;
	// for (vector<char>::iterator it = d_matrix.begin(); it != d_matrix.end(); ++it)
	// 	if (isSplitter(*it))
	// 		++numberOfSplitters;

	// if (numberOfSplitters != (d_power * d_n))
	// 	return false;

	size_t numberOfLanes = 0;
	vector<Lane> lanes;
	for (size_t idx = (d_rows - 1) * d_cols; idx < d_rows * d_cols; ++idx)
	{
		if (numberOfLanes > d_n)
			return false;
		if (d_matrix[idx] == BN)
		{
			Lane lane(d_matrix, idx, d_rows, d_cols, d_power);
			lanes.push_back(lane);
			if (!lane.valid(d_matrix))
				return false;
			++numberOfLanes;
		}
	}

	if (numberOfLanes != d_n)
		return false;

	numberOfLanes = 0;
	for (size_t idx = 0; idx < d_cols; ++idx)
		if (d_matrix[idx] == 1)
			++numberOfLanes;
	if (numberOfLanes != d_n)
		return false;

	for (size_t idx1 = 0; idx1 < lanes.size() - 1; ++idx1)
		for (size_t idx2 = idx1 + 1; idx2 < lanes.size(); ++idx2)
			if (sharedSplitters(lanes[idx1], lanes[idx2]) > 1)
				return false;
	
	vector<char> secondVector(d_cols * d_rows, 0);
	for (vector<Lane>::iterator it1 = lanes.begin(); it1 != lanes.end(); ++it1)
		for (vector<Triple>::iterator it2 = it1->d_path.begin(); it2 != it1->d_path.end(); ++it2)
			if (secondVector[it2->y * d_cols + it2->x] == 0)
				secondVector[it2->y * d_cols + it2->x] = it2->item;
			else
				return false;
	
	if (d_matrix != secondVector)
		return false;
		//d_matrix = secondVector;

	return true;
}