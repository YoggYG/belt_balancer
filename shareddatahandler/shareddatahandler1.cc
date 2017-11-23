#include "shareddatahandler.ih"

SharedDataHandler::SharedDataHandler(size_t storageAvailable)
:
    d_storageAvailable(storageAvailable),
    d_jobsAvailable(0),
    d_outputQAvailable(0)
{}
