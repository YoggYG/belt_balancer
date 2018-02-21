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

	if (val == EMPTY)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up);

	if (val == BN)
		return hasNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight);

	if (val == BE)
		return not (hasEastOutput(left) and hasSouthOutput(up)) and not hasSouthOutput(upRight);

	if (val == BW)
		return hasWestInput(left) and not requiresNorthInput(up) and not hasSouthOutput(upLeft) and not hasEastOutput(leftLeft);

	if (val == BS)
		return not (hasEastOutput(left) and hasSouthOutput(up));

	if (val == UBIN)
		return not requiresNorthInput(up) and not requiresWestInput(left) and not hasEastOutput(left) and not hasSouthOutput(up);

	if (val == UBON)
		return hasNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left) and not hasEastOutput(upLeft) and not hasSouthOutput(upUp) and not hasWestOutput(upRight);

	if (val == UBIE)
		return hasEastOutput(left) and not requiresNorthInput(up) and not hasSouthOutput(up);

	if (val == UBOE)
		return not hasEastOutput(left) and not requiresWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasSouthOutput(upRight);

	if (val == UBIW)
		return not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(left) and not requiresWestInput(left); // maybe same as UBIN

	if (val == UBOW)
		return hasWestInput(left) and not hasSouthOutput(up) and not requiresNorthInput(up) and not hasEastOutput(leftLeft) and not hasSouthOutput(upLeft);

	if (val == UBIS)
		return hasSouthOutput(up) and not hasEastOutput(left) and not requiresWestInput(left);

	if (val == UBOS)
		return not hasEastOutput(left) and not hasSouthOutput(up) and not requiresWestInput(left) and not requiresNorthInput(up);


}