#include "balancer.ih"

bool Balancer::existsShorterMiddlePath(vector<Tile> &matrix, Triple &goal, size_t maxLength, size_t length, size_t previousIdx, size_t idx)
{
	if (length >= maxLength)
		return false;

	if (matrix[previousIdx] == goal.tile and goal.x == getX(previousIdx) and goal.y == getY(previousIdx))
		return true;

	if (matrix[previousIdx] == UBIN)
	{
		if (matrix[idx + d_cols].ugN == d_underground_length - 1)
			return false;

		if (idx < 2 * d_cols)
			return false;

		matrix[idx].ugN = matrix[idx + d_cols].ugN + 1;

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBON;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx - d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx >= 3 * d_cols)
		{
			if (existsShorterMiddlePath(matrix, goal, maxLength, length, previousIdx, idx - d_cols))
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

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOE;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx + 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) + 2 < d_cols)
		{
			if (existsShorterMiddlePath(matrix, goal, maxLength, length, previousIdx, idx + 1))
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

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOW;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx - 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) > 1)
		{
			if (existsShorterMiddlePath(matrix, goal, maxLength, length, previousIdx, idx - 1))
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

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBOS;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx + d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx + 3 * d_cols >= matrix.size())
		{
			if (existsShorterMiddlePath(matrix, goal, maxLength, length, previousIdx, idx + d_cols))
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
		if (length < maxLength - 1)
		{
			if (hasNorthOutput(matrix[previousIdx]) and idx >= d_cols)
				if (matrix[idx + 1].item == SPRN or matrix[idx - 1].item == SPLN)
					return true;

			if (hasEastOutput(matrix[previousIdx]) and getX(idx + 1) > 0)
				if (matrix[idx - d_cols].item == SPLE or matrix[idx + d_cols].item == SPRE)
					return true;

			if (hasWestOutput(matrix[previousIdx]) and getX(idx) > 0)
				if (matrix[idx - d_cols].item == SPRW or matrix[idx + d_cols].item == SPLW)
					return true;

			if (hasSouthOutput(matrix[previousIdx]) and idx < matrix.size() - 2 * d_cols)
				if (matrix[idx + 1].item == SPLS or matrix[idx - 1].item == SPRS)
					return true;
		}
		
		if (not hasSouthOutput(matrix[previousIdx]) and idx >= 2 * d_cols)
		{
			matrix[idx].item = BN;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx - d_cols))
				return true;
		}

		if (not hasWestOutput(matrix[previousIdx]) and getX(idx + 1) > 0)
		{
			matrix[idx].item = BE;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx + 1))
				return true;
		}

		if (not hasEastOutput(matrix[previousIdx]) and getX(idx) > 0)
		{
			matrix[idx].item = BW;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx - 1))
				return true;
		}

		if (not hasNorthOutput(matrix[previousIdx]) and idx + 2 * d_cols < matrix.size())
		{
			matrix[idx].item = BS;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + 1, idx, idx + d_cols))
				return true;
		}

		if (hasNorthOutput(matrix[previousIdx]) and idx >= d_cols * 4)
		{
			matrix[idx].item = UBIN;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + d_underground_cost_penalty + 1, idx, idx - d_cols))
				return true;
		}

		if (hasEastOutput(matrix[previousIdx]) and getX(idx) + 3 < d_cols)
		{
			matrix[idx].item = UBIE;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + d_underground_cost_penalty + 1, idx, idx + 1))
				return true;
		}

		if (hasWestOutput(matrix[previousIdx]) and getX(idx) > 2)
		{
			matrix[idx].item = UBIW;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + d_underground_cost_penalty + 1, idx, idx + 1))
				return true;
		}

		if (hasSouthOutput(matrix[previousIdx]) and idx + 4 * d_cols < matrix.size())
		{
			matrix[idx].item = UBIS;
			if (existsShorterMiddlePath(matrix, goal, maxLength, length + d_underground_cost_penalty + 1, idx, idx + d_cols))
				return true;
		}

		matrix[idx].item = EMPTY;
	}

	return false;
}