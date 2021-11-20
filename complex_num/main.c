#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>
#define arb_N 100

typedef struct complex
{
    int real;
    int imaginary;
} complex;

typedef struct data
{
    int cntr;
    pid_t pid;      // process id
    pid_t tid;      // thread id
    pthread_t ptid; // pthreads tid
} data;

struct complex D[arb_N];
struct complex output[arb_N];

void *runner(void *args)
{
    data *p = (data *)args;
    // store data for further use
    p->pid = getpid();
    p->tid = syscall(SYS_gettid);
    p->ptid = pthread_self();

    // apply complex multiplication
    int pos, index1, index2;
    pos = p->cntr;
    index1 = 2 * pos;
    index2 = 2 * pos + 1;

    struct complex z;
    z.real = (D[index1].real * D[index2].real) - (D[index1].imaginary * D[index2].imaginary);
    z.imaginary = (D[index1].real * D[index2].imaginary) - (D[index1].imaginary * D[index2].real);

    output[pos].real = z.real;
    output[pos].imaginary = z.imaginary;

    printf("complex mul: (%d + i%d)*(%d + i%d) = (%d + i%d)\n", D[index1].real, D[index1].imaginary, D[index2].real, D[index2].imaginary, output[pos].real, output[pos].imaginary);

    // return (void *) 1;
    return (p);
}

void create_threads(unsigned int total_threads)
{
    int ret;
    pthread_t *threadIDs = malloc(sizeof(pthread_t) * total_threads);
    // spawn threads
    for (int i = 0; i < total_threads; i++)
    {
        data *dp = malloc(sizeof(data) * total_threads);
        memset(dp, '\0', sizeof(*dp));

        dp->cntr = i;
        ret = pthread_create(&threadIDs[i], NULL, runner, (void *)dp);

        if (ret != 0)
        {
            perror("pthread create error\n");
        }
    }
    // waiting for threads
    for (int i = 0; i < total_threads; ++i)
    {
        data *status;
        ret = pthread_join(threadIDs[i], (void *)&status);
        if (ret != 0)
        {
            perror("pthread join error\n");
        }
        else
        {
            printf("thread no. %d joined, pthreadID=%lu, processID=%d, threadID=%d\n", status->cntr, status->ptid, status->pid, status->tid);
            free(status);
        }
    }
    free(threadIDs);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file is empty, try again\n");
        exit(1);
    }

    int N;
    fscanf(fp, "%d", &N);

    struct complex temp;
    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%d %*c %*c%d", &temp.real, &temp.imaginary);
        D[i] = temp;
    }

    // check stored value
    for (int i = 0; i < N; i++)
    {
        printf("complex num %d: real=%d, imaginary=%d\n", i + 1, D[i].real, D[i].imaginary);
    }

    fclose(fp);

    // creating threads
    create_threads(floor(N / 2));
    return 0;
}