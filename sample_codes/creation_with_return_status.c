#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status, termret;
    pid = fork();
    if (pid < 0)
    {
        perror("fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // child created
        printf("child process, pid = %u, exiting now\n", getpid());
        exit(3);
    }
    else
    {
        printf("parent process\n");
    }
    // returns pid to termret, wait takes address of integer pointer
    termret = wait(&status);
    printf("child with pid = %u, exit status = %u\n", termret, status / 256);
    return 0;
}