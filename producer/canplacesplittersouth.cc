#include "producer.ih"

bool Producer::canPlaceSplitterSouth(vector<char> &matrix, size_t idx, size_t cols)
{
	if (/*(idx + 1) % cols == 0 or */matrix[idx + 1] != EMPTY/* or idx < cols * 2 or idx >= matrix.size() - (2 * cols)*/)
		return false;

	if (matrix[idx - cols] != EMPTY and matrix[idx - cols] != SPLS)
		return false;

	if (matrix[idx - cols + 1] != EMPTY and matrix[idx - cols + 1] != SPRS)
		return false;

	if (matrix[idx - 1] != EMPTY and matrix[idx - 1] != SPRN and matrix[idx - 1] != SPLS)
		return false;

	if (matrix[idx - (2 * cols)] != EMPTY and matrix[idx - (2 * cols)] != SPLS and matrix[idx - (2 * cols)] != SPLW and matrix[idx - (2 * cols)] != SPRE)
		return false;

	if (matrix[idx - (2 * cols) + 1] != EMPTY and matrix[idx - (2 * cols) + 1] != SPRS and matrix[idx - (2 * cols) + 1] != SPLW and matrix[idx - (2 * cols) + 1] != SPRE)
		return false;

	if (idx == 2 * cols or idx == 3 * cols - 2 or idx == matrix.size() - 3 * cols or idx == matrix.size() - 2 * cols - 2)
		return false;

	if (matrix[idx + 2] != EMPTY)
		return false;

	if (matrix[idx - cols - 1] == SPLW or matrix[idx - cols + 2] == SPRE)
		return false;

	if (idx >= cols * 3 and matrix[idx - 3 * cols] == SPRS and (matrix[idx - 2 * cols + 1] == SPRS or matrix[idx - cols + 1] == SPRS))
		return false;

	if (idx >= cols * 3 and matrix[idx - 3 * cols] == SPRS and (matrix[idx - 2 * cols] == SPLS or matrix[idx - cols] == SPLS))
		return false;

	if (matrix[idx - 1] == SPLS and matrix[idx - 2 * cols] == SPLS)
		return false;

	if (matrix[idx - 2 * cols] == SPLS and matrix[idx - 2 * cols + 1] == SPRS)
		return false;

	return true;
}