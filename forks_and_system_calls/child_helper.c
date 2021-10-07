#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "helper.h"

// array to store pid_t of child process
int child_arr[200];

// decide what range to choose
int decide_even_odd(int proc_id, int even, int odd)
{
    if (proc_id % 2)
        return odd;
    return even;
}

// function to spawn children based on the input provided by the user
void parent_spawns_child(int get_even, int get_odd, int tree_height)
{
    int status = 0, range, retrive_id;

    // base condition - tree_height should be greater than zero
    if (tree_height > 0)
    {
        // assign get_even/get_odd to n
        range = decide_even_odd(getpid(), get_even, get_odd);

        // iterating based on pid
        for (int i = 0; i < range; i++)
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
                // storing pid_t values in array
                child_arr[i] = getpid();

                // printf("\t\tcheck child array, pid = %u\n", child_arr[i]);

                printf("child created, pid = %u, ppid = %u\n", getpid(), getppid());

                // check height of tree
                // printf("\ttree level = %d\n", tree_height);

                // using signal to pause child process
                kill(child_arr[i], SIGSTOP);
                sleep(1);

                // recursion
                parent_spawns_child(get_even, get_odd, --tree_height);
                exit(0);
            }
            else
            {
                sleep(1);
                // printf("\tid = %u\n", child_arr[j]);
                kill(0, SIGCONT);
            }
        }
        // parent process waiting for all children to finish
        int temp_range = decide_even_odd(getpid(), get_even, get_odd);
        for (int j = 0; j < temp_range; j++)
        {
            retrive_id = wait(&status);
            printf("child pid = %d exited. exit status = %d\n", retrive_id, status / 256);
        }
    }
}
