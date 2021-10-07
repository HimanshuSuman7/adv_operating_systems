#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "helper.h"

int main(int argc, char *argv[])
{
	// taking input from user
	int get_even, get_odd, tree_height;
	sscanf(argv[1], "%d", &get_even);
	sscanf(argv[2], "%d", &get_odd);
	sscanf(argv[3], "%d", &tree_height);
	printf("get_even = %d, get_odd = %d, tree_height = %d\n", get_even, get_odd, tree_height);

	// get pid of parent process
	pid_t root = getpid();
	printf("root pid = %u\n", root);

	// calling to create child processes
	parent_spawns_child(get_even, get_odd, tree_height);
	
    // checking if parent exited
	printf("root process, pid = %u exited\n", getpid());

	return 0;
}
