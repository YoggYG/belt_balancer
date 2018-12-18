#include "shareddatahandler.ih"

void SharedDataHandler::addMirror(vector<char> const &matrix)
{
	{
		lock_guard<mutex> lg(d_mirrorMutex);
		d_mirrors.insert(matrix);
	}
}