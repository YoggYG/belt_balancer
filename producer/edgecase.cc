#include "producer.ih"

bool Producer::edgeCase(vector<char> &matrix, size_t idx, size_t rows, size_t cols)
{
	if (idx < 2 * cols)
		if (matrix[idx] == UBIN or matrix[idx] == SPRE or matrix[idx] == SPLW or (matrix[idx] > 16 and matrix[idx] < 21))
			return true;
	if (idx > (rows - 2) * cols - 1)
		if (matrix[idx] == UBON or matrix[idx] == SPLE or (matrix[idx] > 14 and matrix[idx] < 21))
			return true;
	if (idx % cols == 0)
		if (matrix[idx] == BW or (matrix[idx] > 6 and matrix[idx] < 16) or matrix[idx] == SPLS)
			return true;
	if (idx % cols == cols - 1)
		if (matrix[idx] == BE or matrix[idx] == SPLN or (matrix[idx] > 7 and matrix[idx] < 16) or matrix[idx] == SPRS)
			return true;
	return false;
}