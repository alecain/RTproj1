/*
 * RateMonotonicScheduler.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: mkerbel
 */

#include "RateMonotonicScheduler.h"

RateMonotonicScheduler::RateMonotonicScheduler() : Scheduler()
{

}

RateMonotonicScheduler::~RateMonotonicScheduler()
{

}
void RateMonotonicScheduler::ScheduleAll() {
	vector<Task*>::iterator it;
	Task* leastPeriodTask = NULL;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		(*it)->SetPriority(1);
		if (leastPeriodTask == NULL || ((*it)->GetPeriod() < leastPeriodTask->GetPeriod())) {
			leastPeriodTask = *it;
		}
	}
	leastPeriodTask->SetPriority(99);
}
