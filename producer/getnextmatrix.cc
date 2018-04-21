// #include "producer.ih"

// bool Producer::getNextMatrix(vector<char> &matrix, size_t n, size_t rows, size_t cols)
// {
//     char NbPos = 21;
//     char localNbPos = 2;
//     size_t lastPos = rows * cols - 1;

//     if (n == cols)
//     {
//         lastPos -= cols;
//         localNbPos = NbPos;
//     }

//     do 
//         incrementMatrix(matrix, lastPos, d_numIncrements);
//     while (edgeCase(matrix, lastPos, rows, cols));

//     size_t pos = lastPos;
//     while (matrix[pos] >= localNbPos and pos >= 1)
//     {
//         do
//             incrementMatrix(matrix, pos - 1, 1);
//         while (edgeCase(matrix, pos - 1, rows, cols));

//         if (pos == lastPos)
//             matrix[pos] = BN + matrix[pos] % d_numIncrements;
//         else
//             matrix[pos] = BN;
//         --pos;
//         if (localNbPos != NbPos and pos >= cols and pos < (rows - 1) * cols)
//             localNbPos = NbPos;
//         if (localNbPos == NbPos and pos < cols)
//             localNbPos = 2;
//     }

//     if (matrix[0] > 1)
//         return false;
//     return true;
// }