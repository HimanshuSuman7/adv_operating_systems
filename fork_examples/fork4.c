#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("parent pid = %u\n", getpid());
    // parent executes
    if (fork()) {
        // only parent enters (non-zero value), child value is 0(false)
        if (!fork()) {
            // now 2nd child is created and it enters but parent doesn't
            fork();
            // 2nd child will create another child (grandchild)
        }
    }
    printf("check, pid = %u, ppid = %u\n", getpid(), getppid());
    wait(NULL);
    wait(NULL);
    return 0;
}