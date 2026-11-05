/****************************
 * Filename: pmod.c
 * Name: Hunter Vassar
 * Assignment: Lab 9 System Calls
 * Section: 121
 *****************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //Reduce the priotory by 10
    int new_nice = nice(10);
    if (new_nice == -1 && errno != 0) {
        perror("Error changing the priority");
        return 1;
    }
    printf("The new nice value is %d\n", new_nice);
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;
    nanosleep(&ts, NULL);
    printf("See you next time\n");
    return 0;
}