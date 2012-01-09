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
	Task* EarliestDeadlineTask;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		(*it)->SetPriority(1);
		if((*it)->GetPeriod() < EarliestDeadlineTask->GetPeriod())
		{
			EarliestDeadlineTask = *it;
		}
	}
	EarliestDeadlineTask->SetPriority(99);
//	it->schedule();

}
