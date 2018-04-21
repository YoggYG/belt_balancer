// #include "producer.ih"

// bool Producer::possiblyValid(vector<char> &matrix, size_t n,size_t power)
// {
// 	vector<size_t> hist(21,0);
// 	for (size_t idx = 0; idx < matrix.size(); ++idx)
// 		++hist[matrix[idx]];
// 	if (hist[4] != hist[5] or hist[8] != hist[9] or hist[10] != hist[11] or hist[17] != hist[18])
// 		return false;
// 	if (hist[6] != hist[7] or hist[12] != hist[13] or hist[14] != hist[15] or hist[19] != hist[20])
// 		return false;
// 	if (hist[6] + hist[12] + hist[14] + hist[19] != power * n / 2)
// 		return false;
// 	return true;
// }