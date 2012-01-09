/*
 * RateMonotonicScheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include "RateMonotonicScheduler.h"

void RateMonotonicScheduler::ScheduleAll() {
	vector<Task*>::iterator it;
	Task* leastPeriodTask;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		if((*it)->GetPeriod() < leastPeriodTask->GetPeriod()) {
			leastPeriodTask = *it;
		}
	}
	leastPeriodTask->SetPriority(99);
}
