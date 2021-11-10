#include "project.h"

void premier_league_board(int N, int total_fixtures, int prem_fixtures[total_fixtures][2])
{
    // checking premier league fixtures from new array
    for (int i = 0; i < total_fixtures; i++)
    {
        printf("fixture %d: Team %d vs Team %d\n", i + 1, prem_fixtures[i][0], prem_fixtures[i][1]);
    }

    // as per league table
    int manager_status[N];
    int match_status[total_fixtures]; // keeing track of matches that have already been played
    int total_wins[N];
    int total_loss[N];
    int total_draw[N];
    int goals_scored[N];
    int points[N]; // maintain points table

    // starting premier league season, so setting params to zero
    // manager 0 means not playing, 1 means busy playing a game
    for (int i = 0; i < N; i++)
    {
        manager_status[i] = 0;
        match_status[i] = 0;
        total_wins[i] = 0;
        total_loss[i] = 0;
        total_draw[i] = 0;
        goals_scored[i] = 0;
        points[i] = 0;
    }

    // REPORTING: BUG
    // using an alternative approach, save pids to file and then reading
    pid_t track_manager_pid[11] = {0};
    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            // process not created
            perror("fork failed.\n");
            exit(0);
        }
        if (pid == 0)
        {
            track_manager_pid[i] = getpid();
            printf("child created, pid = %u, ppid = %u\n", getpid(), getppid());
            kill(track_manager_pid[i], SIGSTOP);
            sleep(1);
        }
    }
    sleep(1);

    // simulating matches
    int go_ahead, home_team, away_team;
    for (int i = 0; i < total_fixtures; i++)
    {
        home_team = prem_fixtures[i][0];
        away_team = prem_fixtures[i][1];
        // go_ahead = check_conflict(home_team, away_team, manager_status);
        simulate_match(home_team, away_team, &total_wins, &total_loss, &total_draw, &goals_scored, &points);
    }
}