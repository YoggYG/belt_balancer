#include "balancer.ih"

bool Balancer::matrixOK(size_t pos)
{
	//cerr << pos << endl;
	size_t val = d_matrix[pos].item;
	size_t left = EMPTY;
	size_t up = BN;
	size_t upUp = EMPTY;
	size_t upLeft = EMPTY;
	size_t upRight = EMPTY;
	size_t leftLeft = EMPTY;
	size_t down = EMPTY;
	size_t right = EMPTY;
	size_t downRight = EMPTY;
	size_t downLeft = EMPTY;
	size_t downDown = EMPTY;
	size_t rightRight = EMPTY;

	if (pos >= 2 * d_cols)
	{
		upUp = d_matrix[pos - 2 * d_cols].item;
		upLeft = d_matrix[pos - d_cols - 1].item;
		up = d_matrix[pos - d_cols].item;
		upRight = d_matrix[pos - d_cols + 1].item;
		leftLeft = d_matrix[pos - 2].item;
		left = d_matrix[pos - 1].item;
	}
	else if (pos > d_cols)
	{
		upLeft = d_matrix[pos - d_cols - 1].item;
		up = d_matrix[pos - d_cols].item;
		upRight = d_matrix[pos - d_cols + 1].item;
		leftLeft = d_matrix[pos - 2].item;
		left = d_matrix[pos - 1].item;
	}
	else if (pos == d_cols)
	{
		up = d_matrix[pos - d_cols].item;
		upRight = d_matrix[pos - d_cols + 1].item;
		leftLeft = d_matrix[pos - 2].item;
		left = d_matrix[pos - 1].item;
	}
	else if (pos > 1)
	{
		if (pos == d_cols - 1 and numberOfOutputBelts() != d_n)
			return false;
		
		leftLeft = d_matrix[pos - 2].item;
		left = d_matrix[pos - 1].item;
	}	
	else if (pos == 1)
	{
		left = d_matrix[pos - 1].item;
	}

	if (pos < d_matrix.size() - 2 * d_cols)
	{
		right = d_matrix[pos + 1].item;
		rightRight = d_matrix[pos + 2].item;
		downLeft = d_matrix[pos + d_cols - 1].item;
		down = d_matrix[pos + d_cols].item;
		downRight = d_matrix[pos + d_cols + 1].item;
		downDown = d_matrix[pos + 2 * d_cols].item;
	}
	else if (pos < d_matrix.size() - d_cols - 1)
	{
		right = d_matrix[pos + 1].item;
		rightRight = d_matrix[pos + 2].item;
		downLeft = d_matrix[pos + d_cols - 1].item;
		down = d_matrix[pos + d_cols].item;
		downRight = d_matrix[pos + d_cols + 1].item;
	}	
	else if (pos == d_matrix.size() - d_cols - 1)
	{
		right = d_matrix[pos + 1].item;
		rightRight = d_matrix[pos + 2].item;
		downLeft = d_matrix[pos + d_cols - 1].item;
		down = d_matrix[pos + d_cols].item;
	}
	else if (pos < d_matrix.size() - 2)
	{		
		right = d_matrix[pos + 1].item;
		rightRight = d_matrix[pos + 2].item;
	}
	else if (pos == d_matrix.size() - 2)
	{
		right = d_matrix[pos + 1].item;
	}
	else if (numberOfInputBelts() != d_n)
		return false;


	if (val == EMPTY)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up) 
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY or pos < d_cols)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS or right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and verticalUndergroundOK(pos) and horizontalUndergroundOK(pos);

	if (val == BN)
		return hasNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS) and not (right == SPLE or right == SPRE or right == SPLW)
				and not (down == SPLE and right == SPLN and not hasEastOutput(left)) and not (down == SPRW and right == SPRS and not hasEastOutput(left))
				and verticalUndergroundOK(pos) and horizontalUndergroundOK(pos); 

	if (val == BE)
		return (pos + 1) % d_cols != 0
				and not (hasEastOutput(left) and hasSouthOutput(up)) and not hasSouthOutput(upRight)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (down == SPLN or down == SPRN))
				and not (down == SPLS or down == SPRS) and not (right == SPLN or right == SPLW or right == SPRW or right == SPRS)
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLE and not hasEastOutput(left) and not hasSouthOutput(up)) and not (down == SPRW and not hasEastOutput(left) and not hasSouthOutput(up))
				and verticalUndergroundOK(pos) and horizontalUndergroundOK(pos);

	if (val == BW)
		return pos % d_cols != 0
				and hasWestInput(left) and not requiresNorthInput(up) and not hasSouthOutput(upLeft) and not hasEastOutput(leftLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasSouthOutput(up) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS)and not (right == SPLE or right == SPRE) and not (downLeft == SPLN or downLeft == SPRN) 
				and not (down == SPLE and right == SPLN and not hasSouthOutput(up)) and not (down == SPRW and right == SPRS and not hasSouthOutput(up))
				and verticalUndergroundOK(pos) and horizontalUndergroundOK(pos); 

	if (val == BS)
		return pos < d_matrix.size() - 2 * d_cols
				and not (hasEastOutput(left) and hasSouthOutput(up))
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW))
				and not (right == SPLE or right == SPRE) and not (down == SPLN or down == SPRN or down == SPLE or down == SPRW)
				and not (downRight == SPLW or downRight == SPRW) and not (downDown == SPLN or downDown == SPRN)
				and not (right == SPLN and not hasEastOutput(left) and not hasSouthOutput(up)) and not (right == SPRS and not hasEastOutput(left) and not hasSouthOutput(up))
				and verticalUndergroundOK(pos) and horizontalUndergroundOK(pos);

	if (val == UBIN)
		return pos >= 3 * d_cols
				and not requiresNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(left) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == EMPTY)
				and not (up == UBON or up == UBIS) and hasNorthUndergroundOutput(pos)
				and not (downLeft == SPLW or downLeft == SPRW) and not (downDown == SPLS or downDown == SPRS) and not (downRight == SPLE or downRight == SPRE)
				and not (down == SPLE or down == SPRW or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and horizontalUndergroundOK(pos) and d_matrix[pos].ugS == 0 and d_matrix[pos].ugN > 1;

	if (val == UBON)
		return pos + 4 * d_cols < d_matrix.size()
				and hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) 
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and horizontalUndergroundOK(pos) and d_matrix[pos].ugS == 0;

	if (val == UBIE)
		return (pos + 3) % d_cols > 3
				and hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and downLeft != SPLS and not requiresNorthInput(upLeft) and not requiresWestInput(leftLeft)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and verticalUndergroundOK(pos) and d_matrix[pos].ugW == 0;

	if (val == UBOE)
		return (pos + 1) % d_cols > 3
				and not hasEastOutput(left) and not requiresWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasSouthOutput(upRight)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (left == UBIE or left == UBOW) and hasEastUndergroundInput(pos)
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLW or right == SPRW)
				and verticalUndergroundOK(pos) and d_matrix[pos].ugW == 0 and d_matrix[pos].ugE > 1;

	if (val == UBIW)
		return (pos + 1) % d_cols > 3
				and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (left == UBOW or left == UBIE) and hasWestUndergroundOutput(pos)
				and downRight != SPRS and not (rightRight == SPLE or rightRight == SPRE) and not requiresNorthInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLE or right == SPRE)
				and verticalUndergroundOK(pos) and d_matrix[pos].ugE == 0 and d_matrix[pos].ugW > 1;

	if (val == UBOW)
		return (pos + 3) % d_cols > 3
				and hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and downLeft != SPRN
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and verticalUndergroundOK(pos) and d_matrix[pos].ugE == 0;

	if (val == UBIS)
		return pos + 5 * d_cols < d_matrix.size() and pos >= 2 * d_cols
				and hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp))
				and not requiresWestInput(upLeft) and not requiresNorthInput(upUp) and not requiresEastInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and horizontalUndergroundOK(pos) and d_matrix[pos].ugN == 0;

	if (val == UBOS)
		return pos + 3 * d_cols < d_matrix.size() and pos >= 4 * d_cols
				and not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == EMPTY)
				and not (up == UBIS or up == UBON) and hasSouthUndergroundInput(pos)
				and not (downLeft == SPLE or downLeft == SPRE) and not (downDown == SPLN or downDown == SPRN) and not (downRight == SPLW or downRight == SPRW)
				and not (down == SPLE or down == SPRW or down == SPLN or down == SPRN)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				and horizontalUndergroundOK(pos) and d_matrix[pos].ugN == 0 and d_matrix[pos].ugS > 1;

	cerr << "Unexpected value: " << val + '0' - '0' << " at position: " << pos << endl;
	return false;
}