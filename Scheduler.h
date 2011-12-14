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

using std::vector;

class Task;
/**
 * The task that performs scheduling operations
 */
class Scheduler {
public:
	Scheduler();
	~Scheduler();
protected:
	sem_t *m_pSemaphore;
	pthread_t* m_pSchedulerThread;
	vector<Task*> m_tasks;
	void Init(/*void (*StartFunction)()*/);

public:
	void Start();
	virtual void ScheduleAll()=0;
	virtual void Reschedule()=0;

};

#endif /* SCHEDULER_H_ */
