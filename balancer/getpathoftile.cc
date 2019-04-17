#include "balancer.ih"
#include <iostream>

vector<Triple> Balancer::getPathOfTile(size_t pos, bool forward, bool backward)
{
	vector<Triple> resVector;

	resVector.push_back(Triple{getX(pos), getY(pos), d_matrix[pos]});
	size_t idx = pos;

	if (backward)
	{
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
				case SPLN:
				case SPRN:
				case UBIN: idx += d_cols; break;
				case SPLE:
				case SPRE:
				case UBIE: --idx; break;
				case SPLW:
				case SPRW:
				case UBIW: ++idx; break;
				case SPLS:
				case SPRS:
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
							cerr << "UBOE d_underground_length set.\n";
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
					cerr << "SOMETHING WENT WRONG IN backward getPathOfTile\n";
			}

			if (len == d_underground_length or d_matrix[idx] == EMPTY)
				break;

			if (idx == pos)
				return vector<Triple>();

			resVector.insert(resVector.begin(), Triple{getX(idx), getY(idx), d_matrix[idx]});

			if (isSplitter(d_matrix[idx]))
				break;			
		}

		idx = pos;
	}

	if (forward)
	{
		while (getY(idx) != 0)
		{
			size_t len = 0;
			switch (d_matrix[idx].item)
			{
				case BN:
				case UBON:
				case SPLN:
				case SPRN:
					idx -= d_cols;
					break;
				case BE:
				case UBOE:
				case SPLE:
				case SPRE:
					++idx;
					break;
				case BW:
				case UBOW:
				case SPLW:
				case SPRW:
					--idx;
					break;
				case BS:
				case UBOS:
				case SPLS:
				case SPRS:
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
							cerr << "UBIW d_underground_length set.\n";
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
					cerr << "SOMETHING WENT WRONG IN forward getPathOfTile, item: " << d_matrix[idx].item << endl;
			}

			if (len == d_underground_length or d_matrix[idx] == EMPTY)
				break;

			resVector.push_back(Triple{getX(idx), getY(idx), d_matrix[idx]});

			if (isSplitter(d_matrix[idx]))
				break;
		}
	}

	if (not (forward and backward))
		return resVector;

	// Test if there is a shorter path possible from the path start to the path end

	if (resVector.size() < 4) // a path with max length of 3 is always optimal
		return resVector;

	bool isExit = false;
	bool isEntry = false;

	Triple endTile = resVector.back();
	Triple startTile = resVector.front();

	if (endTile == startTile) // loop detection
		return vector<Triple>();

	if (endTile.y == 0)
		isExit = true;

	if (startTile.y == d_rows - 1)
		isEntry = true;

	if (isEntry and isExit)
		return vector<Triple>();

	size_t pathLength = 0;

	// set original path length here TODO: put in function
	for (auto it = resVector.begin(); it != resVector.end(); ++it)
	{
		++pathLength;

		switch (it->tile.item)
		{
			// case UBIN: pathLength += it->tile.ugN; break;
			// case UBOE: pathLength += it->tile.ugE; break;
			// case UBOS: pathLength += it->tile.ugS; break;
			// case UBIW: pathLength += it->tile.ugW; break;
			case UBIN: 
			case UBIE: 
			case UBIS: 
			case UBIW: pathLength += d_underground_cost_penalty; break;
		}
	}

	size_t manHattanDistance = 1; // include the first tile into the path length

	if (endTile.x > startTile.x)
		manHattanDistance += endTile.x - startTile.x;
	else
		manHattanDistance += startTile.x - endTile.x;

	if (endTile.y > startTile.y)
		manHattanDistance += endTile.y - startTile.y;
	else
		manHattanDistance += startTile.y - endTile.y;

	if (pathLength == manHattanDistance and not (isEntry or isExit)) // shortest path possible
		return resVector;

	vector<Tile> copiedMatrix(d_matrix);

	for (auto it = resVector.begin(); it != resVector.end(); ++it)
	{
		idx = it->x + it->y * d_cols;

		copiedMatrix[idx].item = EMPTY;

		switch (it->tile.item)
		{
			case UBIN:
				while (copiedMatrix[idx].ugN > 0)
				{
					copiedMatrix[idx].ugN = 0;
					idx -= d_cols;
				}
				break;
			case UBOS:
				while (copiedMatrix[idx].ugS > 0)
				{
					copiedMatrix[idx].ugS = 0;
					idx -= d_cols;
				}
				break;
			case UBOE:
				while (copiedMatrix[idx].ugE > 0)
				{
					copiedMatrix[idx].ugE = 0;
					--idx;
				}
				break;
			case UBIW:
				while (copiedMatrix[idx].ugW > 0)
				{
					copiedMatrix[idx].ugW = 0;
					--idx;
				}
				break;
		}
	}

	vector<Triple> generatedPath;

	if (isEntry) // Find path backwards from current path end to bottom of balancer
	{
		idx = getIdx(endTile.x, endTile.y);
		size_t nextIdx = getIdx(resVector[resVector.size() - 2].x, resVector[resVector.size() - 2].y);
		
		copiedMatrix[idx].item = endTile.tile.item;

		if (existsShorterEntryPath(copiedMatrix, pathLength, 1, idx, nextIdx))
			return vector<Triple>();
	}
	else 
	{
		idx = getIdx(startTile.x, startTile.y);
		size_t nextIdx = getIdx(resVector[1].x, resVector[1].y);
		
		copiedMatrix[idx].item = startTile.tile.item;

		if (isExit) // Find path forwards from current path start to top of balancer
		{
			if (existsShorterExitPath(copiedMatrix, pathLength, 1, idx, nextIdx))
				return vector<Triple>();
		}
		else
		{
			if (existsShorterMiddlePath(copiedMatrix, endTile, pathLength, 1, idx, nextIdx))
				return vector<Triple>();
		}
	}

	return resVector;
}