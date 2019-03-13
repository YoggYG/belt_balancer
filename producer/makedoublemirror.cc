#include "producer.ih"

vector<char> Producer::makeDoubleMirror(vector<char> &matrix, size_t rows, size_t cols) const
{
	vector<char> mirror;
	vector<char> resVector;

	mirror = makeVerticalMirror(matrix, rows, cols);

	resVector =  makeMirror(mirror, cols);

	return resVector;
}