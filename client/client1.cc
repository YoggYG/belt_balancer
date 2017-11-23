#include "client.ih"

Client::Client(SharedDataHandler &sdh)
:
    d_sdh(sdh),
    d_id(++s_id)
{}
