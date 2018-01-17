#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("argv[0]: %s\n", argv[0]);
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        int wc = waitpid(-1, NULL, 0);
        printf("I am still a child (wc:%d)\n", wc);
    } else {
        // parent goes down this path (original process)
        int wc = waitpid(-1, NULL, 0);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }   
    return 0;
}

/*
    From the man pages:

     wait() and waitpid()
       The wait() system call suspends execution of the calling process until one of its children terminates.  The call wait(&status) is equivalent to:

           waitpid(-1, &status, 0);

       The waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state.  By default, waitpid() waits
       only for terminated children, but this behavior is modifiable via the options argument, as described below.

       The value of pid can be:

       < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.

       -1     meaning wait for any child process.

       0      meaning wait for any child process whose process group ID is equal to that of the calling process.

       > 0    meaning wait for the child whose process ID is equal to the value of pid.

       The value of options is an OR of zero or more of the following constants:
*/

// waitpid allows you to choose which process you want to wait for
