#include "client.ih"

void Client::process(Balancer &b)
{   // Work!
    //pause();
    //b.print();
    if (b.valid())
    	d_sdh.addRes(SharedDataHandler::Spec{b,false});    	
}
