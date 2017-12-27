#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
void do_execl();
void do_execle();

/*
 * Useful explanation: https://stackoverflow.com/questions/5769734/what-are-the-different-versions-of-exec-used-for-in-c-and-c
 * Examples: http://www.yolinux.com/TUTORIALS/ForkExecProcesses.html
 */
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
        do_execle();
        /*char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("four.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
        printf("this shouldn't print out");*/
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }
    return 0;
}

void do_execl() 
{
    // The first argument is the path to the executable.
    // The second argument is what the executable thinks its name is
    // The rest of the arguments are options to the executable
    // The last argument is null.
    execl("/bin/ls", "/bin/ls", "-ltra", (char *) 0);
}

void do_execle()
{
    // execle does not use $PATH to find executables. Only execs with "p" at the end use $PATH
    // execle lets you define an environment and pass it in.
    char *env[] = { "ABC=def", (char *) 0 };
    execle("/bin/bash", "bash", "-c", "echo $ABC", (char *) 0, env);
}
