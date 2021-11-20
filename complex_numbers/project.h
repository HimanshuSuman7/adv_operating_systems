#ifndef ASSIGNMENT_PL
#define ASSIGNMENT_PL

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

extern struct complex D[arb_N];
extern struct complex output[arb_N];

extern void *runner1(void *args);
extern void *runner2(void *args);
extern void *runner3(void *args);
extern void create_threads(unsigned int total_threads, int flag);

#endif