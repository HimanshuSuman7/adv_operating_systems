#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void *runner(void *param);
int sum;

int main(int argc, char *argv[]) {
    printf("main thread, pid : %u\n", getpid());
    printf("main thread, tid : %lu\n", pthread_self());

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    printf("main, sum=%d\n", sum);
    return 0;
}

void *runner(void *param) {
    int upper=atoi(param);
    int sum=0;
    printf("new thread, pid = %u\n", getpid());
    printf("new thread, tid = %lu\n", pthread_self());
    if (upper > 0) {
        for (int i=0; i <= upper; i++) {
            sum = sum + i;
        }
    }
    printf("new thread, sum = %d\n", sum);
    pthread_exit(0);
}