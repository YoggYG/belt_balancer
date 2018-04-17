#include "producer.ih"
void Producer::operator()(size_t n, size_t power, size_t rows, size_t cols)
{
    if (rows == 0)
        rows = 2*n;
    if (cols < n)
        cols = n;
    
    vector<char> matrix(rows * cols, EMPTY);

    size_t startIndex = cols;
    size_t splittersToPlace = power * n / 2;

    placeSplitter(matrix, startIndex, rows, cols, n, power, splittersToPlace);
    
//     while (getNextMatrix(matrix, n, rows, cols))
//     	if (possiblyValid(matrix, n, power))
//         	d_sdh.addTask(SharedDataHandler::Spec{Balancer(matrix, rows, cols, n, power), false});
}