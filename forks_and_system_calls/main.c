#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void create_child(int, int, int);

int main(int argc, char *argv[])
{
    // taking input from user
    int even, odd, tree_level;
    sscanf(argv[1], "%d", &even);
    sscanf(argv[2], "%d", &odd);
    sscanf(argv[3], "%d", &tree_level);
    printf("even = %d, odd = %d, tree_level = %d\n", even, odd, tree_level);

    // get pid of parent process
    pid_t root = getpid();
    printf("root pid = %u\n", root);
    // calling to create child processes
    create_child(even, odd, tree_level);
    // checking if parent exited
    printf("root process, pid = %u exited\n", getpid());

    return 0;
}

void create_child(int even, int odd, int tree_level)
{
    int status = 0, n = even, retrive_id;
    // base condition
    if (tree_level > 0)
    {
        // assign even/odd to n
        if (getpid() % 2)
            n = odd;
        
        // iterating based on pid
        for (int i = 0; i < n; i++)
        {
            // calling fork, child will execute after this
            pid_t id = fork();
            if (id < 0)
            {
                // process not created
                perror("fork failed.\n");
                exit(0);
            }
            else if (id == 0)
            {
                printf("child created, pid = %u, ppid = %u\n", getpid(), getppid());
                // printf("level = %d\n", tree_level);
                // recursion
                create_child(even, odd, --tree_level);
                exit(0);
            }
            else
            {
                // parent process waiting for children
                retrive_id = wait(&status);
                printf("child pid = %d exited. exit status = %d\n", retrive_id, status / 256);
            }
        }
    }
}