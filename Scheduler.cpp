/*
 * Scheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include <pthread.h>
#include "Scheduler.h"
//#include "Task.h"

Scheduler::Scheduler() {
	sem_init(&this->m_pSemaphore, 0, 0);
	//TODO set highest priority
	//TODO find out what priority to use
	pthread_create(&this->m_pSchedulerThread, 0, &Scheduler::Start, this);
	pthread_setschedprio(this->m_pSchedulerThread, 100);
}

Scheduler::~Scheduler() {
}


void *Scheduler::Start(void *object) {
	Scheduler *inst = (Scheduler*)(object);
    if (!inst) {
        return NULL;
    }

	// Starts scheduling thread
	// Iterate through all tasks and start each one
	vector<Task*>::iterator it;

	for (it = inst->m_tasks.begin(); it < inst->m_tasks.end(); it++) {
		(*it)->Start();
	}

	while(!inst->m_tasks.empty()){
		// schedule a task
		inst->ScheduleAll();
		// wait for semaphore
		sem_wait(&inst->m_pSemaphore);
		// [ other task runs ]
		// [ other task posts semaphore ]
	}

	//TODO:figure out what to return? Should we return?
	return NULL;
}

void Scheduler::RegisterTask(Task *pNewTask) {
	m_tasks.push_back(pNewTask);
}

void Scheduler::Reschedule() {
	sem_post(&m_pSemaphore);
}
