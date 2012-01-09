/*
 * ShortestCompletionTimeScheduler.cpp
 *
 *  Created on: Jan 9, 2012
 *      Author: mkerbel
 */

#include "ShortestCompletionTimeScheduler.h"

ShortestCompletionTimeScheduler::ShortestCompletionTimeScheduler() : Scheduler()
{

}

ShortestCompletionTimeScheduler::~ShortestCompletionTimeScheduler() {
	// TODO Auto-generated destructor stub
}

void ShortestCompletionTimeScheduler::ScheduleAll(){
//	sem_wait(&this->m_pSemaphore);

	// SCT Scheduling
	vector<Task*>::iterator it;
	Task* shortestCompletionTimeTask;

	for (it = m_tasks.begin(); it < m_tasks.end(); it++) {
		if((*it)->GetRemaining() < shortestCompletionTimeTask->GetRemaining())
		{
			shortestCompletionTimeTask = *it;
		}
	}
	shortestCompletionTimeTask->SetPriority(99);
//	it->schedule();
}

