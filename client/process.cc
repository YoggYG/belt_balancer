#include "client.ih"

void Client::process(Balancer &b)
{   // Work!
    do 
    	if (b.valid()) 
    		// TODO: copy balancer, shrink copy and add the copy of the balancer to the result queue instead of the original balancer. 
    		d_sdh.addRes(SharedDataHandler::Spec{b,false});
	while (b.nextMatrix());
}
