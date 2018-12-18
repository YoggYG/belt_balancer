#include "producer.ih"

vector<char> Producer::makeMirror(vector<char> &matrix, size_t cols) const
{
	vector<char> resVector(matrix.size(), EMPTY);

	for (size_t idx = cols; idx < matrix.size() - cols; ++idx)
	{
		size_t mirrorIdx = (idx / cols) * cols + cols - (idx % cols + 1);
		switch (matrix[idx])
		{
			case SPLN:
				resVector[mirrorIdx] = SPRN;
				resVector[mirrorIdx - 1] = SPLN;
				break;
			case SPRS:
				resVector[mirrorIdx] = SPLS;
				resVector[mirrorIdx - 1] = SPRS;
				break;
			case SPLE:
				resVector[mirrorIdx] = SPRW;
				resVector[mirrorIdx + cols] = SPLW;
				break;
			case SPRW:
				resVector[mirrorIdx] = SPLE;
				resVector[mirrorIdx + cols] = SPRE;
		}
	}

	return resVector;
}