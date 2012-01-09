/*
 * ShortestCompletionTimeScheduler.h
 *
 *  Created on: Jan 9, 2012
 *      Author: mkerbel
 */

#ifndef SHORTESTCOMPLETIONTIMESCHEDULER_H_
#define SHORTESTCOMPLETIONTIMESCHEDULER_H_

#include "Scheduler.h"

class ShortestCompletionTimeScheduler: public Scheduler {
public:
	ShortestCompletionTimeScheduler();
	virtual ~ShortestCompletionTimeScheduler();

	void ScheduleAll();
};

#endif /* SHORTESTCOMPLETIONTIMESCHEDULER_H_ */
