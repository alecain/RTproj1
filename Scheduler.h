/*
 * Scheduler.h
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

class Scheduler {
public:
	virtual Scheduler();
	virtual ~Scheduler();
private:
	sem_t *m_pSemaphore;

private:
	void Init();

public:
	void Start();

	virtual void ScheduleAll()=0;

	virtual void Reschedule()=0;
};

#endif /* SCHEDULER_H_ */
