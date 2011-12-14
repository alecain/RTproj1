/*
 * Scheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include "Scheduler.h"
//#include "Task.h"

Scheduler::Scheduler() {
	Init();
}

Scheduler::~Scheduler() {
}

void Scheduler::Init(/*void(*StartFunction)()*/) {
	sem_init(m_pSemaphore, 0, 0);
	//TODO set highest priority
	pthread_setschedparam(m_schedulerThread, SCHED_OTHER, PRIORITY_MAX);
	pthread_create(m_schedulerThread, 0, Start, 0);
}

void Scheduler::Start() {
	// Starts scheduling thread
	// Iterate through all tasks and start each one
	vector<Task*>::iterator it;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		it.Start();
	}
	sem_post(m_pSemaphore);
}

void Scheduler::RegisterTask(Task *pNewTask) {
	m_tasks.push_back(pNewTask);
}
