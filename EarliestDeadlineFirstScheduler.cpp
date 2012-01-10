/*
 * EarliestDeadlineFirstScheduler.cpp
 *
 *  Created on: Jan 8, 2012
 *      Author: mkerbel
 */

#include "EarliestDeadlineFirstScheduler.h"

EarliestDeadlineFirstScheduler::EarliestDeadlineFirstScheduler() : Scheduler()
{

}

EarliestDeadlineFirstScheduler::~EarliestDeadlineFirstScheduler()
{

}

void EarliestDeadlineFirstScheduler::ScheduleAll()
{
//	sem_wait(m_pSemaphore);

	// EDF scheduling
	vector<Task*>::iterator it;
	Task* earliestDeadlineTask = NULL;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		(*it)->SetPriority(1);
		if(earliestDeadlineTask == NULL || (*it)->GetTimeToDeadline() < earliestDeadlineTask->GetTimeToDeadline())
		{
			earliestDeadlineTask = *it;
		}
	}
	earliestDeadlineTask->SetPriority(99);
//	it->schedule();

}
