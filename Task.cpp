
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


}

#include <pthread.h>
#include <semaphore.h>

int returnCheck(int retValue, bool exitOnError, int exitValue, char* message) {
    if (retValue == -1) {
        perror(message);
        if(exitOnError) {
            exit(exitValue);
        }
    }

    return(retValue);
}

Task::Task(Scheduler *s, int c, int p, int taskId){
    this->scheduler = s;
    this->time = c;
    this->period = p;
    this->remaining = 0;
    this->critical = false;
    this->taskId = taskId;
    this->runThread = true;
    returnCheck(pthread_create( &this->threadId,
                    NULL,
                    &Task::run, this ), true, 1, "Task thread creation failed.");
}

Task::~Task(Scheduler *s, int c, int p, const char *name){
    this->runThread = false;
    returnCheck(sem_destroy(&Task::runSemId), true, 1, "sem_destroy failed");
}

static void *Task::run(void *object){
    Task *inst = dynamic_cast<Task*>(object);
    if (!inst) {
        return NULL;
    }

    while (runThread) {
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + this->taskId, "start");
        while (remaining > 0) {
            nano_spin(UNIT_NANOSECONDS);
            --remaining;
        }
        returnCheck(sem_wait(&Task::runSemId), true, 1, "Error waiting on runSemId.");;
        TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST + this->taskId, "end");
    }
}

Task::setPriority(int priority) {
    pthread_setschedparam(...)
}
Task::setCritical(bool critical) {
    this->critical = critical;
}
Task::schedule(bool reschedule) {
    TraceEvent( _NTO_TRACE_INSERTUSRSTREVENT,
                _NTO_TRACE_USERFIRST + this->taskId,
                this->remaining == 0 ? "period:1" : "period:0" );
    if (critical) {
        this->remaining += this->time;
    } else {
        this->remaining = this->time;
    }
    if (reschedule) {
        scheduler.reschedule();
    }
    returnCheck(sem_post(&Task::runSemId), true, 1, "Error posting runSemId.");
}


/*  Begin private member functions */


void Task::RegisterTimer(){

    struct sigevent event;
    timer_t timer; //out value for timer create

    SIGEV_THREAD_INIT(&event, SIGALRM, &this->period,); //load timer
    timer_create(CLOCK_REALTIME, &event, &timer );
}


/**
 * Handle the SIGALARM event for this task indicating that the period is
 * elapsed, and we need to reset.
 *
 */

void PeriodElapsed(void* arg){

    //cast the arg as a pointer to a task
    Task *ptr=(Task *) arg;

    //reset timer
    prt->RegisterTimer();

    //call schedule on the supplied argument
    ptr.schedule(TRUE);
}

