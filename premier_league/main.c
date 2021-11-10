#include "project.h"

int main(int argc, char *argv[])
{
    // initailize srand only once
    srand(time(NULL));
    // printf("random nums = %d %d\n", get_rand_goals(), get_rand_goals());

    // get file
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("file is empty, try again\n");
        exit(1);
    }

    int N; // total teams
    int total_fixtures;

    // reading data
    fscanf(fp, "%d", &N);
    total_fixtures = N * (N - 1);

    int prem_fixtures[total_fixtures][2]; // [[home0][away0], [home1][away1]]

    for (int i = 0; i < total_fixtures; i++)
    {
        fscanf(fp, "%d %d", &prem_fixtures[i][0], &prem_fixtures[i][1]);
    }

    // closing file
    fclose(fp);

    // now premier board decides
    premier_league_board(N, total_fixtures, prem_fixtures); // kind of parent process

    return 0;
}