#include "producer.ih"

bool Producer::canPlaceSplitterNorth(vector<char> &matrix, size_t idx, size_t cols, size_t n)
{
	if (/*(idx + 1) % cols == 0 or */matrix[idx + 1] != EMPTY)
		return false;

	if (matrix[idx - cols] != EMPTY and matrix[idx - cols] != SPRN)
		return false;

	if (matrix[idx - cols + 1] != EMPTY and matrix[idx - cols + 1] != SPLN)
		return false;

	if (matrix[idx - 1] != EMPTY and matrix[idx - 1] != SPRN and matrix[idx - 1] != SPLS)
		return false;

	if (idx < cols * 2)
	{
		size_t numOutputs = 0;
		for (size_t idx2 = cols; idx2 < idx; ++idx2)
			if (matrix[idx2] == SPLN)
				++numOutputs;

		return numOutputs * 2 < n;
	}

	if (matrix[idx - (2 * cols)] != EMPTY and matrix[idx - (2 * cols)] != SPRN and matrix[idx - (2 * cols)] != SPLW and matrix[idx - (2 * cols)] != SPRE)
		return false;

	if (matrix[idx - (2 * cols) + 1] != EMPTY and matrix[idx - (2 * cols) + 1] != SPLN and matrix[idx - (2 * cols) + 1] != SPLW and matrix[idx - (2 * cols) + 1] != SPRE)
		return false;

	if (matrix[idx - 1] == SPRN and matrix[idx - 2 * cols] == SPRN)
		return false;

	if (matrix[idx - 2 * cols] == SPRN and matrix[idx - 2 * cols + 1] == SPLN)
		return false;

	return true;
}