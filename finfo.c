/****************************
 * Filename: finfo.c
 * Name: Hunter Vassar
 * Assignment: Lab 9 System Calls
 * Section: 121
 *****************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

int main(int argc, char* argv[])
{   
    //checks that the user only provided 1 argument
    if (argc != 2) {
        fprintf(stderr, "Please provide a filepath");
    }
    struct stat st;
    //Checks that the filepath provided exists
    if (stat(argv[1], &st) == -1) {
        perror("Could not find file path");
        return 1;
    } else {
        //Prints out the file type, uses and if-else statement to 
        //to test each possible type of file
        printf("File type: ");
        if (S_ISREG(st.st_mode)) {
            printf("Regular File\n");
        }else if (S_ISDIR(st.st_mode)) {
            printf("Directory File\n");
        }else if (S_ISLNK(st.st_mode)) {
            printf("Symbolic Link\n");
        } else {
            printf("Some other file type\n");
        }
        //Prints out the permissions, there are 3 groups, owenr, group,
        //and others.
        printf("Permissions:\n");
        printf("  Owner:  %c%c%c\n",
            (st.st_mode & S_IRUSR) ? 'r' : '-',
            (st.st_mode & S_IWUSR) ? 'w' : '-',
            (st.st_mode & S_IXUSR) ? 'x' : '-');
        printf("  Group:  %c%c%c\n",
            (st.st_mode & S_IRGRP) ? 'r' : '-',
            (st.st_mode & S_IWGRP) ? 'w' : '-',
            (st.st_mode & S_IXGRP) ? 'x' : '-');
        printf("  Others: %c%c%c\n",
            (st.st_mode & S_IROTH) ? 'r' : '-',
            (st.st_mode & S_IWOTH) ? 'w' : '-',
            (st.st_mode & S_IXOTH) ? 'x' : '-');
            //Prints out the owner of the file using st_uid
            printf("The owner of the file: %u\n", st.st_uid);
            //Prints out the size of the file using st_size
            printf("The size of the file: %lld bytes\n", (long long)st.st_size);
            //Print out the last modified date, ctime makes it human readable
            printf("Last Modified: %s\n", ctime(&st.st_mtime));
    }
    return 0;
}