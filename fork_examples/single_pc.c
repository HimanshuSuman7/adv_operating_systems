#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t var1;
    printf("fork program starting \n");
    var1 = fork();
    if (var1 < 0)
    {
        perror("fork failed\n");
        exit(1);
    }
    else if (var1 == 0)
    {
        printf("This is from child process My PID is % d, my Parent PID is % d and var1 is % d\n", getpid(), getppid(), var1);
    }
    else
    {
        printf("This is from parent process My PID is % d, my Child’s PID is % d and var1 is % d\n", getpid(), var1, var1);
        wait(NULL);
    }
    return 0;
}
