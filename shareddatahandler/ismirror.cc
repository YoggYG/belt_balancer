#include "shareddatahandler.ih"

bool SharedDataHandler::isMirror(vector<char> &matrix)
{
	{
		lock_guard<mutex> lg(d_mirrorMutex);
		return d_mirrors.count(matrix) == 1;
	}
}