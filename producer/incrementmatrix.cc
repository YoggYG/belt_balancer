#include "producer.ih"

void Producer::incrementMatrix(vector<char> &matrix, size_t idx, size_t incr)
{
	matrix[idx] += incr;
	if (d_onlyNorthUGS)
		while (matrix[idx] > 7 and matrix[idx] < 16)
			matrix[idx] += incr;
	if (d_noSouthBelts)
    	while (matrix[idx] > 15 and matrix[idx] < 21)
    		matrix[idx] += incr;
}