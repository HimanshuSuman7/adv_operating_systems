#ifndef ASSIGNMENT_PL
#define ASSIGNMENT_PL

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

extern void print_match_preview(int first_team, int second_team);
extern void print_final_score(int first_team, int second_team, int first_goals, int second_goals);
extern int get_rand_goals();
extern void premier_league_board(int N, int total_fixtures, int prem_fixtures[][2]);
extern void simulate_match(int home_team, int away_team, int **total_wins, int **total_loss, int **total_draw, int **goals_scored, int **points);

extern int check_conflict(int home_team, int away_team, int *manager_status);

#endif