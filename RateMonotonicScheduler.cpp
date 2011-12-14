/*
 * RateMonotonicScheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include "RateMonotonicScheduler.h"

RateMonotonicScheduler::RateMonotonicScheduler() {
	Init(/*&Start*/);

}

RateMonotonicScheduler::~RateMonotonicScheduler() {
}

//TODO Possibly not needed -- will be defined in base class
/*void RateMonotonicScheduler::Init() {
	sem_init(semaphore, 0, 0);
}*/

/*void RateMonotonicScheduler::Start() {
	// Starts scheduling thread
	// TODO iterate through all tasks and start each one
	vector<Task*>::iterator it;

	for(it=m_tasks.begin(); it < m_tasks.end(); it++) {

	}
	sem_post(m_pSemaphore);
}*/

void RateMonotonicScheduler::ScheduleAll() {
	sem_wait(m_pSemaphore);
	// perform scheduling
	sem_post(m_pSemaphore);
}

void RateMonotonicScheduler::Reschedule() {
	// TODO post the semaphore
}