#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("parent pid = %u\n", getpid());
    // for loop is similar to fork3 (1st child from parent forks another child)
    // calling fork twice
    for (int i = 0; i < 2; i++)
    {
        fork();
    }
    printf("check pid = %u, ppid = %u\n", getpid(), getppid());
    // since wait will give pid of the child, wait will be -1 when you will not have any children
    // better to put this way rather than putting one wait for each child
    while(wait(NULL) != -1);
    return 0;
}