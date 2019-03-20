#include "producer.ih"

bool Producer::isMirror(vector<char> &matrix, size_t rows, size_t cols)
{
	vector<char> mirror = makeMirror(matrix, cols);

	// for (size_t mirrorType = 0; mirrorType < 3; ++mirrorType)
	{
		// if (mirrorType == 1)
		// 	mirror = makeVerticalMirror(matrix, rows, cols);
		// if (mirrorType == 2)
		// 	mirror = makeDoubleMirror(matrix, rows, cols);

		size_t idx;
		for (idx = 0; idx < matrix.size(); ++idx)
		{
			if (mirror[idx] > 0 and ((mirror[idx] + 1) / 2 < (matrix[idx] + 1) / 2 or matrix[idx] == 0))
				return true;

			// if (matrix[idx] > 0)
			// 	break;

			// if (mirror[idx] > 0)
			// 	return true;
		}

		// if (mirror[idx] > 0 and mirror[idx] < matrix[idx])
		// 	return true;
	}
	return false;
}