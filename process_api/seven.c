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
        close(STDOUT_FILENO);
        // printf here will not be printed to standard out since it is closed
        printf("closed stdout_fileno");
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
