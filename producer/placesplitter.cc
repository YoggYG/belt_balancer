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
		if ((idx + 1) % cols != 0 
			and matrix[idx + 1] == EMPTY and matrix[idx + 2] == EMPTY
			and (matrix[idx - cols] == EMPTY or matrix[idx - cols] == SPRN)
			and (matrix[idx + 1 - cols] == EMPTY or matrix[idx + 1 - cols] == SPLN)
			and (idx < 2 * cols or ((matrix[idx - 2 * cols] == EMPTY or matrix[idx - 2 * cols] == SPRE or matrix[idx - 2 * cols] == SPLW or matrix[idx - 2 * cols] == SPRN) 
				and (matrix[idx - 2 * cols + 1] == EMPTY or matrix[idx - 2 * cols + 1] == SPRE or matrix[idx - 2 * cols + 1] == SPLW or matrix[idx - 2 * cols + 1] == SPLN)))
			and (matrix[idx - 1] == EMPTY or matrix[idx - 1] == SPRN or matrix[idx - 1] == SPLS))
		{
			matrix[idx] = SPLN;
			matrix[idx + 1] = SPRN;
			placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
		if ((idx + 1) % cols > 1 and idx < (rows - 2) * cols 
			and (matrix[idx + 1] == EMPTY or matrix[idx + 1] == SPRE)
			and (matrix[idx - 1] == EMPTY or matrix[idx - 1] == SPRE)
			and matrix[idx - 1 + cols] == EMPTY
			and (matrix[idx - 2] == EMPTY or matrix[idx - 2] == SPRN or matrix[idx - 2] == SPLS or matrix[idx - 2] == SPRE)
			and (matrix[idx - cols] == EMPTY or matrix[idx - cols] == SPRE or matrix[idx - cols] == SPLW))
		{
			matrix[idx] = SPLE;
			matrix[idx + cols] = SPRE;
			placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}
		if ((idx + 1) % cols > 1 and idx < (rows - 2) * cols
			and (matrix[idx + 1] == EMPTY or matrix[idx + 1] == SPLW)
			and (matrix[idx - 1] == EMPTY or matrix[idx - 1] == SPLW)
			and matrix[idx - 1 + cols] == EMPTY
			and (matrix[idx - 2] == EMPTY or matrix[idx - 2] == SPRN or matrix[idx - 2] == SPLS or matrix[idx - 2] == SPLW)
			and (matrix[idx - cols] == EMPTY or matrix[idx - cols] == SPRE or matrix[idx - cols] == SPLW))
		{
			matrix[idx] = SPRW;
			matrix[idx + cols] = SPLW;
			placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}
		if ((idx + 1) % cols != 0 and idx >= 2 * cols and idx < (rows - 2) * cols
			and matrix[idx + 1] == EMPTY and matrix[idx + 2] == EMPTY
			and (matrix[idx - cols] == EMPTY or matrix[idx - cols] == SPLS)
			and (matrix[idx + 1 - cols] == EMPTY or matrix[idx + 1 - cols] == SPRS)
			and (matrix[idx - 2 * cols] == EMPTY or matrix[idx - 2 * cols] == SPRE or matrix[idx - 2 * cols] == SPLW or matrix[idx - 2 * cols] == SPLS) 
			and (matrix[idx - 2 * cols + 1] == EMPTY or matrix[idx - 2 * cols + 1] == SPRE or matrix[idx - 2 * cols + 1] == SPLW or matrix[idx - 2 * cols + 1] == SPRS)
			and (matrix[idx - 1] == EMPTY or matrix[idx - 1] == SPRN or matrix[idx - 1] == SPLS))
		{
			matrix[idx] = SPRS;
			matrix[idx + 1] = SPLS;
			placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
	}
}