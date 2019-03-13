#include "producer.ih"

vector<char> Producer::makeVerticalMirror(vector<char> &matrix, size_t rows, size_t cols) const
{
	vector<char> resVector(matrix.size(), EMPTY);

	for (size_t idx = cols; idx < matrix.size() - cols; ++idx)
	{
		size_t mirrorIdx = idx % cols + cols * (rows - (1 + idx / cols));
		switch (matrix[idx])
		{
			case SPLN:
				resVector[mirrorIdx] = SPLN;
				resVector[mirrorIdx + 1] = SPRN;
				break;
			case SPRS:
				resVector[mirrorIdx] = SPRS;
				resVector[mirrorIdx + 1] = SPLS;
				break;
			case SPLE:
				resVector[mirrorIdx] = SPRE;
				resVector[mirrorIdx - cols] = SPLE;
				break;
			case SPRW:
				resVector[mirrorIdx] = SPLW;
				resVector[mirrorIdx - cols] = SPRW;
		}
	}

	return resVector;
}