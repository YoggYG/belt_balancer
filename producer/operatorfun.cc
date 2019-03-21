#include "producer.ih"
void Producer::operator()(size_t n, size_t power, size_t rows, size_t cols, size_t undergroundLength)
{
    if (rows == 0)
        rows = 2*n;
    if (cols < n)
        cols = n;
    
    vector<char> matrix(rows * cols, EMPTY);

    size_t startIndex = cols + d_startNumber;
    size_t splittersToPlace = power * n / 2;

    placeSplitter(matrix, startIndex, rows, cols, n, power, splittersToPlace, d_numIncrements, undergroundLength);
}