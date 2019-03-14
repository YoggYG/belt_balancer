#include "balancer.ih"

bool Balancer::existsShorterExitPath(vector<Tile> &matrix, size_t maxLength, size_t length, size_t previousIdx, size_t idx)
{
	if (previousIdx < d_cols and matrix[previousIdx] == BN)
		return true;

	if (length == maxLength)
		return false;

	if (matrix[previousIdx] == UBIN)
	{
		if (matrix[idx + d_cols].ugN == d_underground_length - 1)
			return false;

		if (idx < d_cols)
			return false;

		matrix[idx].ugN = matrix[idx + d_cols].ugN + 1;

		if (matrix[idx + d_cols].item != EMPTY and matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBON;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx - d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx >= 2 * d_cols)
		{
			if (existsShorterExitPath(matrix, maxLength, length + 1, previousIdx, idx - d_cols))
				return true;
		}
		
		matrix[idx].ugN = 0;
	}
	else if (matrix[previousIdx] == UBIE)
	{
		if (matrix[idx - 1].ugE == d_underground_length - 1)
			return false;

		if (getX(idx + 1) == 0)
			return false;

		matrix[idx].ugE = matrix[idx - 1].ugE + 1;

		if (matrix[idx - 1].item != EMPTY and matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOE;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx + 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) + 2 < d_cols)
		{
			if (existsShorterExitPath(matrix, maxLength, length + 1, previousIdx, idx + 1))
				return true;
		}
		
		matrix[idx].ugE = 0;
	}
	else if (matrix[previousIdx] == UBIW)
	{
		if (matrix[idx + 1].ugW == d_underground_length - 1)
			return false;

		if (getX(idx) == 0)
			return false;

		matrix[idx].ugW = matrix[idx + 1].ugW + 1;

		if (matrix[idx + 1].item != EMPTY and matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOW;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx - 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) > 1)
		{
			if (existsShorterExitPath(matrix, maxLength, length + 1, previousIdx, idx - 1))
				return true;
		}
		
		matrix[idx].ugW = 0;
	}
	else if (matrix[previousIdx] == UBIS)
	{
		if (matrix[idx - d_cols].ugS == d_underground_length - 1)
			return false;

		if (idx + 2 * d_cols >= matrix.size())
			return false;

		matrix[idx].ugS = matrix[idx - d_cols].ugS + 1;

		if (matrix[idx - d_cols].item != EMPTY and matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOS;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx + d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx + 3 * d_cols >= matrix.size())
		{
			if (existsShorterExitPath(matrix, maxLength, length + 1, previousIdx, idx + d_cols))
				return true;
		}
		
		matrix[idx].ugS = 0;
	}
	else if (matrix[previousIdx] == EMPTY)
	{
		cerr << "error in findexitpath, empty item.\n";
	}
	else if (matrix[idx] == EMPTY)
	{
		if (not hasSouthOutput(matrix[previousIdx]))
		{
			matrix[idx].item = BN;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx - d_cols))
				return true;
		}

		if (not hasWestOutput(matrix[previousIdx]) and getX(idx + 1) > 0 and idx >= d_cols)
		{
			matrix[idx].item = BE;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx + 1))
				return true;
		}

		if (not hasEastOutput(matrix[previousIdx]) and getX(idx) > 0 and idx >= d_cols)
		{
			matrix[idx].item = BW;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx - 1))
				return true;
		}

		if (not hasNorthOutput(matrix[previousIdx]) and idx + 2 * d_cols < matrix.size())
		{
			matrix[idx].item = BS;
			if (existsShorterExitPath(matrix, maxLength, length + 1, idx, idx + d_cols))
				return true;
		}

		if (hasNorthOutput(matrix[previousIdx]) and idx >= d_cols * 3 and matrix[idx - d_cols].item != EMPTY)
		{
			matrix[idx].item = UBIN;
			if (existsShorterExitPath(matrix, maxLength, length + 2, idx, idx - d_cols))
				return true;
		}

		if (hasEastOutput(matrix[previousIdx]) and getX(idx) + 3 < d_cols and matrix[idx + 1].item != EMPTY)
		{
			matrix[idx].item = UBIE;
			if (existsShorterExitPath(matrix, maxLength, length + 2, idx, idx + 1))
				return true;
		}

		if (hasWestOutput(matrix[previousIdx]) and getX(idx) > 2 and matrix[idx - 1].item != EMPTY)
		{
			matrix[idx].item = UBIW;
			if (existsShorterExitPath(matrix, maxLength, length + 2, idx, idx + 1))
				return true;
		}

		if (hasSouthOutput(matrix[previousIdx]) and idx + 4 * d_cols < matrix.size() and matrix[idx + d_cols].item != EMPTY)
		{
			matrix[idx].item = UBIS;
			if (existsShorterExitPath(matrix, maxLength, length + 2, idx, idx + d_cols))
				return true;
		}

		matrix[idx].item = EMPTY;
	}

	return false;

}