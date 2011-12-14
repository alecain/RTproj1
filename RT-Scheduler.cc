#include <cstdlib>
#include <iostream>

#include "RateMonotonicScheduler.h"
#include "Task.h"

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;
	RateMonotonicScheduler scheduler();
	scheduler.RegisterTask(new Task(&scheduler, 1, 2));
	scheduler.RegisterTask(new Task(&scheduler, 1, 2));
	scheduler.RegisterTask(new Task(&scheduler, 1, 2));
	scheduler.RegisterTask(new Task(&scheduler, 1, 2));
	return EXIT_SUCCESS;
}
