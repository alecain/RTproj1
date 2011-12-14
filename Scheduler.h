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
#include "Task.cpp"

/**
 * The task that performs scheduling operations
 */
class Scheduler {
public:
	virtual Scheduler();
	virtual ~Scheduler();
private:
	sem_t *m_pSemaphore;
	pthread_t* m_scheduleTask;

protected:
	vector<Task*> m_Tasks;
	void Init(void (*StartFunction)());

public:
	virtual void Start()=0;
	void RegisterTask(Task *pNewTask);
	virtual void ScheduleAll()=0;
	virtual void Reschedule()=0;

};

#endif /* SCHEDULER_H_ */
