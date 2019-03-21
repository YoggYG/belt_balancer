#include "balancer.ih"

bool Balancer::existsShorterEntryPath(vector<Tile> &matrix, size_t maxLength, size_t length, size_t previousIdx, size_t idx)
{
	if (length >= maxLength)
		return false;

	if (previousIdx >= matrix.size() - d_cols and matrix[previousIdx] == BN)
		return true;

	if (matrix[previousIdx] == UBON)
	{
		if (matrix[idx - d_cols].ugN == d_underground_length - 1)
			return false;

		if (idx + d_cols >= matrix.size())
			return false;

		matrix[idx].ugN = matrix[idx - d_cols].ugN + 1;

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBIN;
			if (existsShorterEntryPath(matrix, maxLength, length + d_underground_cost_penalty + 1, idx, idx + d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx + 2 * d_cols < matrix.size())
		{
			if (existsShorterEntryPath(matrix, maxLength, length, previousIdx, idx + d_cols))
				return true;
		}
		
		matrix[idx].ugN = 0;
	}
	else if (matrix[previousIdx] == UBOE)
	{
		if (matrix[idx + 1].ugE == d_underground_length - 1)
			return false;

		if (getX(idx) == 0)
			return false;

		matrix[idx].ugE = matrix[idx + 1].ugE + 1;

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBIE;
			if (existsShorterEntryPath(matrix, maxLength, length + d_underground_cost_penalty + 1, idx, idx - 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) > 1)
		{
			if (existsShorterEntryPath(matrix, maxLength, length, previousIdx, idx - 1))
				return true;
		}
		
		matrix[idx].ugE = 0;
	}
	else if (matrix[previousIdx] == UBOW)
	{
		if (matrix[idx - 1].ugW == d_underground_length - 1)
			return false;

		if (getX(idx + 1) == 0)
			return false;

		matrix[idx].ugW = matrix[idx - 1].ugW + 1;

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBIW;
			if (existsShorterEntryPath(matrix, maxLength, length + d_underground_cost_penalty + 1, idx, idx + 1))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (getX(idx) + 2 < d_cols)
		{
			if (existsShorterEntryPath(matrix, maxLength, length, previousIdx, idx + 1))
				return true;
		}
		
		matrix[idx].ugW = 0;
	}
	else if (matrix[previousIdx] == UBOS)
	{
		if (matrix[idx + d_cols].ugS == d_underground_length - 1)
			return false;

		if (idx < 2 * d_cols)
			return false;

		matrix[idx].ugS = matrix[idx + d_cols].ugS + 1;

		if (matrix[idx].item == EMPTY)
		{
			matrix[idx].item = UBIS;
			if (existsShorterEntryPath(matrix, maxLength, length + d_underground_cost_penalty + 1, idx, idx - d_cols))
				return true;
			
			matrix[idx].item = EMPTY;
		}

		if (idx >= 3 * d_cols)
		{
			if (existsShorterEntryPath(matrix, maxLength, length, previousIdx, idx - d_cols))
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
		if (previousIdx + d_cols == idx)
		{
			matrix[idx].item = BN;
			if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + d_cols))
				return true;

			if (getX(idx + 1) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + 1))
				return true;

			if (getX(idx) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - 1))
				return true;

			if (idx < matrix.size() - 3 * d_cols)
			{
				matrix[idx].item = UBON;
				if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + d_cols))
					return true;
			}
		}
		else if (previousIdx == idx + 1)
		{
			matrix[idx].item = BE;
			if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + d_cols))
				return true;

			if (getX(idx) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - 1))
				return true;

			if (idx >= d_cols and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - d_cols))
				return true;

			if (getX(idx) > 2)
			{
				matrix[idx].item = UBOE;
				if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - 1))
					return true;
			}
		}
		else if (previousIdx + 1 == idx)
		{
			matrix[idx].item = BW;
			if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + d_cols))
				return true;

			if (getX(idx + 1) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + 1))
				return true;

			if (idx >= d_cols and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - d_cols))
				return true;

			if (getX(idx) + 3 < d_cols)
			{
				matrix[idx].item = UBOW;
				if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + 1))
					return true;
			}
		}
		else if (previousIdx == idx + d_cols)
		{
			matrix[idx].item = BS;
			if (getX(idx) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - 1))
				return true;

			if (getX(idx + 1) > 0 and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx + 1))
				return true;

			if (idx >= d_cols and existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - d_cols))
				return true;

			if (idx >= d_cols * 3)
			{
				matrix[idx].item = UBOS;
				if (existsShorterEntryPath(matrix, maxLength, length + 1, idx, idx - d_cols))
					return true;
			}
		}

		matrix[idx].item = EMPTY;
	}

	return false;
}