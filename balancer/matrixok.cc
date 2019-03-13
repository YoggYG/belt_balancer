#include "balancer.ih"

bool Balancer::matrixOK(size_t pos)
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
		if (pos == d_cols - 1 and numberOfOutputBelts() != d_n)
			return false;
		
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
	else if (numberOfInputBelts() != d_n)
		return false;

	if (val.ugN >= d_underground_length or val.ugE >= d_underground_length or val.ugW >= d_underground_length or val.ugS >= d_underground_length)
		return false;

	if ((pos + 1) % d_cols == 0 and (val.ugE > 0 or val.ugW > 0))
		return false;


	if (val == EMPTY)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up) 
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == EMPTY or pos < d_cols) // ensure 'up' does have an input
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS or right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == BN)
		return hasNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPLN or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS) and not (right == SPLE or right == SPRE or right == SPLW)
				and not (down == SPLE and right == SPLN and not hasEastOutput(left)) and not (down == SPRW and right == SPRS and not hasEastOutput(left))
				and not hasLoop(val, up, upLeft, left); 

	if (val == BE)
		return not (hasEastOutput(left) and hasSouthOutput(up)) and not hasSouthOutput(upRight) and not requiresWestInput(left) and not requiresNorthInput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == UBOS or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPLN or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (down == SPLN or down == SPRN))
				and not (down == SPLS or down == SPRS) and not (right == SPLN or right == SPLW or right == SPRW or right == SPRS)
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLE and not hasEastOutput(left) and not hasSouthOutput(up)) and not (down == SPRW and not hasEastOutput(left) and not hasSouthOutput(up))
				and not hasLoop(val, up, upLeft, left);

	if (val == BW)
		return hasWestInput(left) and not requiresNorthInput(up) and not hasSouthOutput(upLeft) and not hasEastOutput(leftLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == UBOS or up == EMPTY)
				and not (hasSouthOutput(up) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS)and not (right == SPLE or right == SPRE) and not (downLeft == SPLN or downLeft == SPRN) 
				and not (down == SPLE and right == SPLN and not hasSouthOutput(up)) and not (down == SPRW and right == SPRS and not hasSouthOutput(up))
				and not hasLoop(val, up, upLeft, left); 

	if (val == BS)
		return not (hasEastOutput(left) and hasSouthOutput(up)) and not requiresWestInput(left) and not requiresNorthInput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == UBOS or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not ((pos + 1) % d_cols == 0 and not hasSouthOutput(up) and not hasEastOutput(left))
				and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW))
				and not (right == SPLE or right == SPRE) and not (down == SPLN or down == SPRN or down == SPLE or down == SPRW)
				and not (downRight == SPLW or downRight == SPRW) and not (downDown == SPLN or downDown == SPRN)
				and not (right == SPLN and not hasEastOutput(left) and not hasSouthOutput(up)) and not (right == SPRS and not hasEastOutput(left) and not hasSouthOutput(up))
				and not hasLoop(val, up, upLeft, left);

	if (val == UBIN)
		return not requiresNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(left) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBOE or up == UBOW or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPLN or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				// and not (up == UBON or up == UBIS) and hasNorthUndergroundOutput(pos)
				and val.ugN > 1
				and not (downLeft == SPLW or downLeft == SPRW) and not (downDown == SPLS or downDown == SPRS) and not (downRight == SPLE or downRight == SPRE)
				and not (down == SPLE or down == SPRW or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBON)
		return hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) 
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				// and not hasVerticalUndergroundPath(pos)
				and val.ugN == 0 and val.ugS == 0
				;

	if (val == UBIE)
		return hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN) // ensure 'left' does have an input
				and downLeft != SPLS and not requiresNorthInput(upLeft) and not requiresWestInput(leftLeft)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				// and not hasHorizontalUndergroundPath(pos);
				and val.ugE == 0 and val.ugW == 0;

	if (val == UBOE)
		return not hasEastOutput(left) and not requiresWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasSouthOutput(upRight)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOS or left == EMPTY) // ensure 'left' does have an input
				// and not (left == UBIE or left == UBOW) and hasEastUndergroundInput(pos)
				and val.ugE > 1
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLW or right == SPRW);

	if (val == UBIW)
		return not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOS or left == EMPTY) // ensure 'left' does have an input
				// and not (left == UBOW or left == UBIE) and hasWestUndergroundOutput(pos)
				and val.ugW > 1
				and downRight != SPRS and not (rightRight == SPLE or rightRight == SPRE) and not requiresNorthInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLE or right == SPRE);

	if (val == UBOW)
		return hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == UBOE or up == UBOW or up == EMPTY)
				and downLeft != SPRN
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				// and not hasHorizontalUndergroundPath(pos);
				and val.ugE == 0 and val.ugW == 0;

	if (val == UBIS)
		return hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBOS)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				and not requiresWestInput(upLeft) and not requiresNorthInput(upUp) and not requiresEastInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW)
				// and not hasVerticalUndergroundPath(pos)
				and val.ugN == 0 and val.ugS == 0;

	if (val == UBOS)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBOE or up == UBOW or up == EMPTY)
				and (hasEastOutput(leftLeft) or hasSouthOutput(upLeft) or downLeft == EMPTY or downLeft == SPRN or left == UBON or left == UBOE or left == UBOW or left == UBOS or left == EMPTY or pos % d_cols == 0) // ensure 'left' does have an input
				// and not (up == UBIS or up == UBON) and hasSouthUndergroundInput(pos)
				and val.ugS > 1
				and not (downLeft == SPLE or downLeft == SPRE) and not (downDown == SPLN or downDown == SPRN) and not (downRight == SPLW or downRight == SPRW)
				and not (down == SPLE or down == SPRW or down == SPLN or down == SPRN)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	cerr << "Unexpected value: " << val.item + '0' - '0' << " at position: " << pos << endl;
	return false;
}