#include "shareddatahandler.ih"

SharedDataHandler::Spec SharedDataHandler::nextRes()
{
    lock_guard<mutex> lg(d_resultMutex);

    Spec ret = d_results.front();
    d_results.pop();

    return ret;
}
