#include <cstdlib>
#include <iostream>

#include "Scheduler.h"
#include "RateMonotonicScheduler.h"
#include "Task.h"
#include <string>

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	Scheduler * scheduler(new RateMonotonicScheduler());
	scheduler->RegisterTask(new Task(scheduler, 1, 2));
	scheduler->RegisterTask(new Task(scheduler, 1, 2));
	scheduler->RegisterTask(new Task(scheduler, 1, 2));
	scheduler->RegisterTask(new Task(scheduler, 1, 2));

	Scheduler::Start(scheduler);

	std::string input;
	while(std::cin>>input && input!="q"){
		std::cout<<"what was that?\r\n";
	}
}
