/****************************
 * Filename: pinfo.c
 * Name: Hunter Vassar
 * Assignment: Lab 9 System Calls
 * Section: 121
 *****************************/

#define _GNU_SOURCE

#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc, char* argv[])
{
    if (argc == 1) {
        //Get the process ID for current process running
        //Pass in 0 instead of the processor ID to get current running
        pid_t pid = getpid();
        printf("ID of current processor running is %d\n", pid);
        //Get the nice value/ranking for process priority
        errno = 0;
        int nice_value = getpriority(PRIO_PROCESS, 0);
        if (nice_value == -1 && errno != 0) {
            perror("Could not get priority");
        } else {
            printf("Current priority number is %d\n", nice_value);
        }
        //Get the schuedling policy using sched_getscheduler
        int policy = sched_getscheduler(0);
        if (policy == -1) {
            perror("Error getting shceduler");
        } else {
            //Use a switch case to print the possible scheduling policy for the running process
            switch (policy) {
                case SCHED_OTHER: printf("Scheduling method: SCHED_OTHER\n"); break;
                case SCHED_FIFO:  printf("Scheduling method: SCHED_FIFO\n");  break;
                case SCHED_RR:    printf("Scheduling method: SCHED_RR\n");    break;
                case SCHED_BATCH: printf("Scheduling method: SCHED_BATCH\n"); break;
                case SCHED_IDLE:  printf("Scheduling method: SCHED_IDLE\n");  break;
                default:          printf("Scheduling method: unknown (%d)\n", policy);
            }
        }

    } else if (argc == 2) {
        //Must first validate that the process identifier exists
        pid_t pid = atoi(argv[1]);
        if (pid <= 0) {
            fprintf(stderr, "Invalid process ID: %s\n", argv[1]);
            return 1;
        }
        //call kill with a signal of 0
        if (kill(pid, 0) == 0) {
            //Get the nice value/ranking for process priority
            errno = 0;
            int nice_value = getpriority(PRIO_PROCESS, pid);
            if (nice_value == -1 && errno != 0) {
            perror("Could not get priority");
        } else {
            printf("Current priority number is %d\n", nice_value);
        }
        } else {
            perror("Could not find process");
            return 1;
        }
        //Get the schuedling policy using sched_getscheduler
        int policy = sched_getscheduler(pid);
        if (policy == -1) {
            perror("Error getting shceduler");
        } else {
            //Use a switch case to print the possible scheduling policy for the running process
            switch (policy) {
                case SCHED_OTHER: printf("Scheduling method: SCHED_OTHER\n"); break;
                case SCHED_FIFO:  printf("Scheduling method: SCHED_FIFO\n");  break;
                case SCHED_RR:    printf("Scheduling method: SCHED_RR\n");    break;
                case SCHED_BATCH: printf("Scheduling method: SCHED_BATCH\n"); break;
                case SCHED_IDLE:  printf("Scheduling method: SCHED_IDLE\n");  break;
                default:          printf("Scheduling method: unknown (%d)\n", policy);
            }
        }
    } else {
        printf("Too many arguments");
    }
    return 0;
}