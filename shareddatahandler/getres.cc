#include "shareddatahandler.ih"

SharedDataHandler::Spec SharedDataHandler::getRes()
{
    d_outputQAvailable.wait();
    Spec ret = nextRes();

    return ret;
}
