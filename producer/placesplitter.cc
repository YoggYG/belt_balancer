#include "producer.ih"
#include <iostream>

void Producer::placeSplitter(vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace, size_t incr, size_t undergroundLength)
{
	if (splittersToPlace == 0)
	{
		d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power, undergroundLength), false});
		// Balancer bal(matrix, rows, cols, n, power);
		// bal.print();
		return;
	}
	
	for (size_t idx = startIndex; idx < (rows - 1) * cols; idx += incr)
	{
		// bool calculated = false;
		// bool stored = false;

		if (matrix[idx] != EMPTY or (idx + 1) % cols == 0)
			continue;

		// Try to place north splitter first
		if (canPlaceSplitterNorth(matrix, idx, cols, n))
		{
			matrix[idx] = SPLN;
			matrix[idx + 1] = SPRN;

			if (not isMirror(matrix, rows, cols))
				placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1, undergroundLength);
				// calculated = true;

			// if (not d_sdh.isMirror(matrix))
			// {
			// 	stored = true;
			// 	d_sdh.addMirror(makeMirror(matrix, cols));
			// 	d_sdh.addMirror(makeVerticalMirror(matrix, rows, cols));
			// 	d_sdh.addMirror(makeDoubleMirror(matrix, rows, cols));
			// 	placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1);
			// }

			// if (calculated != stored)
			// {
			// 	cerr << "calculated != stored, " << calculated << ", " << stored << endl;
			// 	Balancer bal(matrix, rows, cols, n, power);
			// 	bal.print2();
			// 	vector<char> mirror = makeMirror(matrix, cols);
			// 	Balancer bal2(mirror, rows, cols, n, power);
			// 	bal2.print2();
			// 	vector<char> verticalMirror = makeVerticalMirror(matrix, rows, cols);
			// 	Balancer bal3(verticalMirror, rows, cols, n, power);
			// 	bal3.print2();
			// 	vector<char> doubleMirror = makeDoubleMirror(matrix, rows, cols);
			// 	Balancer bal4(doubleMirror, rows, cols, n, power);
			// 	bal4.print2();
			// }

			// calculated = false;
			// stored = false;

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
				// calculated = true;

			// if (not d_sdh.isMirror(matrix))
			// {
			// 	stored = true;
			// 	d_sdh.addMirror(makeMirror(matrix, cols));
			// 	d_sdh.addMirror(makeVerticalMirror(matrix, rows, cols));
			// 	d_sdh.addMirror(makeDoubleMirror(matrix, rows, cols));
			// 	placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1);
			// }

			// if (calculated != stored)
			// {
			// 	cerr << "calculated != stored, " << calculated << ", " << stored << endl;
			// 	Balancer bal(matrix, rows, cols, n, power);
			// 	bal.print2();
			// 	vector<char> mirror = makeMirror(matrix, cols);
			// 	Balancer bal2(mirror, rows, cols, n, power);
			// 	bal2.print2();
			// 	vector<char> verticalMirror = makeVerticalMirror(matrix, rows, cols);
			// 	Balancer bal3(verticalMirror, rows, cols, n, power);
			// 	bal3.print2();
			// 	vector<char> doubleMirror = makeDoubleMirror(matrix, rows, cols);
			// 	Balancer bal4(doubleMirror, rows, cols, n, power);
			// 	bal4.print2();
			// }

			// calculated = false;
			// stored = false;

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
			// 	calculated = true;
			
			// if (not d_sdh.isMirror(matrix))
			// {
			// 	stored = true;
			// 	d_sdh.addMirror(makeMirror(matrix, cols));
			// 	d_sdh.addMirror(makeVerticalMirror(matrix, rows, cols));
			// 	d_sdh.addMirror(makeDoubleMirror(matrix, rows, cols));
			// 	placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1);
			// }

			// if (calculated != stored)
			// {
			// 	cerr << "calculated != stored, " << calculated << ", " << stored << endl;
			// 	Balancer bal(matrix, rows, cols, n, power);
			// 	bal.print2();
			// 	vector<char> mirror = makeMirror(matrix, cols);
			// 	Balancer bal2(mirror, rows, cols, n, power);
			// 	bal2.print2();
			// 	vector<char> verticalMirror = makeVerticalMirror(matrix, rows, cols);
			// 	Balancer bal3(verticalMirror, rows, cols, n, power);
			// 	bal3.print2();
			// 	vector<char> doubleMirror = makeDoubleMirror(matrix, rows, cols);
			// 	Balancer bal4(doubleMirror, rows, cols, n, power);
			// 	bal4.print2();
			// }

			// calculated = false;
			// stored = false;

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
			// 	calculated = true;
			
			// if (not d_sdh.isMirror(matrix))
			// {
			// 	stored = true;
			// 	d_sdh.addMirror(makeMirror(matrix, cols));
			// 	d_sdh.addMirror(makeVerticalMirror(matrix, rows, cols));
			// 	d_sdh.addMirror(makeDoubleMirror(matrix, rows, cols));
			// 	placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1, 1);
			// }

			// if (calculated != stored)
			// {
			// 	cerr << "calculated != stored, " << calculated << ", " << stored << endl;
			// 	Balancer bal(matrix, rows, cols, n, power);
			// 	bal.print2();
			// 	vector<char> mirror = makeMirror(matrix, cols);
			// 	Balancer bal2(mirror, rows, cols, n, power);
			// 	bal2.print2();
			// 	vector<char> verticalMirror = makeVerticalMirror(matrix, rows, cols);
			// 	Balancer bal3(verticalMirror, rows, cols, n, power);
			// 	bal3.print2();
			// 	vector<char> doubleMirror = makeDoubleMirror(matrix, rows, cols);
			// 	Balancer bal4(doubleMirror, rows, cols, n, power);
			// 	bal4.print2();
			// }

			// calculated = false;
			// stored = false;

			matrix[idx] = EMPTY;
			matrix[idx + 1] = EMPTY;
		}
	}
}