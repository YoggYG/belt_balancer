#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include "balancer/balancer.h"
#include "producers/producers.h"
#include "clients/clients.h"
#include "outputhandler/outputhandler.h"
#include "shareddatahandler/shareddatahandler.h"

using namespace std;

int main(int argc, char **argv) {
	auto start_time = chrono::system_clock::now();
	time_t start_c_time = chrono::system_clock::to_time_t(start_time);
	string start_time_string = ctime(&start_c_time);
	
	size_t n;


	vector<char> test
	{
		0,0,0,0,
		0,13,14,0,
		0,0,0,0,
		0,0,0,0,
		0,13,14,0,
		0,0,0,0,
		0,0,0,0,
		13,14,13,14,
		0,0,0,0
	};

	vector<char> solution
	{
		1,1,1,1,
		1,6,6,1,
		1,3,2,1,
		0,13,14,0,
		2,1,1,3,
		1,5,5,1,
		1,13,14,1,
		13,14,13,14,
		1,1,1,1
	};

	n = 4;

	Balancer testBal(test, 9, 4, 4, 2);
	Balancer solutionBal(solution, 9, 4, 4, 2);

	do
	{
		if (testBal == solutionBal)
		{
			solutionBal.print();
			testBal.print();
			cout << "solutionBal equals testBal.\n";
			cout << "solutionBal.valid() == " << solutionBal.valid() << endl;
			cout << "testBal.valid() == " << testBal.valid() << endl;
			cout << "equal? " << (testBal == solutionBal) << endl;
		}

		//if (testBal.valid())
			testBal.print2();

	} while (testBal.nextMatrix());

	return 0;


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

	if (maxWidth < n)
		maxWidth = n;

	if (maxHeight == 0)
		maxHeight = 2 * n;

	size_t threads_on_machine = thread::hardware_concurrency();
	//size_t threads_on_machine = 1;
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
	time_t end_c_time = chrono::system_clock::to_time_t(end_time);
	string end_time_string = ctime(&end_c_time);

	cerr << "Started computation on " << start_time_string
		 << "Finished computation on " << end_time_string
		 << "Elapsed time: " << elapsed_seconds.count() << "s\n";

	cout << "Started computation on " << start_time_string
		 << "Finished computation on " << end_time_string
		 << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}