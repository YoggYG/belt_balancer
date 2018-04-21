#include "producer.ih"
#include <iostream>

void Producer::placeSplitter(vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace)
{
	if (splittersToPlace == 0)
	{
		cerr << "Submitted a balancer to task queue\n" << flush;
		d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
		return;
	}
	
	for (size_t idx = startIndex; idx < (rows - 1) * cols; ++idx)
	{
		if (matrix[idx] != EMPTY)
			continue;

		// Try to place north splitter first
		if ((idx + 1) % cols != 0 and matrix[idx + 1] == EMPTY)
		{
			matrix[idx] = SPLN;
			matrix[idx + 1] = SPRN;
			placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
		if (idx % cols != 0 and (idx + 1) % cols != 0 and idx + cols < (rows - 1) * cols)
		{
			matrix[idx] = SPLE;
			matrix[idx + cols] = SPRE;
			placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}
		if (idx % cols != 0 and (idx + 1) % cols != 0 and idx + cols < (rows - 1) * cols)
		{
			matrix[idx] = SPRW;
			matrix[idx + cols] = SPLW;
			placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}
		if ((idx + 1) % cols != 0 and matrix[idx + 1] == EMPTY and idx >= 2 * cols and idx < (rows - 2) * cols)
		{
			matrix[idx] = SPRS;
			matrix[idx + 1] = SPLS;
			placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
	}
}