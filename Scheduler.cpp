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

void Scheduler::Init(void (*StartFunction)()) {
	sem_init(m_pSemaphore, 0, 0);
	pthread_create(m_scheduleTask, 0, Start, 0);
}

void Scheduler::RegisterTask(Task *pNewTask) {
	m_Tasks.push_back(pNewTask);
}
