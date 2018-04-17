#include "lane.ih"

bool Lane::valid(vector<char> &matrix)
{
	if (d_path.back().item != BN || d_path.back().y != EMPTY)
		return false;

	size_t numSplit = 0;
	for (vector<Triple>::iterator it = d_path.begin(); it != d_path.end(); ++it)
		switch (it->item)
		{
			case SPLN: 
				if (it->x + 1 >= d_cols) 
					return false;
				if (matrix[it->y * d_cols + it->x + 1] != SPRN)
					return false; 
				++numSplit;
				break;
			case SPRN: 
				if (it->x == 0)
					return false; 
				if (matrix[it->y * d_cols + it->x - 1] != SPLN)
					return false;
				++numSplit;
				break;
			case SPLE: 
				if (it->y + 1 >= d_rows) 
					return false; 
				if (matrix[(it->y + 1) * d_cols + it->x] != SPRE)
					return false;
				++numSplit;
				break;
			case SPRE: 
				if (it->y == 0) 
					return false; 
				if (matrix[(it->y - 1) * d_cols + it->x] != SPLE)
					return false;
				++numSplit;
				break;
			case SPLS: 
				if (it->x == 0) 
					return false; 
				if (matrix[it->y * d_cols + it->x - 1] != SPRS)
					return false;
				++numSplit;
				break;
			case SPRS: 
				if (it->x + 1 >= d_cols) 
					return false; 
				if (matrix[it->y * d_cols + it->x + 1] != SPLS)
					return false; 
				++numSplit;
				break;
			case SPLW: 
				if (it->y == 0) 
					return false; 
				if (matrix[(it->y - 1) * d_cols + it->x] != SPRW)
					return false;
				++numSplit;
				break;
			case SPRW: 
				if (it->y + 1 >= d_rows) 
					return false; 
				if (matrix[(it->y + 1) * d_cols + it->x] != SPLW)
					return false;
				++numSplit;
				break;
		}
	if (numSplit != d_power)
		return false;
	return true;
}