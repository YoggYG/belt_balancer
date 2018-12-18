#include "producer.ih"
void Producer::operator()(size_t n, size_t power, size_t rows, size_t cols)
{
    if (rows == 0)
        rows = 2*n;
    if (cols < n)
        cols = n;
    
    vector<char> matrix(rows * cols, EMPTY);

    size_t startIndex = cols + d_startNumber;
    size_t splittersToPlace = power * n / 2;

	// vector<char> test
	// {
	// 	0,0,0,0,
	// 	0,13,14,0,
	// 	0,0,0,0,
	// 	0,0,0,0,
	// 	0,13,14,0,
	// 	0,0,0,0,
	// 	0,0,0,0,
	// 	13,14,13,14,
	// 	0,0,0,0
	// };

	// d_sdh.addTask(SharedDataHandler::Spec{Balancer(test, rows, cols, n, power), false});

    placeSplitter(matrix, startIndex, rows, cols, n, power, splittersToPlace, d_numIncrements);
    
//     while (getNextMatrix(matrix, n, rows, cols))
//     	if (possiblyValid(matrix, n, power))
//         	d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
}