#include "balancer.ih"

bool Balancer::incrMatrixUntilOK(size_t pos)
{
	// cin.get();
	// print();
	if (d_matrix[0].item > 1)
		return false;

	size_t maxVal = MAXVAL;
	if (pos < d_cols or pos >= (d_rows - 1) * d_cols)
		maxVal = 2;

	while (d_matrix[pos].item < maxVal and not matrixOK(pos))
		++d_matrix[pos].item;

	if (d_matrix[pos].item == maxVal and pos > 0)
	{
		d_matrix[pos].item = EMPTY;

		if (not verticalUndergroundOK(pos))
		{
			size_t originalPos = pos;
			do
				pos -= d_cols;
			while (isSplitter(d_matrix[pos].item));
			for (size_t idx = pos + 1; idx < originalPos; ++idx)
				if (not isSplitter(d_matrix[idx].item))
					d_matrix[idx].item = EMPTY;
		}
		else
			do
				--pos;
			while (isSplitter(d_matrix[pos].item));

		++d_matrix[pos].item;

		return incrMatrixUntilOK(pos);
	}

	if (d_matrix[pos].item > maxVal and not verticalUndergroundOK(pos))
	{
		size_t originalPos = pos;
		do
			pos -= d_cols;
		while (isSplitter(d_matrix[pos].item));
		for (size_t idx = pos + 1; idx < originalPos; ++idx)
			if (not isSplitter(d_matrix[idx].item))
				d_matrix[idx].item = EMPTY;

		++d_matrix[pos].item;

		return incrMatrixUntilOK(pos);
	}

	if (d_matrix[pos].item > maxVal and not horizontalUndergroundOK(pos))
	{
		do
			--pos;
		while (isSplitter(d_matrix[pos].item));

		++d_matrix[pos].item;

		return incrMatrixUntilOK(pos);
	}

	if (maxVal == MAXVAL)
	{
		if ((d_matrix[pos].ugN and d_matrix[pos].item != UBIN) or d_matrix[pos].item == UBON)
			d_matrix[pos + d_cols].ugN = d_matrix[pos].ugN + 1;
		else
			d_matrix[pos + d_cols].ugN = 0;

		if ((d_matrix[pos].ugE and d_matrix[pos].item != UBOE) or d_matrix[pos].item == UBIE)
			d_matrix[pos + 1].ugE = d_matrix[pos].ugE + 1;
		else
			d_matrix[pos + 1].ugE = 0;

		if ((d_matrix[pos].ugS and d_matrix[pos].item != UBOS) or d_matrix[pos].item == UBIS)
			d_matrix[pos + d_cols].ugS = d_matrix[pos].ugS + 1;
		else
			d_matrix[pos + d_cols].ugS = 0;

		if ((d_matrix[pos].ugW and d_matrix[pos].item != UBIW) or d_matrix[pos].item == UBOW)
			d_matrix[pos + 1].ugW = d_matrix[pos].ugW + 1;
		else
			d_matrix[pos + 1].ugW = 0;

		return incrMatrixUntilOK(pos + 1);
	}
	
	if (pos + 1 < d_matrix.size())
		return incrMatrixUntilOK(pos + 1);

	return true;
}