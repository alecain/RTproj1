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

/**
 * The task that performs scheduling operations
 */
class Scheduler {
public:
	virtual Scheduler();
	virtual ~Scheduler();
private:
	sem_t *m_pSemaphore;
	pthread_t* m_schedulerThread;

protected:
	vector<Task*> m_tasks;
	void Init(/*void (*StartFunction)()*/);

public:
	void Start();
	virtual void ScheduleAll()=0;
	virtual void Reschedule()=0;

};

#endif /* SCHEDULER_H_ */
