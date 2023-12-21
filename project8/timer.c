#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "curr_time.h"                  /* Declares currTime() */
#include "itimerspec_from_str.h"        /* Declares itimerspecFromStr() */

static void handler(int sig, siginfo_t *si, void *uc){
    printf("[%s] Got signal %d\n", currTime("%T"), sig);
}

int main(int argc, char *argv[]){
    struct itimerspec ts;
    struct sigaction  sa;
    timer_t *tidlist;

    if (argc != 2){
        fprintf(stderr, "%s [initial time up]:[interval time up]\n", argv[0]);
    	exit(1);
    }
    tidlist = calloc(argc - 1, sizeof(timer_t));
    if (tidlist == NULL)
        perror("malloc");

    /* Establish handler for notification signal */

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(60, &sa, NULL) == -1)
        perror("sigaction");
/* ToDo:
    struct sigevent sev;
    ...
*/
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = 60;
    sev.sigev_value.sival_ptr = tidlist;
    itimerspecFromStr(argv[1], &ts);
    if (timer_create(CLOCK_REALTIME, &sev, &tidlist[0]) == -1)
    	perror("timer_create");
    printf("Timer ID: %ld (%s)\n", (long) tidlist[0], argv[1]);
    
    if (timer_settime(tidlist[0], 0, &ts, NULL) == -1)
    	perror("timer_settime");

    for (;;)                            /* Wait for incoming timer signals */
        pause();
}
