#include "balancer.ih"

bool Balancer::matrixOptimised(size_t pos)
{
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

	if (pos + 1 == 2 * d_cols)
	{
		bool onlyNorthBelts = true;
		for (size_t idx = d_cols; idx < 2 * d_cols; ++idx)
			if (d_matrix[idx] != EMPTY and d_matrix[idx] != BN)
			{
				onlyNorthBelts = false;
				break;
			}
		
		if (onlyNorthBelts)
			return false;
	}

	if (pos > d_cols and pos < d_matrix.size() - d_cols and (pos + 1) % d_cols == 0)
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
	
	if (val != EMPTY)
	{
		vector<Triple> path = getPathOfTile(pos);
		if (path.size() == 0)
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

	if (val == EMPTY)
		return not (up == UBON or up == UBIS or left == UBIE or left == UBOW)
				and not (up == BE and upLeft == BE and upUp == UBON and d_matrix[pos - (2 * d_cols) - 1] == BS and d_matrix[pos - 3 * d_cols] == BW and d_matrix[pos - (3 * d_cols) - 1] == BS)
				and not (up == BW and upRight == BW and upUp == UBON and d_matrix[pos - (2 * d_cols) + 1] == BS and d_matrix[pos - 3 * d_cols] == BE and d_matrix[pos - (3 * d_cols) + 1] == BS)
				and not (up == BW and upLeft == BS and left != SPLS and upUp == BS and d_matrix[pos - 2 * d_cols - 1] == UBON and d_matrix[pos - 3 * d_cols] == BS and d_matrix[pos - 3 * d_cols - 1] == BE)
				and not (up == BE and upRight == BS and right != SPRS and upUp == BS and d_matrix[pos - 2 * d_cols + 1] == UBON and d_matrix[pos - 3 * d_cols] == BS and d_matrix[pos - 3 * d_cols + 1] == BW);

	if (val == BN)
		return not (left == BE and upLeft == EMPTY and (up == BN or up == BE))
				and not (left == BE and up == UBIN and upLeft == BS and upUp == BW and d_matrix[pos - (2 * d_cols) - 1] == BS 
					and (d_matrix[pos - (3 * d_cols)] == UBON 
						or (d_matrix[pos - (2 * d_cols) + 1] == BW and (upRight == EMPTY or upRight == BN))))
				and not (left == BE and leftLeft == BE and upLeft == UBON and d_matrix[pos - d_cols - 2] == BS and d_matrix[pos - (2 * d_cols) - 1] == BW and d_matrix[pos - (2 * d_cols) - 2] == BS);

	if (val == BE)
		return not (left == BE and upLeft == BS and up == EMPTY);

	if (val == BW)
		return not (left == BN and up == EMPTY and (upLeft == BN or upLeft == BW))
				and not (upLeft == EMPTY and up == BS and (left == BS or left == BW))
				and not (left == BN and up == BS and upLeft == UBIN and upUp == BS and d_matrix[pos - (2 * d_cols) - 1] == BE 
					and (d_matrix[pos - (3 * d_cols) - 1] == UBON 
						or (d_matrix[pos - (2 * d_cols) - 2] == BE and (d_matrix[pos - d_cols - 2] == EMPTY or d_matrix[pos - d_cols - 2] == BN))))
				and not (left == BW and leftLeft == BN and up == BS and upLeft == UBON and upUp == BS and d_matrix[pos - (2 * d_cols) - 1] == BE);

	if (val == BS)
		return not (left == BE and upLeft == BS and up == EMPTY);

	if (val == UBIN)
		return up != EMPTY
				and not (up == BE and upLeft == BE and upUp == UBON and d_matrix[pos - (2 * d_cols) - 1] == BS and d_matrix[pos - (3 * d_cols)] == BW and d_matrix[pos - (3 * d_cols) - 1] == BS)
				and not (up == BW and upRight == BW and upUp == UBON and d_matrix[pos - (2 * d_cols) + 1] == BS and d_matrix[pos - (3 * d_cols)] == BE and d_matrix[pos - (3 * d_cols) + 1] == BS);

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
		return left != EMPTY;

	if (val == UBIW)
		return left != EMPTY;

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
		return up != EMPTY;

	return true;

	// cerr << "Unexpected value: " << val.item + '0' - '0' << " at position: " << pos << endl;
	// return false;
}