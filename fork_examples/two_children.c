#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t child1, child2;
    child1 = fork();
    if (child1 == 0)
    {
        printf("child1 created, pid = %d, ppid = %d\n", getpid(), getppid());
    }
    else
    {
        child2 = fork();
        if (child2 == 0)
        {
            printf("child2 created, pid = %d, ppid = %d\n", getpid(), getppid());
        }
        else
        {
            printf("parent process, pid = %d\n", getpid());
        }
    }
    return 0;
}