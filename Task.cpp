
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
struct timespec Task::UNIT_NANOSECONDS = {0,0};

Task::Task(Scheduler *s, int c, int p) {
    this->scheduler = s;
    this->time = c;
    this->period = p;
    this->remaining = 0;
    this->critical = false;
    this->taskId = taskIdCounter;
    ++taskIdCounter;
    this->runThread = true;

    sem_init(&this->runSemId,0,0);

    this->RegisterTimer();
    UNIT_NANOSECONDS.tv_nsec = 1000;
}

Task::~Task(){
    this->runThread = false;
    returnCheck(sem_destroy(&this->runSemId), true, 1, "sem_destroy failed");
}

void Task::Start() {
   returnCheck(pthread_create( &this->threadId,
                    NULL,
                    &Task::Run, (void *)this ), true, 1, "Task thread creation failed.");
}


void *Task::Run(void *object) {
    Task *inst = (Task*) object;
    if (!inst) {
        return NULL;
    }

    while (inst->runThread) {
    	printf("task %d  burning\r\n",inst->threadId);
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + inst->taskId, "start");
        while (inst->remaining > 0) {
            nanospin(&UNIT_NANOSECONDS);
            --inst->remaining;
        }
        printf("task %d done\r\n", inst->threadId);
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + inst->taskId, "end");
        returnCheck(sem_wait(&inst->runSemId), true, 1, "Error waiting on runSemId.");
    }

    return( 0 );
}

void Task::SetPriority(int priority) {
	returnCheck(pthread_setschedprio(this->taskId, priority), true, 1, "Error setting priority.");
}

void Task::Schedule() {
    TraceEvent( _NTO_TRACE_INSERTUSRSTREVENT,
                _NTO_TRACE_USERFIRST + this->taskId,
                this->remaining == 0 ? "period:1" : "period:0" );
    if (critical) {
        this->remaining += this->time;
    } else {
        this->remaining = this->time;
    }
    scheduler->Reschedule();
    returnCheck(sem_post(&this->runSemId), true, 1, "Error posting runSemId.");
}


/*  Begin private member functions */

void Task::RegisterTimer(){


	printf("Registering timer :%d\r\n",this->threadId);

    struct sigevent event;
    timer_t timer; //out value for timer create
    struct itimerspec value;

    SIGEV_THREAD_INIT(&event,&PeriodElapsed,(void*)this, NULL); //fill event with instructions to start a new thread

    timer_create(CLOCK_REALTIME, &event, &timer );

    value.it_value.tv_nsec = this->period * UNIT_NANOSECONDS.tv_nsec;
    value.it_value.tv_sec = 0; //TODO: set to 0 for release

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
    ptr->Schedule();
}


