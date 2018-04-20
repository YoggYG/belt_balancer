#include "producer.ih"
void Producer::placeSplitter(vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace)
{
	vector<char> splList = {SPLN, SPLE, SPRW, SPRS};

	if (splittersToPlace == 0)
	{
		//d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
		Balancer bal(matrix, rows, cols, n, power);
		bal.print();
		return;
	}
	
	for (size_t idx = startIndex; idx < (rows - 1) * cols; ++idx)
	{
		if (matrix[idx] != EMPTY)
			continue;

		for (size_t splType = 0; splType < splList.size(); ++splType)
		{
			// Try to place north splitter first
			if (splList[splType] == SPLN)
			{
				if ((idx + 1) % cols != 0 and matrix[idx + 1] == EMPTY)
				{
					matrix[idx] = SPLN;
					matrix[idx + 1] = SPRN;
					placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
				}
			}
			// Try to place east splitter
			if (splList[splType] == SPLE) 
			{
				if (idx % cols != 0 and (idx + 1) % cols != 0 and idx + cols < (rows - 1) * cols)
				{
					matrix[idx] = SPLE;
					matrix[idx + cols] = SPRE;
					placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
				}
			}
			// Try to place west splitter
			if (splList[splType] == SPRW)
			{
				if (idx % cols != 0 and (idx + 1) % cols != 0 and idx + cols < (rows - 1) * cols)
				{
					matrix[idx] = SPRW;
					matrix[idx + cols] = SPLW;
					placeSplitter(matrix, idx + 1, rows, cols, n, power, splittersToPlace - 1);
				}
			}
			// Try to place south splitter
			if (splList[splType] == SPRS)
			{
				if ((idx + 1) % cols != 0 and matrix[idx + 1] == EMPTY and idx >= 2 * cols and idx < (rows - 2) * cols)
				{
					matrix[idx] = SPRS;
					matrix[idx + 1] = SPLS;
					placeSplitter(matrix, idx + 2, rows, cols, n, power, splittersToPlace - 1);
				}
			}
		}
	}
}