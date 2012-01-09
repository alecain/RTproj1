/*
 * EarliestDeadlineFirstScheduler.cpp
 *
 *  Created on: Jan 8, 2012
 *      Author: mkerbel
 */

#include "EarliestDeadlineFirstScheduler.h"

EarliestDeadlineFirstScheduler::EarliestDeadlineFirstScheduler()
{
	Init();
}

EarliestDeadlineFirstScheduler::~EarliestDeadlineFirstScheduler()
{

}

void EarliestDeadlineFirstScheduler::ScheduleAll()
{
//	sem_wait(m_pSemaphore);

	// EDF scheduling
	vector<Task*>::iterator it;
	Task* earliestDeadlineTask;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		if((*it)->getPeriod() < earliestDeadlineTask->getPeriod())
		{
			earliestDeadlineTask = *it;
		}
	}
	earliestDeadlineTask->setPriority(99);
//	it->schedule();

}
