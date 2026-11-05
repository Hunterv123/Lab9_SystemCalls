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
    //Check to see if there was a failure changing the priority
    if (new_nice == -1 && errno != 0) {
        perror("Error changing the priority");
        return 1;
    }
    //Print out the new nice value
    printf("The new nice value is %d\n", new_nice);
    //Define the timspec struct and set the appropraiate values
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;
    //Use nanosleep to actualy delay the time
    nanosleep(&ts, NULL);
    printf("See you next time\n");
    return 0;
}