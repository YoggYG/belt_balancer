#include "balancer.ih"

bool Balancer::incrMatrixUntilOK(size_t pos)
{
	cerr << "incrMatrixUntilOK called at pos: " << pos << endl << flush;

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
	{
		cerr << "second to last position in incrMatrixUntilOK\n" << flush;
		return incrMatrixUntilOK(pos + 1);
	}

	//pos is the final pos at this point. Now, build lanes.
	size_t minPos = pos;

	cerr << "pos: " << pos << endl << flush;

	vector<Lane> lanes;
	for (size_t idx = pos; idx > pos - d_cols; --idx)
		if (d_matrix[idx] == BN)
		{
			size_t maxSplitterPos = 0;
			size_t numSplit = 0;
			Lane lane(d_matrix, idx, d_rows, d_cols, d_power, d_underground_length); // This gives a SEGFAULT for some reason, even though the print above is not triggered.

			// for (vector<Triple>::iterator it = lane.d_path.begin(); it != lane.d_path.end(); ++it)
			// 	if (it->item > MAXVAL)
			// 	{
			// 		++numSplit;
			// 		size_t splitterPos = it->y * d_cols + it->x;
			// 		cerr << "splitterPos: " << splitterPos << endl;
			// 		if (splitterPos > maxSplitterPos)
			// 			maxSplitterPos = splitterPos;
			// 	}

			// if (numSplit > d_power)
			// {
			// 	cerr << "maxSplitterPos: " << maxSplitterPos << endl;
			// 	if (d_matrix[maxSplitterPos].item == SPLN or d_matrix[maxSplitterPos].item == SPRN or d_matrix[maxSplitterPos].item == SPLS or d_matrix[maxSplitterPos].item == SPRS)
			// 		while (isSplitter(d_matrix[maxSplitterPos].item))
			// 			maxSplitterPos -= d_cols;
			// 	else
			// 		while (isSplitter(d_matrix[maxSplitterPos].item))
			// 			--maxSplitterPos;
				
			// 	if (maxSplitterPos < minPos)
			// 		minPos = maxSplitterPos;
			// }
			// else if (numSplit == d_power)
			// 	lanes.push_back(lane);
		}

	// if (minPos < pos)
	// {
	// 	cerr << "minPos: " << minPos << endl;
	// 	for (size_t idx = pos; idx > minPos; --idx)
	// 		if (not isSplitter(d_matrix[idx].item))
	// 			d_matrix[idx].item = EMPTY;

	// 	++d_matrix[minPos].item;

	// 	return incrMatrixUntilOK(minPos);
	// }

	return true;
}