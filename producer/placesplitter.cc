#include "producer.ih"
void Producer::placeSplitter(vector<char> &matrix, size_t startIndex, size_t rows, size_t cols, size_t n, size_t power, size_t splittersToPlace)
{
	vector<char> splList = {SPLN, SPRE, SPLW, SPRS};

	if (splittersToPlace == 0)
		return; //maybe add to task queue here
	
	for (size_t idx = startIndex; idx < (rows - 1) * cols; ++idx)
	{
		//for ()
	}

}