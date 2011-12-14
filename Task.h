/*
 * Task.h
 *
 *  Created on: Dec 14, 2011
 *      Author: axz5388
 */

#ifndef TASK_H_
#define TASK_H_


#include <signal.h>
#include <sys/siginfo.h>
#include <time.h>


#include <pthread.h>
#include <semaphore.h>

/**
* Represents a task to be scheduled by the Scheduler class.
*/
class Task {
  private:

    /**
    * How many nanoseconds represent one time unit.
    * This should not exceed 550 milliseconds.
    */
    const long UNIT_NANOSECONDS = 1000;

    /**
    * The number of units that the task should take to run.
    * The c value in the (c, p, d) triple.
    */
    int time;

    /**
    * The period of the task. Assumed to also be the deadline.
    */
    int period;

    /**
    * The remaining amount of units that this task must run.
    */
    int remaining;

    /**
    * The number id of the task. Added to _NTO_TRACE_USERFIRST
    * Must be between 0 and (_NTO_TRACE_USERLAST - _NTO_TRACE_USERFIRST)
    */
    int taskId;

    /**
    * Whether this task is critical.
    * A critical task must finish before the enxt time it is run.
    * A non-critical task is killed if it misses it's deadline.
    */
    bool critical;

    /**
    * The Scheduler that is scheduling the current task set.
    */
    Scheduler * scheduler;

    /**
    * The current task's thread id.
    */
    pthread_t threadId;

    /**
    * Whether the current task should continue running.
    */
    bool runThread;

    /**
    * The semephore used to block tasks that have completed
    * but have not yet reached their period (idle tasks).
    */
    static sem_t runSemId;


  public:
    Task(Scheduler s, int c, int p, int taskId);
    ~Task();

    /**
    *
    */
    void setCritical(bool critical);

    /**
    *
    */
    void setPriority(int priority);

    /**
    *
    */
    int getRemaining() {
        return this->remaining;
    }

    /**
    *
    */
    void schedule(bool reschedule);

    /**
     * Registers a timer to call PeriodElapsed every $period microseconds
     */
    void Task::RegisterTimer();

  private:
    /**
    *
    */
    static void *run(void *object);

    /**
    *
    */
    static void PeriodElapsed();


};

#endif /* TASK_H_ */
