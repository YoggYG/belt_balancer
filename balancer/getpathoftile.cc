#include "balancer.ih"
#include <iostream>

vector<Triple> Balancer::getPathOfTile(size_t pos)
{
	vector<Triple> resVector;

	resVector.push_back(Triple{d_matrix[pos].item, pos % d_cols, pos / d_cols});
	size_t idx = pos;

	while (idx / d_cols != 0)
	{
		size_t len = 0;
		switch (d_matrix[idx].item)
		{
			case BN:
			case UBON:
				idx -= d_cols;
				break;
			case BE:
			case UBOE:
				++idx;
				break;
			case BW:
			case UBOW:
				--idx;
				break;
			case BS:
			case UBOS:
				idx += d_cols;
				break;
			case UBIN:
				for (len = 2; len < d_underground_length; ++len)
					if (d_matrix[idx - len * d_cols] == UBON)
					{
						idx -= len * d_cols;
						break;
					}
				break;
			case UBIE:
				for (len = 2; len < d_underground_length; ++len)
					if (d_matrix[idx + len] == UBOE)
					{
						idx += len;
						break;
					}
				break;
			case UBIW:
				for (len = 2; len < d_underground_length; ++len)
					if (d_matrix[idx - len] == UBOW)
					{
						idx -= len;
						break;
					}
				break;
			case UBIS:
				for (len = 2; len < d_underground_length; ++len)
					if (d_matrix[idx + len * d_cols] == UBOS)
					{
						idx += len * d_cols;
						break;
					}
				break;
			default:
				cerr << "SOMETHING WENT WRONG IN getPathOfTile\n";
		}

		if (isSplitter(d_matrix[idx]) or d_matrix[idx] == EMPTY or len == d_underground_length)
			break;

		resVector.push_back(Triple{d_matrix[idx].item, idx % d_cols, idx / d_cols});
	}

	idx = pos;

	// while ()


	return resVector;
}