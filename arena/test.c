#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void parent_spawns_child(int, int, int);

int child_arr[200];

int main(int argc, char *argv[])
{
	// taking input from user
	int get_even, get_odd, tree_height;
	sscanf(argv[1], "%d", &get_even);
	sscanf(argv[2], "%d", &get_odd);
	sscanf(argv[3], "%d", &tree_height);
	printf("get_get_even = %d, get_odd = %d, tree_height = %d\n", get_even, get_odd, tree_height);

	// get pid of parent process
	pid_t root = getpid();
	printf("root pid = %u\n", root);
	// calling to create child processes
	parent_spawns_child(get_even, get_odd, tree_height);
	// checking if parent exited
	printf("root process, pid = %u exited\n", getpid());

	return 0;
}

void parent_spawns_child(int get_even, int get_odd, int tree_height)
{
	int status = 0, range = get_even;
	int retrive_id;
	int temp_range;

	// base condition
	if (tree_height > 0)
	{
		// assign get_even/get_odd to n
		if (getpid() % 2)
			range = get_odd;

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
				
				// printf("\t\thimanshu id = %u\n", child_arr[i]);
				
				printf("child created, pid = %u, ppid = %u\n", getpid(), getppid());

				// check height of tree
				// printf("level = %d\n", tree_height);

				// using signal
				kill(child_arr[i], SIGSTOP);
				sleep(1);

				// recursion
				parent_spawns_child(get_even, get_odd, --tree_height);
				exit(0);
			}
			else
			{
				sleep(1);
				for (int j = 0; j < 1; j++)
				{
					// printf("\tid = %u\n", child_arr[j]);
					kill(0, SIGCONT);
				}
			}
		}
		// parent process waiting for children
		temp_range = get_even;
		if (getpid() % 2)
			temp_range = get_odd;
		for (int j = 0; j < temp_range; j++)
		{
			retrive_id = wait(&status);
			printf("child pid = %d exited. exit status = %d\n", retrive_id, status / 256);
		}
	}
}