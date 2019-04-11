#include "balancer.ih"

bool Balancer::matrixOptimised(size_t pos)
{
	if (pos < d_cols)
		return true;

	//cerr << pos << endl;
	Tile val = d_matrix[pos];
	Tile left = EMPTY;
	Tile up = BN;
	Tile upUp = EMPTY;
	Tile upLeft = EMPTY;
	Tile upRight = EMPTY;
	Tile leftLeft = EMPTY;
	Tile down = EMPTY;
	Tile right = EMPTY;
	Tile downRight = EMPTY;
	Tile downLeft = EMPTY;
	Tile downDown = EMPTY;
	Tile rightRight = EMPTY;

	// // Check at the end of a row to see if there is only BS and BN or EMPTY on this row. If so, reject matrix.
	// if (getX(pos + 1) == 0 and pos > d_cols and pos < d_matrix.size() - d_cols) // exclude top and bottom
	// {
	// 	bool onlyNorthSouthBelts = true;
	// 	for (size_t idx = pos; idx > pos - d_cols; --idx)
	// 		if (d_matrix[idx] != EMPTY and d_matrix[idx] != BN and d_matrix[idx] != BS)
	// 		{
	// 			onlyNorthSouthBelts = false;
	// 			break;
	// 		}

	// 	if (onlyNorthSouthBelts)
	// 		return false;
	// }

	// Check at the end of a row to see if there is only BS and BN or EMPTY on this row. If so, reject matrix.
	if (getX(pos + 1) == 0 and pos > d_cols and pos < d_matrix.size() - d_cols) // exclude top and bottom
	{
		bool onlyNorthSouthBelts = true;
		bool southBelt = false;
		for (size_t idx = pos; idx > pos - d_cols; --idx)
		{
			if (d_matrix[idx] != EMPTY and d_matrix[idx] != BN and d_matrix[idx] != BS)
			{
				onlyNorthSouthBelts = false;
				break;
			}
			
			if (d_matrix[idx] == BS)
				southBelt = true;
		}

		if (onlyNorthSouthBelts and southBelt)
			return false;
	}

	if (getX(pos + 1) == 0 and pos > d_cols and pos < d_matrix.size() - d_cols)
	{
		bool onlyNorthBelts = true;
		bool splitterPresent = false;
		for (size_t idx = pos; idx > pos - d_cols; --idx)
		{
			if (not (d_matrix[idx] == EMPTY or d_matrix[idx] == BN or (d_matrix[idx] == UBIN and d_matrix[idx - d_cols] == EMPTY)))
			{
				onlyNorthBelts = false;
				break;
			}
			
			if (isSplitter(d_matrix[idx]))
				splitterPresent = true;
		}

		if (not splitterPresent)
			for (size_t idx = pos + 1; idx < d_matrix.size() - d_cols; ++idx)
				if (isSplitter(d_matrix[idx]))
				{
					splitterPresent = true;
					break;
				}

		if (onlyNorthBelts and splitterPresent)
			return false;
	}

	if (pos >= 2 * d_cols)
	{
		upUp = d_matrix[pos - 2 * d_cols];
		upLeft = d_matrix[pos - d_cols - 1];
		up = d_matrix[pos - d_cols];
		upRight = d_matrix[pos - d_cols + 1];
		leftLeft = d_matrix[pos - 2];
		left = d_matrix[pos - 1];
	}
	else if (pos > d_cols)
	{
		upLeft = d_matrix[pos - d_cols - 1];
		up = d_matrix[pos - d_cols];
		upRight = d_matrix[pos - d_cols + 1];
		leftLeft = d_matrix[pos - 2];
		left = d_matrix[pos - 1];
	}
	else if (pos == d_cols)
	{
		up = d_matrix[pos - d_cols];
		upRight = d_matrix[pos - d_cols + 1];
		leftLeft = d_matrix[pos - 2];
		left = d_matrix[pos - 1];
	}
	else if (pos > 1)
	{		
		leftLeft = d_matrix[pos - 2];
		left = d_matrix[pos - 1];
	}	
	else if (pos == 1)
	{
		left = d_matrix[pos - 1];
	}

	if (pos < d_matrix.size() - 2 * d_cols)
	{
		right = d_matrix[pos + 1];
		rightRight = d_matrix[pos + 2];
		downLeft = d_matrix[pos + d_cols - 1];
		down = d_matrix[pos + d_cols];
		downRight = d_matrix[pos + d_cols + 1];
		downDown = d_matrix[pos + 2 * d_cols];
	}
	else if (pos < d_matrix.size() - d_cols - 1)
	{
		right = d_matrix[pos + 1];
		rightRight = d_matrix[pos + 2];
		downLeft = d_matrix[pos + d_cols - 1];
		down = d_matrix[pos + d_cols];
		downRight = d_matrix[pos + d_cols + 1];
	}	
	else if (pos == d_matrix.size() - d_cols - 1)
	{
		right = d_matrix[pos + 1];
		rightRight = d_matrix[pos + 2];
		downLeft = d_matrix[pos + d_cols - 1];
		down = d_matrix[pos + d_cols];
	}
	else if (pos < d_matrix.size() - 2)
	{		
		right = d_matrix[pos + 1];
		rightRight = d_matrix[pos + 2];
	}
	else if (pos == d_matrix.size() - 2)
	{
		right = d_matrix[pos + 1];
	}

	// if (val == EMPTY)
	// 	return not (up == UBON or up == UBIS or left == UBIE or left == UBOW)
	// 			and not (up == BE and upLeft == BE and upUp == UBON and d_matrix[pos - (2 * d_cols) - 1] == BS and d_matrix[pos - 3 * d_cols] == BW and d_matrix[pos - (3 * d_cols) - 1] == BS)
	// 			and not (up == BW and upRight == BW and upUp == UBON and d_matrix[pos - (2 * d_cols) + 1] == BS and d_matrix[pos - 3 * d_cols] == BE and d_matrix[pos - (3 * d_cols) + 1] == BS)
	// 			and not (up == BW and upLeft == BS and left != SPLS and upUp == BS and d_matrix[pos - 2 * d_cols - 1] == UBON and d_matrix[pos - 3 * d_cols] == BS and d_matrix[pos - 3 * d_cols - 1] == BE)
	// 			and not (up == BE and upRight == BS and right != SPRS and upUp == BS and d_matrix[pos - 2 * d_cols + 1] == UBON and d_matrix[pos - 3 * d_cols] == BS and d_matrix[pos - 3 * d_cols + 1] == BW);

	if (val == BN)
	{
		if (left == BE and upLeft == EMPTY and (up == BN or up == BE))
			return false;

		if (pos > d_cols and down == SPRN and (left == BN or (left == UBIN and upLeft == EMPTY)))
			return false;

				// and not (left == BE and up == UBIN and upLeft == BS and upUp == BW and d_matrix[pos - (2 * d_cols) - 1] == BS 
				// 	and (d_matrix[pos - (3 * d_cols)] == UBON 
				// 		or (d_matrix[pos - (2 * d_cols) + 1] == BW and (upRight == EMPTY or upRight == BN))))
				// and not (left == BE and leftLeft == BE and upLeft == UBON and d_matrix[pos - d_cols - 2] == BS and d_matrix[pos - (2 * d_cols) - 1] == BW and d_matrix[pos - (2 * d_cols) - 2] == BS);
	}

	if (val == BE)
	{
		if (left == BE and upLeft == BS and up == EMPTY)
			return false;

		if (right == SPRE and (left == BE or left == UBOE) and ((up == BE and (upLeft == BE or upLeft == UBOE)) or (up == UBOE and upLeft == EMPTY)))
			return false;
	}

	if (val == BW)
	{
		if (left == BN and up == EMPTY and (upLeft == BN or upLeft == BW))
			return false;
		
		if (upLeft == EMPTY and up == BS and (left == BS or left == BW))
			return false;

		if (right == SPLW and (up == BW or (up == UBIW and upLeft == EMPTY)))
			return false;

				// and not (left == BN and up == BS and upLeft == UBIN and upUp == BS and d_matrix[pos - (2 * d_cols) - 1] == BE 
				// 	and (d_matrix[pos - (3 * d_cols) - 1] == UBON 
				// 		or (d_matrix[pos - (2 * d_cols) - 2] == BE and (d_matrix[pos - d_cols - 2] == EMPTY or d_matrix[pos - d_cols - 2] == BN))))
				// and not (left == BW and leftLeft == BN and up == BS and upLeft == UBON and upUp == BS and d_matrix[pos - (2 * d_cols) - 1] == BE);
	}

	if (val == BS)
	{
		if (left == BE and upLeft == BS and up == EMPTY)
			return false;

		if (down == SPLS and (up == BS or up == UBOS) and ((left == BS and (upLeft == BS or upLeft == UBOS)) or (left == UBOS and upLeft == EMPTY)))
			return false;

		// if (up == UBOS and up.ugS < d_underground_length - 1)
		// 	return false;
	}

	if (val == UBIN)
	{
		if (down == SPRN and up == EMPTY and ((left == UBIN and upLeft == EMPTY) or left == BN))
			return false;
	}

	// 	return up != EMPTY
	// 			and not (up == BE and upLeft == BE and upUp == UBON and d_matrix[pos - (2 * d_cols) - 1] == BS and d_matrix[pos - (3 * d_cols)] == BW and d_matrix[pos - (3 * d_cols) - 1] == BS)
	// 			and not (up == BW and upRight == BW and upUp == UBON and d_matrix[pos - (2 * d_cols) + 1] == BS and d_matrix[pos - (3 * d_cols)] == BE and d_matrix[pos - (3 * d_cols) + 1] == BS);

	// if (val == UBON)
	// 	return hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
	// 			and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) 
	// 			and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	// if (val == UBIE)
	// 	return hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up)
	// 			and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
	// 			and downLeft != SPLS and not requiresNorthInput(upLeft) and not requiresWestInput(leftLeft)
	// 			and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
	// 			and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBOE)
	{
		if (right == SPRE and left == EMPTY and ((up == UBOE and upLeft == EMPTY) or (up == BE and (upLeft == BE or upLeft == UBOE))))
			return false;
	}
	// 	return left != EMPTY;

	if (val == UBIW)
	{
		if (right == SPLW and left == EMPTY and ((up == UBIW and upLeft == EMPTY) or up == BW))
			return false;
	}
	// 	return left != EMPTY;

	// if (val == UBOW)
	// 	return hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft)
	// 			and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
	// 			and downLeft != SPRN
	// 			and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
	// 			and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	// if (val == UBIS)
	// 	return hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left)
	// 			and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp))
	// 			and not requiresWestInput(upLeft) and not requiresNorthInput(upUp) and not requiresEastInput(upRight)
	// 			and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
	// 			and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBOS)
	{
		if (down == SPLS and up == EMPTY and ((left == UBOS and upLeft == EMPTY) or (left == BS and (upLeft == BS or upLeft == UBOS))))
			return false;
	}
	// 	return up != EMPTY;



	
	if (val != EMPTY)
	{
		vector<Triple> path = getPathOfTile(pos, true, true);
		if (path.size() == 0)
			return false;

		if (not isCompletePath(path))
			return true;

		size_t pos2;
		vector<Triple> path2;

		if (isEntryPath(path))
		{
			pos2 = getIdxOfComplementarySplitterHalf(getIdx(path.back().x, path.back().y));
			path2 = getPathOfTile(pos2, false, true);
		}
		else
		{
			pos2 = getIdxOfComplementarySplitterHalf(getIdx(path.front().x, path.front().y));
			path2 = getPathOfTile(pos2, true, false);
		}

		if (isCompletePath(path2))
		{
			if (isEntryPath(path))
			{
				if (not isEntryPath(path2))
					return false;
			}
			else if (isExitPath(path))
			{
				if (not isExitPath(path2))
					return false;
			}
			else
				if (isEntryPath(path2) or isExitPath(path2))
					return false;


			Lane lane1 = Lane(d_matrix, getIdx(path.front().x, path.front().y), d_rows, d_cols, d_power, d_underground_length);
			Lane lane2 = Lane(d_matrix, getIdx(path2.front().x, path2.front().y), d_rows, d_cols, d_power, d_underground_length);

			// print2();

			if (not (lane1.valid(d_matrix) and lane2.valid(d_matrix)))
				return false;

			if (not sharedSplitters(lane1, lane2))
				return false;
		}



		// if (isExitPath(path))
		// {
		// 	size_t pos2 = getIdxOfComplementarySplitterHalf(getIdx(path.front().x, path.front().y));
		// 	vector<Triple> path2 = getPathOfTile(pos2, true, false);
		// 	if (not isExitPath(path2) and isCompletePath(path2))
		// 		return false;
		// }
		// else if (isEntryPath(path))
		// {
		// 	size_t pos2 = getIdxOfComplementarySplitterHalf(getIdx(path.back().x, path.back().y));
		// 	vector<Triple> path2 = getPathOfTile(pos2, false, true);
		// 	if (isCompletePath(path2))
		// 	{
		// 		if (not isEntryPath(path2))
		// 			return false;

		// 		Lane lane1 = Lane(d_matrix, getIdx(path.front().x, path.front().y), d_rows, d_cols, d_power, d_underground_length);
		// 		Lane lane2 = Lane(d_matrix, getIdx(path2.front().x, path2.front().y), d_rows, d_cols, d_power, d_underground_length);

		// 		// print2();

		// 		if (not (lane1.valid(d_matrix) and lane2.valid(d_matrix)))
		// 			return false;

		// 		if (not sharedSplitters(lane1, lane2))
		// 			return false;
		// 	}			
		// }
		// else
		// {
		// 	size_t pos2 = getIdxOfComplementarySplitterHalf(getIdx(path.front().x, path.front().y));
		// 	vector<Triple> path2 = getPathOfTile(pos2, true, false);
		// 	if (isCompletePath(path2))
		// 	{
		// 		if (isEntryPath(path2) or isExitPath(path2))
		// 			return false;
				
		// 		if (isSameSplitter(path.back(), path2.back()))
		// 			return false;
		// 	}
		// }

		
	}

	return true;

	// cerr << "Unexpected value: " << val.item + '0' - '0' << " at position: " << pos << endl;
	// return false;
}