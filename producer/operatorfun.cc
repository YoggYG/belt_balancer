#include "producer.ih"
void Producer::operator()(size_t n, size_t power, size_t rows, size_t cols)
{
    if (rows == 0)
        rows = 2*n;
    if (cols < n)
        cols = n;
    vector<char> matrix(rows * cols, BN);

    matrix[(rows-1) * cols - 1] -= (d_startNumber + 1);
    
    while (getNextMatrix(matrix, n, rows, cols))
    	if (possiblyValid(matrix, n, power))
        	d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
}

// {
//     if (rows == 0)
//         rows = 2*n;
//     if (cols == 0)
//         cols = n;
// 	vector<char> matrix = {
// 		1,1,1,1,
// 		1,5,5,1,
// 		1,3,2,1,
// 		1,6,7,1,
// 		2,1,1,3,
// 		1,4,4,1,
// 		1,6,7,1,
// 		6,7,6,7,
// 		1,1,1,1
// 	};
// 	d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
// }