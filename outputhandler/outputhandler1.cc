#include "outputhandler.ih"

OutputHandler::OutputHandler(SharedDataHandler &sdh)
:
    d_sdh(sdh),
    d_id(++s_id)
{}
