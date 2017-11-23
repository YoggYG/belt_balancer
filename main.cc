#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <ctime>
#include "balancer/balancer.h"
#include "producers/producers.h"
#include "clients/clients.h"
#include "outputhandler/outputhandler.h"
#include "shareddatahandler/shareddatahandler.h"

using namespace std;

int main(int argc, char **argv) {
	auto start_time = chrono::system_clock::now();
	
	size_t n;
	if (argc < 2)
	{
		cout << "Provide the number of belts to be balanced\n";
		exit(0);
	}

	if (!(istringstream(argv[1]) >> n))
	{
		cout << "Input must be a number\n";
		exit(0);
	}

	size_t maxHeight = 0;
	if (argc > 2)
		if (!(istringstream(argv[2]) >> maxHeight))
		{
			cout << "Input must be a number\n";
			exit(0);
		}	

	size_t maxWidth = 0;	
	if (argc > 3)
		if (!(istringstream(argv[3]) >> maxWidth))
		{
			cout << "Input must be a number\n";
			exit(0);
		}

	size_t power = double(log2(n));
	if (double(log2(n)) > power)
		++power;
	n = pow(2,power);

	size_t threads_on_machine = thread::hardware_concurrency();
	if (threads_on_machine == 0)
	{
		cout << "Unable to detect available threads, using 8 as default\n";
		threads_on_machine = 8;
	}

	bool noSouthBelts = true;
	bool onlyNorthUGS = false;

	SharedDataHandler sdh(30);

	Producers producers(sdh, threads_on_machine, noSouthBelts, onlyNorthUGS);
	Clients clients(sdh, threads_on_machine);
	OutputHandler opHandler(sdh);
	
	producers.run(n, power, maxHeight, maxWidth);
	clients.run();
	thread opThread(ref(opHandler));

	producers.join();
	vector<char> endVector;
	SharedDataHandler::Spec endSignal = SharedDataHandler::Spec{Balancer(endVector, 0, 0, 0, 0), true};
	sdh.addTask(endSignal);

	clients.join();
	sdh.addRes(endSignal);

	opThread.join();

	sdh.sortVector();
	sdh.printSolution();

	auto end_time = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end_time - start_time;
	time_t start_c_time = chrono::system_clock::to_time_t(start_time);
	time_t end_c_time = chrono::system_clock::to_time_t(end_time);

	cout << "Started computation on " << ctime(&start_c_time)
		 << "Finished computation on " << ctime(&end_c_time)
		 << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}