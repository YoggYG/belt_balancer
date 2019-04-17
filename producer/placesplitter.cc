#include "producer.ih"
#include <chrono>
#include <iostream>

void Producer::placeSplitter(vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace, size_t incr, size_t undergroundLength)
{
	if (splittersToPlace == 0)
	{
		d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power, undergroundLength), false});
		// Balancer bal(matrix, rows, cols, n, power, undergroundLength);
		// bal.print2();
		return;
	}

	if (splittersToPlace == 8)
	{
		auto end_time = chrono::system_clock::now();
		time_t end_c_time = chrono::system_clock::to_time_t(end_time);
		string end_time_string = ctime(&end_c_time);
		
		cerr << end_time_string << endl;

		Balancer bal(matrix, rows, cols, n, power, undergroundLength);
		bal.print2();
	}
	
	for (size_t idx = startIndex; idx < (rows - 1) * cols; idx += incr)
	{
		if (matrix[idx] != EMPTY or (idx + 1) % cols == 0)
			continue;

		// Try to place north splitter first
		if (canPlaceSplitterNorth(matrix, idx, cols, n))
		{
			matrix[idx] = SPLN;
			matrix[idx + 1] = SPRN;

			if (not isMirror(matrix, rows, cols))
				placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1, undergroundLength);

			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}

		if (idx >= matrix.size() - (2 * cols))
			continue;

		// Try to place east splitter
		if (canPlaceSplitterEast(matrix, idx, cols))
		{
			matrix[idx] = SPLE;
			matrix[idx + cols] = SPRE;

			if (not isMirror(matrix, rows, cols))
				placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1, undergroundLength);

			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}
		// Try to place west splitter
		if (canPlaceSplitterWest(matrix, idx, cols))
		{
			matrix[idx] = SPRW;
			matrix[idx + cols] = SPLW;

			if (not isMirror(matrix, rows, cols))
				placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1, undergroundLength);

			matrix[idx] = EMPTY;
			matrix[idx + cols] = EMPTY;
		}

		if (idx < cols * 2)
			continue;

		// Try to place south splitter
		if (canPlaceSplitterSouth(matrix, idx, cols))
		{
			matrix[idx] = SPRS;
			matrix[idx + 1] = SPLS;

			if (not isMirror(matrix, rows, cols))
				placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1, undergroundLength);

			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
	}
}