#include "shareddatahandler.ih"

SharedDataHandler::Spec SharedDataHandler::nextTask()
{
    lock_guard<mutex> lg(d_taskMutex);

    Spec ret = d_tasks.front();

    if (ret.done)
        d_jobsAvailable.notify_all();
    else
        d_tasks.pop();

    return ret;
}
