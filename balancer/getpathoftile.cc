#include "balancer.ih"
#include <iostream>

vector<Triple> Balancer::getPathOfTile(size_t pos)
{
	vector<Triple> resVector;

	resVector.push_back(Triple{pos % d_cols, pos / d_cols, d_matrix[pos].item});
	size_t idx = pos;

	while (idx / d_cols != 0)
	{
		size_t len = 0;
		switch (d_matrix[idx].item)
		{
			case BN:
			case UBON:
				idx -= d_cols;
				break;
			case BE:
			case UBOE:
				++idx;
				break;
			case BW:
			case UBOW:
				--idx;
				break;
			case BS:
			case UBOS:
				idx += d_cols;
				break;
			case UBIN:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx < len * d_cols + d_cols)
					{
						len = d_underground_length;
						cerr << "UBIN d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx - len * d_cols] == UBON)
					{
						idx -= len * d_cols;
						break;
					}
				}
				break;
			case UBIE:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx % d_cols + len == d_cols - 1)
					{
						len = d_underground_length;
						// cerr << "UBIE d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx + len] == UBOE)
					{
						idx += len;
						break;
					}
				}
				break;
			case UBIW:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx % d_cols - len == 0)
					{
						len = d_underground_length;
						// cerr << "UBIW d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx - len] == UBOW)
					{
						idx -= len;
						break;
					}
				}
				break;
			case UBIS:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx + len * d_cols >= d_matrix.size() - d_cols)
					{
						len = d_underground_length;
						// cerr << "UBIS d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx + len * d_cols] == UBOS)
					{
						idx += len * d_cols;
						break;
					}
				}
				break;
			
			default:
				cerr << "SOMETHING WENT WRONG IN getPathOfTile\n";
		}

		if (len == d_underground_length or d_matrix[idx] == EMPTY)
			break;

		if (idx == pos)
			return vector<Triple>();

		resVector.push_back(Triple{idx % d_cols, idx / d_cols, d_matrix[idx]});

		if (isSplitter(d_matrix[idx]))
			break;
	}

	idx = pos;

	while (idx < d_matrix.size() - d_cols)
	{
		size_t len = 0;
		switch (d_matrix[idx].item)
		{
			case BN: 
			case BE:
			case BW:
			case BS:
				if (hasNorthOutput(d_matrix[idx + d_cols]))
					idx += d_cols;
				else if (hasEastOutput(d_matrix[idx - 1]))
					--idx;
				else if (hasWestOutput(d_matrix[idx + 1]))
					++idx;
				else if (hasSouthOutput(d_matrix[idx - d_cols]))
					idx -= d_cols;
				else
					len = d_underground_length;
				break;
			case UBIN: idx += d_cols; break;
			case UBIE: --idx; break;
			case UBIW: ++idx; break;
			case UBIS: idx -= d_cols; break;
			case UBON:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx + len * d_cols >= d_matrix.size() - d_cols)
					{
						len = d_underground_length;
						// cerr << "UBON d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx + len * d_cols] == UBIN)
					{
						idx += len * d_cols;
						break;
					}
				}
				break;
			case UBOE:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx % d_cols - len == 0)
					{
						len = d_underground_length;
						// cerr << "UBOE d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx - len] == UBIE)
					{
						idx -= len;
						break;
					}
				}
				break;
			case UBOW:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx % d_cols + len == d_cols - 1)
					{
						len = d_underground_length;
						// cerr << "UBOW d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx + len] == UBIW)
					{
						idx += len;
						break;
					}
				}
				break;
			case UBOS:
				for (len = 2; len < d_underground_length; ++len)
				{
					if (idx < len * d_cols + d_cols)
					{
						len = d_underground_length;
						cerr << "UBOS d_underground_length set.\n";
						break;
					}
					if (d_matrix[idx - len * d_cols] == UBIS)
					{
						idx -= len * d_cols;
						break;
					}
				}
				break;

			default:
				cerr << "SOMETHING WENT WRONG IN getPathOfTile\n";
		}

		if (len == d_underground_length or d_matrix[idx] == EMPTY)
			break;

		resVector.insert(resVector.begin(), Triple{idx % d_cols, idx / d_cols, d_matrix[idx]});

		if (isSplitter(d_matrix[idx]))
			break;

		// debug stuff, remove when working
		if (resVector.size() > d_matrix.size())
		{
			cerr << resVector.size() << ", " << idx % d_cols << "," << idx / d_cols << ", " << d_matrix[idx].item << ", pos: " << pos << endl;
			for (size_t i = 0; i < resVector.size(); ++i)
			{
				cerr << resVector[i].x << "," << resVector[i].y << ", " << resVector[i].tile.item << endl;
			}

			print();

			string c;
			cin >> c;
		}
	}

	// Test if there is a shorter path possible from the path start to the path end

	bool isExit = false;
	bool isEntry = false;

	Triple endTile = resVector.back();
	Triple startTile = resVector.front();

	if (endTile == startTile and isSplitter(startTile.tile)) // loop detection
	{
		// cerr << startTile.x << "," << startTile.y << ", " << startTile.tile.item << endl << endTile.x << "," << endTile.y << ", " << endTile.tile.item << endl;
		// print2();
		return vector<Triple>();
	}

	if (endTile.y == 0)
		isExit = true;

	if (startTile.y == d_rows - 1)
		isEntry = true;

	vector<Tile> copiedMatrix(d_matrix);

	size_t pathLength = 0;

	// set original path length here TODO: put in function
	for (auto it = resVector.begin(); it != resVector.end(); ++it)
	{
		++pathLength;

		switch (it->tile.item)
		{
			case UBIN: pathLength += it->tile.ugN; break;
			case UBOE: pathLength += it->tile.ugE; break;
			case UBOS: pathLength += it->tile.ugS; break;
			case UBIW: pathLength += it->tile.ugW; break;
		}
	}

	// for (auto it = resVector.begin(); it != resVector.end(); ++it)
	// {
	// 	idx = it->x + it->y * d_cols;

	// 	copiedMatrix[idx].item = EMPTY;

	// 	switch (it->tile.item)
	// 	{
	// 		case UBIN:
	// 			while (copiedMatrix[idx].ugN > 0)
	// 			{
	// 				copiedMatrix[idx].ugN = 0;
	// 				idx -= d_cols;
	// 			}
	// 			break;
	// 		case UBOS:
	// 			while (copiedMatrix[idx].ugS > 0)
	// 			{
	// 				copiedMatrix[idx].ugS = 0;
	// 				idx -= d_cols;
	// 			}
	// 			break;
	// 		case UBOE:
	// 			while (copiedMatrix[idx].ugE > 0)
	// 			{
	// 				copiedMatrix[idx].ugE = 0;
	// 				--idx;
	// 			}
	// 			break;
	// 		case UBIW:
	// 			while (copiedMatrix[idx].ugW > 0)
	// 			{
	// 				copiedMatrix[idx].ugE = 0;
	// 				--idx;
	// 			}
	// 			break;
	// 	}
	// }

	// Find path backwards from current path end to bottom of balancer
	if (isEntry)
	{

	}

	return resVector;
}