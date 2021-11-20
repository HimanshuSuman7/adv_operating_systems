#include "project.h"

void *runner1(void *args)
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

    printf("\tcomplex mul: (%d + i%d)*(%d + i%d) = ", D[index1].real, D[index1].imaginary, D[index2].real, D[index2].imaginary);

    struct complex z;
    z.real = (D[index1].real * D[index2].real) - (D[index1].imaginary * D[index2].imaginary);
    z.imaginary = (D[index1].real * D[index2].imaginary) + (D[index1].imaginary * D[index2].real);

    output[pos].real = z.real;
    output[pos].imaginary = z.imaginary;

    printf("(%d + i%d)\n", output[pos].real, output[pos].imaginary);

    // return (void *) 1;
    return (p);
}

void *runner2(void *args)
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

    printf("\tcomplex mul: (%d + i%d)*(%d + i%d) = ", output[index1].real, output[index1].imaginary, output[index2].real, output[index2].imaginary);

    struct complex z;
    z.real = (output[index1].real * output[index2].real) - (output[index1].imaginary * output[index2].imaginary);
    z.imaginary = (output[index1].real * output[index2].imaginary) + (output[index1].imaginary * output[index2].real);

    output[pos].real = z.real;
    output[pos].imaginary = z.imaginary;

    printf("(%d + i%d)\n", output[pos].real, output[pos].imaginary);

    // return (void *) 1;
    return (p);
}

void *runner3(void *args)
{
    data *p = (data *)args;
    // store data for further use
    p->pid = getpid();
    p->tid = syscall(SYS_gettid);
    p->ptid = pthread_self();

    // apply complex multiplication
    int pos = 0, index;
    index = (p->cntr) - 1;

    printf("\tcomplex mul: (%d + i%d)*(%d + i%d) = ", output[pos].real, output[pos].imaginary, D[index].real, D[index].imaginary);

    struct complex z;
    z.real = (output[pos].real * D[index].real) - (output[pos].imaginary * D[index].imaginary);
    z.imaginary = (output[pos].real * D[index].imaginary) + (output[pos].imaginary * D[index].real);

    output[pos].real = z.real;
    output[pos].imaginary = z.imaginary;

    printf("(%d + i%d)\n", output[pos].real, output[pos].imaginary);

    // return (void *) 1;
    return (p);
}

void create_threads(unsigned int total_threads, int flag)
{
    int ret;
    pthread_t *threadIDs = malloc(sizeof(pthread_t) * total_threads);
    // spawn threads
    for (int i = 0; i < total_threads; i++)
    {
        data *dp = malloc(sizeof(data) * total_threads);
        memset(dp, '\0', sizeof(*dp));

        dp->cntr = i;
        if (flag == 0)
        {
            ret = pthread_create(&threadIDs[i], NULL, runner1, (void *)dp);
        }
        else if (flag == 1)
        {
            ret = pthread_create(&threadIDs[i], NULL, runner2, (void *)dp);
        }
        else
        {
            dp->cntr = flag;
            ret = pthread_create(&threadIDs[i], NULL, runner3, (void *)dp);
        }

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
            printf("==> thread no. %d joined, pthreadID=%lu, processID=%d, threadID=%d\n", status->cntr, status->ptid, status->pid, status->tid);
            free(status);
        }
    }
    free(threadIDs);
}