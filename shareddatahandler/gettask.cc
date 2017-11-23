#include "shareddatahandler.ih"

SharedDataHandler::Spec SharedDataHandler::getTask()
{
    d_jobsAvailable.wait();
    Spec ret = nextTask();
    d_storageAvailable.notify_all();

    return ret;
}
