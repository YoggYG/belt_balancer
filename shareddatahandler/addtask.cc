#include "shareddatahandler.ih"

void SharedDataHandler::addTask(SharedDataHandler::Spec bal)
{
	d_storageAvailable.wait();
	{
		lock_guard<mutex> lg(d_taskMutex);
		d_tasks.push(bal);
	}
	d_jobsAvailable.notify_all();
}