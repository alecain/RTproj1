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
	Scheduler();
	virtual ~Scheduler();
private:
	void Init();

public:
	void Start();

	void ScheduleAll();

	void Reschedule();
};

#endif /* SCHEDULER_H_ */
