#include "project.h"

void simulate_match(int home_team, int away_team, int **total_wins, int **total_loss, int **total_draw, int **goals_scored, int **points)
{
    int home_goals = get_rand_goals(), away_goals = get_rand_goals();
    goals_scored[home_team - 1] = goals_scored[home_team - 1] + home_goals;
    goals_scored[away_team - 1] = goals_scored[away_team - 1] + away_goals;
    print_match_preview(home_team, away_team);
    print_final_score(home_team, away_team, home_goals, away_goals);
    if (home_goals > away_goals)
    {
        total_wins[home_team - 1] = total_wins[home_team - 1] + 1;
        total_loss[away_team - 1] = total_loss[away_team - 1] + 1;
        points[home_team - 1] = points[home_team - 1] + 3;
    }
    else if (home_goals < away_goals)
    {
        total_wins[away_team - 1] = total_wins[away_team - 1] + 1;
        total_loss[home_team - 1] = total_loss[home_team - 1] + 1;
        points[away_team - 1] = points[away_team - 1] + 3;
    }
    else
    {
        total_draw[away_team - 1] = total_draw[away_team - 1] + 1;
        total_draw[home_team - 1] = total_draw[home_team - 1] + 1;
        points[home_team - 1] = points[home_team - 1] + 1;
        points[away_team - 1] = points[away_team - 1] + 1;
    }
    sleep(3);
}

int check_conflict(int home, int away, int *manager_status)
{
    if ((manager_status[home] == 0) && (manager_status[away] == 0))
    {
        return 1;
    }
    return 0;
}

int get_rand_goals()
{
    return (rand() % 6);
}

void print_match_preview(int first_team, int second_team)
{
    printf("Starting match: Team %d vs Team %d\n", first_team, second_team);
}

void print_final_score(int first_team, int second_team, int first_goals, int second_goals)
{
    printf("Starting match: Team %d vs Team %d,\tResult: %d-%d\n", first_team, second_team, first_goals, second_goals);
}