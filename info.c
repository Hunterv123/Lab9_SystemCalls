/****************************
 * Filename: info.c
 * Name: Hunter Vassar
 * Assignment: Lab 9 System Calls
 * Section: 121
 *****************************/

#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>
int main(int argc, char* argv[])
{   //Display time of day in nanoseconds
    //Make the timespec struct 
    struct timespec ts;
    //Use CLOCK_REALTIME to get the real time
    clock_gettime(CLOCK_REALTIME, &ts);
    long long ns = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
    printf("The current time of day in nanoseconds is %lld\n", ns);

    //Display the systems network name
    //Big enough buffer to read full name, use gethostname to actually get the name
    char buffer[256];
    if (gethostname(buffer, sizeof(buffer)) == 0) {
        printf("The networks name is %s\n", buffer);
    }
    //Display the operating system name, verison, release, and hardware type
    //The utsname struct contains all the variables to do so 
    struct utsname uts;
    if(uname(&uts) == 0) {
        printf("Operating system name: %s\n", uts.sysname);
        printf("Operating system release: %s\n", uts.release);
        printf("Operating system version: %s\n", uts.version);
        printf("Operating system hardware type: %s\n", uts.machine);
    }
    //Number of CPUs on the system
    //Simply use get_nprocs to get the number of CPUs
    printf("Number of CPUs: %d\n", get_nprocs_conf());
    //Total amount of physical and free memory in bytes
    //This uses sysconf
    long page_size = sysconf(_SC_PAGESIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long free_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("The total physical memory in bytes is %lld\n", (long long)page_size * total_pages);
    printf("The total free memory in bytes is %lld\n", (long long)free_pages * total_pages);
    return 0;
}