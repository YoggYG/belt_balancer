#include "client.ih"
#include <iostream>

void Client::process(Balancer &b)
{
	cerr << "Started task\n" << flush;
	b.initMatrix();
    do 
    	if (b.valid()) 
    	{
    		Balancer outputBal(b);
    		outputBal.shrinkBalancer();
    		d_sdh.addRes(SharedDataHandler::Spec{outputBal,false});
    	}
	while (b.nextMatrix());
}
