/*
 * Scheduler.h
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <vector>
#include <semaphore.h>
#include <pthread.h>
#include "Task.h"

using std::vector;

/**
 * The task that performs scheduling operations
 */
class Scheduler {
public:
	Scheduler();
	~Scheduler();
protected:
	sem_t m_pSemaphore;
	pthread_t m_pSchedulerThread;
	vector<Task*> m_tasks;

public:
	static void *Run(void *object);
	void Start();
	virtual void ScheduleAll()=0;
	void Reschedule();
	virtual void RegisterTask(Task *pNewTask);

};

#endif /* SCHEDULER_H_ */
