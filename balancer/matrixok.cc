#include "balancer.ih"

bool Balancer::matrixOK(size_t pos)
{
	if (pos == 0)
		return true;

	char val = d_matrix[pos];
	char left = d_matrix[pos - 1];
	char up = BN;
	char upUp = BN;
	char upLeft = BN;
	char upRight = BN;
	char leftLeft = BN;
	char down = BN;
	char right = BN;

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

	if (pos < d_matrix.size() - d_cols)
		down = d_matrix[pos - d_cols];


	if (val == EMPTY)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up) 
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS or right == SPLE or right == SPRE or right == SPLW or right == SPRW);

	if (val == BN)
		return hasNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS) and not (right == SPLE or right == SPRE or right == SPLW)
				and not (down == SPLE and right == SPLN and not hasEastOutput(left)) and not (down == SPRW and right == SPRS and not hasEastOutput(left)); 

	if (val == BE)
		return not (hasEastOutput(left) and hasSouthOutput(up)) and not hasSouthOutput(upRight)
				and not (hasEastOutput(left) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (down == SPLN or down == SPRN))
				and not (down == SPLS or down == SPRS or down == SPLN) and not (right == SPLN or right == SPLW or right == SPRW or right == SPRS) //(isSplitter(right) and not (right == SPLE or right == SPRE))
				and not (down == SPLE and not hasEastOutput(left) and not hasSouthOutput(up)) and not (down == SPRW and not hasEastOutput(left) and not hasSouthOutput(up));

	if (val == BW)
		return hasWestInput(left) and not requiresNorthInput(up) and not hasSouthOutput(upLeft) and not hasEastOutput(leftLeft)
				and not (hasSouthOutput(up) and (down == SPLN or down == SPRN)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW)) and not ((down == SPLN or down == SPRN) and (right == SPLW or right == SPRW))
				and not (down == SPLS or down == SPRS or down == SPRN) and not (right == SPLE or right == SPRE)
				and not (down == SPLE and right == SPLN and not hasSouthOutput(up)) and not (down == SPRW and right == SPRS and not hasSouthOutput(up)); 

	if (val == BS)
		return not (hasEastOutput(left) and hasSouthOutput(up))
				and not (hasEastOutput(left) and (right == SPLW or right == SPRW)) and not (hasSouthOutput(up) and (right == SPLW or right == SPRW))
				and not (right == SPLE or right == SPRE or right == SPRW) and not (down == SPLN or down == SPRN or down == SPLE or down == SPRW) //(isSplitter(down) and not (down == SPLS or down == SPRS))
				and not (right == SPLN and not hasEastOutput(left) and not hasSouthOutput(up)) and not (right == SPRS and not hasEastOutput(left) and not hasSouthOutput(up));

	if (val == UBIN)
		return not requiresNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(left) and not hasSouthOutput(up)
				and not (down == SPLE or down == SPRW or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLN or down == SPRN))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	if (val == UBON)
		return hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	if (val == UBIE)
		return hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	if (val == UBOE)
		return not hasEastOutput(left) and not requiresWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasSouthOutput(upRight)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLN or right == SPRS or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLE or right == SPRE));

	if (val == UBIW)
		return not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLN or right == SPRS or right == SPLE or right == SPRE); //(isSplitter(right) and not (right == SPLW or right == SPRW));

	if (val == UBOW)
		return hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	if (val == UBIS)
		return hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left)
				and not (down == SPLN or down == SPRN or down == SPLS or down == SPRS) //(isSplitter(down) and not (down == SPLE or down == SPRW))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	if (val == UBOS)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up)
				and not (down == SPLE or down == SPRW or down == SPLN or down == SPRN) //(isSplitter(down) and not (down == SPLS or down == SPRS))
				and not (right == SPLE or right == SPRE or right == SPLW or right == SPRW); //(isSplitter(right) and not (right == SPLN or right == SPRS));

	cerr << "Unexpected value: " << val + '0' - '0' << " at position: " << pos << endl;
	return false;
}