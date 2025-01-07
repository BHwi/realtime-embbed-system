#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>

#define NUM_THREADS 1

typedef struct
{
	int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
//
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];

void *myThread(void *threadp)
{
	threadParams_t *threadParams = (threadParams_t *)threadp;
	
	syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Thread!");

	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	openlog("pthread", LOG_PID | LOG_CONS, LOG_USER);
	
	char buffer[1024];

	FILE* uname_output = popen("uname -a", "r");
	fgets(buffer, sizeof(buffer), uname_output);
	pclose(uname_output);

	syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] %s", buffer);

	int rc;
	int i;
	for(i= 0; i < NUM_THREADS; i++)
	{
		threadParams[i].threadIdx = i;

		pthread_create(&threads[i], // pointer to thread descriptor
			       (void *) 0,
			       myThread,
			       (void *)&(threadParams[i])
			      );
	}

	for(i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	syslog(LOG_INFO, "[COURSE:1][ASSIGNMENT:1] Hello World from Main!");
	closelog();

	return 0;
}
