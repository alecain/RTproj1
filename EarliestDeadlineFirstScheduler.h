/**
 * EarliestDeadlineFirstScheduler.h
 */

#ifndef EARLIESTDEADLINEFIRSTSCHEDULER_H_
#define EARLIESTDEADLINEFIRSTSCHEDULER_H_

#include "Scheduler.h"

class EarliestDeadlineFirstScheduler : public Scheduler
{
public:
	EarliestDeadlineFirstScheduler();
	virtual ~EarliestDeadlineFirstScheduler();

	void ScheduleAll();

};

#endif /* EARLIESTDEADLINEFIRSTSCHEDULER_H_ */
