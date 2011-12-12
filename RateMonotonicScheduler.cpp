/*
 * RateMonotonicScheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include "RateMonotonicScheduler.h"

RateMonotonicScheduler::RateMonotonicScheduler() {
	// TODO Auto-generated constructor stub

}

RateMonotonicScheduler::~RateMonotonicScheduler() {
	// TODO Auto-generated destructor stub
}

void RateMonotonicScheduler::Init() {
	sem_init(semaphore, 0, 0);
}

void RateMonotonicScheduler::Start() {

}

void RateMonotonicScheduler::ScheduleAll() {
	sem_wait(semaphore);
	// perform scheduling
	sem_post(semaphore);
}

void RateMonotonicScheduler::Reschedule() {

}
