#include "producer.ih"

bool Producer::canPlaceSplitterEast(vector<char> &matrix, size_t idx, size_t cols)
{
	if (/*(idx + 1) % cols == 0 or */idx % cols == 0/* or idx >= matrix.size() - (2 * cols)*/)
		return false;

	if (matrix[idx + 1] == SPLW)
		return false;

	if (matrix[idx - cols] != EMPTY and matrix[idx - cols] != SPRE and matrix[idx - cols] != SPLW)
		return false;

	if (matrix[idx - 1] != EMPTY and matrix[idx - 1] != SPRE)
		return false;

	if (matrix[idx - 2] != EMPTY and matrix[idx - 2] != SPRE and matrix[idx - 2] != SPRN and matrix[idx - 2] != SPLS)
		return false;

	return true;
}