#include "project.h"

struct complex D[arb_N];
struct complex output[arb_N];

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

    printf("==> parent thread, pthreadID=%lu, processID=%d, threadID=%ld\n", pthread_self(), getpid(), syscall(SYS_gettid));

    // creating threads
    int total_threads = floor(N / 2);
    create_threads(total_threads, 0);

    // now, working with output array
    total_threads = floor(total_threads / 2);
    while (total_threads >= 1)
    {
        create_threads(total_threads, 1);
        total_threads = floor(total_threads / 2);
    }

    if (N % 2 == 1) {
        create_threads(1, N);
    }

    return 0;
}