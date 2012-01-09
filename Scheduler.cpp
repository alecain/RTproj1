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
}

Scheduler::~Scheduler() {
}


void *Scheduler::Run(void *object) {
	Scheduler *inst = (Scheduler*)(object);
    if (!inst) {
        return NULL;
    }

	// Starts scheduling thread
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

/**
 *
 * Starts all the task that the scheduler has
 */
void Scheduler::Start()
{
	// Iterate through all tasks and start each one
	vector<Task*>::iterator it;

	for (it = this->m_tasks.begin(); it < this->m_tasks.end(); it++) {
		(*it)->Start();
	}

	//TODO set highest priority
	//TODO find out what priority to use
	pthread_create(&this->m_pSchedulerThread, 0, &Scheduler::Run, this);
	pthread_setschedprio(this->m_pSchedulerThread, 60);


}

void Scheduler::RegisterTask(Task *pNewTask) {
	m_tasks.push_back(pNewTask);
}

void Scheduler::Reschedule() {
	sem_post(&m_pSemaphore);
}
