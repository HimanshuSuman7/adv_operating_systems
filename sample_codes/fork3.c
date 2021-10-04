#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// 
int main(int argc, char *argv[])
{
    printf("parent pid = %u\n", getpid());
    fork();
    // child is created and child starts excuting from below 
    fork();
    // one grandchild is created and it starts execution
    // after 1st child returns, parent executes and 2nd child is created
    printf("forked, pid = %u, ppid = %u\n", getpid(), getppid());
    // all child processed execute the wait system call, if no child executes stiil it will wait
    wait(NULL);
    wait(NULL);
    return 0;
}