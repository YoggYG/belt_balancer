#include "shareddatahandler.ih"

void SharedDataHandler::printSolution()
{
	cout << "\nSorted solutions based on cost\n";
	for (vector<Balancer>::iterator it = d_balancers.begin(); it != d_balancers.end(); ++it)
		it->print();
}