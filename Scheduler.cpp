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
	Init();
}

Scheduler::~Scheduler() {
}

void Scheduler::Init(/*void(*StartFunction)()*/) {
	sem_init(&this->m_pSemaphore, 0, 0);
	//TODO set highest priority
	//TODO find out what priority to use
	pthread_create(&this->m_pSchedulerThread, 0, &Scheduler::Start, this);
	pthread_setschedprio(this->m_pSchedulerThread, 100);
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
		(*it)->start();
	}

	while(!m_tasks.empty()){
		// schedule a task
		ScheduleAll();
		// post semaphore -- call reschedule()
		Reschedule();
		// wait for semaphore
		sem_wait(m_pSchedulerThread);
		// [ other task runs ]
		// [ other task posts semaphore ]
	}
	sem_post(&inst->m_pSemaphore);

	//TODO:figure out what to return? Should we return?
	return NULL;
}

void Scheduler::RegisterTask(Task *pNewTask) {
	m_tasks.push_back(pNewTask);
}

void Scheduler::Reschedule() {
	sem_post(&m_pSemaphore);
}
