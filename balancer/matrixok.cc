#include "balancer.ih"

bool Balancer::matrixOK(size_t pos)
{
	//cerr << pos << endl;
	char val = d_matrix[pos];
	char left = EMPTY;
	char up = BN;
	char upUp = EMPTY;
	char upLeft = EMPTY;
	char upRight = EMPTY;
	char leftLeft = EMPTY;
	char down = EMPTY;
	char right = EMPTY;
	char downRight = EMPTY;
	char downLeft = EMPTY;
	char downDown = EMPTY;
	char rightRight = EMPTY;

	if (pos > 0)
		left = d_matrix[pos - 1];

	if (pos > 1)
		leftLeft = d_matrix[pos - 2];

	if (pos > d_cols)
		upLeft = d_matrix[pos - d_cols - 1];
	
	if (pos >= d_cols)
	{
		up = d_matrix[pos - d_cols];
		upRight = d_matrix[pos - d_cols + 1];
	}
	
	if (pos >= 2 * d_cols)
		upUp = d_matrix[pos - 2 * d_cols];

	if (pos < d_matrix.size() - 1)
		right = d_matrix[pos + 1];

	if (pos < d_matrix.size() - 2)
		rightRight = d_matrix[pos + 2];

	if (pos < d_matrix.size() - d_cols)
	{
		down = d_matrix[pos + d_cols];
		downLeft = d_matrix[pos + d_cols - 1];
	}
	else if (numberOfInputBelts() > d_n)
		return false;

	if (pos < d_matrix.size() - d_cols - 1)
		downRight = d_matrix[pos + d_cols + 1];

	if (pos < d_matrix.size() - 2 * d_cols)
		downDown = d_matrix[pos + 2 * d_cols];

	if (val == EMPTY)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up) 
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY or pos < d_cols)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS or right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == BN)
		return hasNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS) and not (right == SPLE or right == SPRE or right == SPLW)
				and not (down == SPLE and right == SPLN and not hasEastOutput(left)) and not (down == SPRW and right == SPRS and not hasEastOutput(left)); 

	if (val == BE)
		return not (hasEastOutput(left) and hasSouthOutput(up)) and not hasSouthOutput(upRight)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (down == SPLN or down == SPRN))
				and not (down == SPLS or down == SPRS) and not (right == SPLN or right == SPLW or right == SPRW or right == SPRS)
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLE and not hasEastOutput(left) and not hasSouthOutput(up)) and not (down == SPRW and not hasEastOutput(left) and not hasSouthOutput(up));

	if (val == BW)
		return hasWestInput(left) and not requiresNorthInput(up) and not hasSouthOutput(upLeft) and not hasEastOutput(leftLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasSouthOutput(up) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS)and not (right == SPLE or right == SPRE) and not (downLeft == SPLN or downLeft == SPRN) 
				and not (down == SPLE and right == SPLN and not hasSouthOutput(up)) and not (down == SPRW and right == SPRS and not hasSouthOutput(up)); 

	if (val == BS)
		return not (hasEastOutput(left) and hasSouthOutput(up))
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW))
				and not (right == SPLE or right == SPRE) and not (down == SPLN or down == SPRN or down == SPLE or down == SPRW)
				and not (downRight == SPLW or downRight == SPRW) and not (downDown == SPLN or downDown == SPRN)
				and not (right == SPLN and not hasEastOutput(left) and not hasSouthOutput(up)) and not (right == SPRS and not hasEastOutput(left) and not hasSouthOutput(up));

	if (val == UBIN)
		return not requiresNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(left) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == EMPTY)
				and not (up == UBON or up == UBIS) and hasNorthUndergroundOutput(pos)
				and not (downLeft == SPLW or downLeft == SPRW) and not (downDown == SPLS or downDown == SPRS) and not (downRight == SPLE or downRight == SPRE)
				and not (down == SPLE or down == SPRW or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBON)
		return hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) 
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBIE)
		return hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and downLeft != SPLS and not requiresNorthInput(upLeft) and not requiresWestInput(leftLeft)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBOE)
		return not hasEastOutput(left) and not requiresWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasSouthOutput(upRight)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (left == UBIE or left == UBOW) and hasEastUndergroundInput(pos)
				and not (downRight == SPLN or downRight == SPRN) and not (rightRight == SPLW or rightRight == SPRW)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLW or right == SPRW);

	if (val == UBIW)
		return not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and not (left == UBOW or left == UBIE) and hasWestUndergroundOutput(pos)
				and downRight != SPRS and not (rightRight == SPLE or rightRight == SPRE) and not requiresNorthInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLN or right == SPRS or right == SPLE or right == SPRE);

	if (val == UBOW)
		return hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == UBON or up == EMPTY)
				and downLeft != SPRN
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBIS)
		return hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp))
				and not requiresWestInput(upLeft) and not requiresNorthInput(upUp) and not requiresEastInput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == UBOS)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up)
				and (hasEastOutput(upLeft) or hasWestOutput(upRight) or hasSouthOutput(upUp) or up == EMPTY)
				and not (up == UBIS or up == UBON) and hasSouthUndergroundInput(pos)
				and not (downLeft == SPLE or downLeft == SPRE) and not (downDown == SPLN or downDown == SPRN) and not (downRight == SPLW or downRight == SPRW)
				and not (down == SPLE or down == SPRW or down == SPLN or down == SPRN)
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	cerr << "Unexpected value: " << val + '0' - '0' << " at position: " << pos << endl;
	return false;
}