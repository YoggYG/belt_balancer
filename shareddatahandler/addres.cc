#include "shareddatahandler.ih"

void SharedDataHandler::addRes(SharedDataHandler::Spec bal)
{
	{
		lock_guard<mutex> lg(d_resultMutex);
		d_results.push(bal);
	}
	d_outputQAvailable.notify_all();
}