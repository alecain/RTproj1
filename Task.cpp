
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/trace.h>
#include <time.h>

#include "Task.h"
#include "Scheduler.h"

int returnCheck(int retValue, bool exitOnError, int exitValue, const char* message) {
    if (retValue == -1) {
        perror(message);
        if(exitOnError) {
            exit(exitValue);
        }
    }

    return(retValue);
}

int Task::taskIdCounter = 1;

Task::Task(Scheduler *s, int c, int p) {
    this->scheduler = s;
    this->time = c;
    this->period = p;
    this->remaining = 0;
    this->critical = false;
    this->taskId = taskIdCounter;
    ++taskIdCounter;
    this->runThread = true;

    this->RegisterTimer();
    //UNIT_NANOSECONDS.tv_nsec = 1000;
}

Task::~Task(){
    this->runThread = false;
    //TODO:complaining about the semaphore.. I'm pretty sure it shouldn't be a static semaphore for all tasks
    //returnCheck(sem_destroy(&Task::runSemId), true, 1, "sem_destroy failed");
}

void Task::start() {
	//TODO:Fix this. complaining about the function the thread is running to start
   /* returnCheck(pthread_create( &this->threadId,
                    NULL,
                    &Task::run, this ), true, 1, "Task thread creation failed.");*/
}

//TODO:Fix this to compile.. Should this really be returning a void*? Also, can someone explain why this is static to me?
/*static void *Task::run(void *object){
    Task *inst = dynamic_cast<Task*>(object);
    if (!inst) {
        return NULL;
    }

    while (inst->runThread) {
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + inst->taskId, "start");
        while (inst->remaining > 0) {
            nanospin(&UNIT_NANOSECONDS);
            --inst->remaining;
        }
        returnCheck(sem_wait(&Task::runSemId), true, 1, "Error waiting on runSemId.");
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + inst->taskId, "end");
    }
}
*/

void Task::setPriority(int priority) {
	returnCheck(pthread_setschedprio(this->taskId, priority), true, 1, "Error setting priority.");
}

void Task::schedule() {
    TraceEvent( _NTO_TRACE_INSERTUSRSTREVENT,
                _NTO_TRACE_USERFIRST + this->taskId,
                this->remaining == 0 ? "period:1" : "period:0" );
    if (critical) {
        this->remaining += this->time;
    } else {
        this->remaining = this->time;
    }
    scheduler->Reschedule();
    //TODO:same semaphore problem here
    //returnCheck(sem_post(&Task::runSemId), true, 1, "Error posting runSemId.");
}


/*  Begin private member functions */

#define TIMESCALE 10000000
void Task::RegisterTimer(){


	printf("Registering timer\r\n");

    struct sigevent event;
    timer_t timer; //out value for timer create
    struct itimerspec value;

    SIGEV_THREAD_INIT(&event,&PeriodElapsed,(void*)this, NULL); //fill event with instructions to start a new thread

    timer_create(CLOCK_REALTIME, &event, &timer );

    value.it_value.tv_nsec = this->period*TIMESCALE;
    value.it_value.tv_sec = 1;

    //the following causes the timer to reload... Which is bad when we are debugging.
    //value.it_interval.tv_nsec = this->period*TIMESCALE;
    //value.it_interval.tv_sec = 1;
    timer_settime(timer,0,&value,NULL);


    //timer_connect (timerid, periodElapsed,this);


}


/**
 * Handle the SIGALARM event for this task indicating that the period is
 * elapsed, and we need to reset.
 *
 */

void Task::PeriodElapsed(sigval arg){

    //cast the arg as a pointer to a task
    Task *ptr=(Task *)arg.sival_ptr;

    //reload the timer
   ptr->RegisterTimer();

    //call schedule on the supplied argument
    ptr->schedule();
}


