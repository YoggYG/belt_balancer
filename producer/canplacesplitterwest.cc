#include "producer.ih"

bool Producer::canPlaceSplitterWest(vector<char> &matrix, size_t idx, size_t cols)
{
	if (/*(idx + 1) % cols == 0 or */idx % cols == 0/* or idx >= matrix.size() - (2 * cols)*/)
		return false;

	if (matrix[idx + 1] == SPRE)
		return false;

	if (matrix[idx - cols] != EMPTY and matrix[idx - cols] != SPRE and matrix[idx - cols] != SPLW)
		return false;

	if (matrix[idx - 1] != EMPTY and matrix[idx - 1] != SPLW)
		return false;

	if (matrix[idx - 2] != EMPTY and matrix[idx - 2] != SPLW and matrix[idx - 2] != SPRN and matrix[idx - 2] != SPLS)
		return false;

	if (matrix[idx - cols - 1] == SPLS or matrix[idx - cols + 1] == SPLN)
		return false;

	if (matrix[idx - 2] == SPLW and matrix[idx + 1] == SPLW)
		return false;

	if (matrix[idx - 1] == SPLW and matrix[idx + 2] == SPLW)
		return false;

	if ((idx + 2) % cols == 0 and idx > 3 * cols and matrix[idx - 2 * cols] == SPRN and matrix[idx - 3 * cols] == SPLN)
		return false;

	if (idx % cols == 1 and idx > 3 * cols and matrix[idx - 2 * cols] == SPRS and matrix[idx - 3 * cols] == SPLS)
		return false;

	if (matrix[idx - 3] == SPRW and (matrix[idx - 1] == SPLW or matrix[idx - 2] == SPLW))
		return false;

	if (matrix[idx - 2] == SPLW and matrix[idx - cols] == SPLW)
		return false;

	if (matrix[idx - cols] == SPLW and matrix[idx + 2] == SPLW)
		return false;

	return true;
}