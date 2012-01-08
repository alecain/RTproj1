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

class Scheduler;

/**
* Represents a task to be scheduled by the Scheduler class.
*/
class Task {
  private:

	/**
	 * A global task id that is incremented with each new process.
	 */
	static int taskIdCounter;

    /**
    * How many nanoseconds represent one time unit.
    * This should not exceed 550 milliseconds.
    */
    static timespec UNIT_NANOSECONDS;

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
    /**
     * Instantiates a new Task scheduled by scheduler s, time c, period p and task id taskId.
     */
    Task(Scheduler *s, int c, int p);
    ~Task();

    /**
     * Starts the task thread.
     */
    void start();

    /**
    * Sets whether the task is critical. Critical tasks do not get killed if they missed their deadline.
    */
    void setCritical(bool critical) {
        this->critical = critical;
    }

    /**
    * Sets the priority of the task thread. Used by the scheduler.
    */
    void setPriority(int priority);

    /**
    * Gets the remaining time for this task. Used for some scheduling algorithms.
    */
    int getRemaining() {
        return this->remaining;
    }

    /**
    * Schedules the task to run.
    */
    void schedule();

    /**
     * Registers a timer to call PeriodElapsed every $period microseconds
     */
    void RegisterTimer();

  private:
    /**
    * Burns CPU for `remaining` time in a new thread.
    */
    static void *run(void *object);

    /**
    *
    */
    static void PeriodElapsed(sigval arg);


};

#endif /* TASK_H_ */
