/*
 * RateMonotonicScheduler.h
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#ifndef RATEMONOTONICSCHEDULER_H_
#define RATEMONOTONICSCHEDULER_H_

#include "Scheduler.h"

class RateMonotonicScheduler: public Scheduler {
public:
	RateMonotonicScheduler();
	virtual ~RateMonotonicScheduler();

private:
//	void Init();

public:
	void ScheduleAll();
	void Reschedule();
};

#endif /* RATEMONOTONICSCHEDULER_H_ */
