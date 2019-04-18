#include "producer.ih"

bool Producer::isMirror(vector<char> &matrix, size_t rows, size_t cols)
{
	vector<char> mirror = makeMirror(matrix, cols);

	for (size_t mirrorType = 0; mirrorType < 3; ++mirrorType)
	{
		if (mirrorType == 1)
			mirror = makeVerticalMirror(matrix, rows, cols);
		if (mirrorType == 2)
			mirror = makeDoubleMirror(matrix, rows, cols);

		size_t idx;
		for (idx = 0; idx < matrix.size(); ++idx)
		{
			if (matrix[idx] > 0 and mirror[idx] == 0)
				break;

			if (matrix[idx] == 0 and mirror[idx] > 0)
				return true;

			if (matrix[idx] > mirror[idx])
				return true;

			if (matrix[idx] < mirror[idx])
				break;
		}
	}

	double middleRow = (rows - 1) / 2.0;

	double weightedSum = 0;

	for (size_t row = 0; row < rows; ++row)
	{
		double weight = middleRow - row;

		for (size_t idx = row * cols; idx < (row + 1) * cols; ++idx)
		{
			if (matrix[idx] == SPLN or matrix[idx] == SPLS)
				weightedSum += weight;

			if (matrix[idx] == SPLE or matrix[idx] == SPRW)
				weightedSum += weight - 0.5;
		}
	}

	if (weightedSum < 0)
		return true;

	return false;
}