/*
Navn: Marcelino Patrick Pini
Email: mpini21@student.aau.dk
Gruppe: Gruppe 8
Studieretning: Software
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PATH_TO_FILE "kampe-2020-2021.txt"
#define AMOUNT_OF_MATCHES 132
#define AMOUNT_OF_TEAMS 12

typedef struct
{
    char day[4];
    char date[6];
    char time[6];
    char team_1[4];
    char team_2[4];
    int goal_1;
    int goal_2;
    int spectator_count;
} Match;

typedef struct
{
    char name[4];
    int points;
    int goals_scored;
    int goals_conceded;
    int difference;
} Team;

void read_matches_from_file(Match match[]);
void calculate_team_stats(Match *match, Team *team);
int calculate_team_points(Match *match, Team *team, int n);
int calculate_team_goals_scored(Match *match, Team *team, int n);
int calculate_team_goals_conceded(Match *match, Team *team, int n);
int compare(const void *a, const void *b);
void display_team_stats(Team *team);

int main()
{
    Match match[AMOUNT_OF_MATCHES];
    Team team[AMOUNT_OF_TEAMS];

    read_matches_from_file(match);
    calculate_team_stats(match, team);
    display_team_stats(team);

    return 0;
}

void read_matches_from_file(Match match[])
{
    FILE *fp = fopen(PATH_TO_FILE, "r");

    if (fp)
    {
        Match new_match;
        int number = 0;

        while (fscanf(fp, "%s     %s %s     %s - %s     %d - %d     %d",
                      new_match.day, new_match.date, new_match.time, new_match.team_1, new_match.team_2,
                      &(new_match.goal_1), &(new_match.goal_2), &(new_match.spectator_count)) == 8)
        {

            match[number] = new_match;
            number++;
        }
        fclose(fp);
    }
}

void calculate_team_stats(Match *match, Team *team)
{
    char team_name[][4] = {"SDR", "FCM", "ACH", "RFC", "LBK", "AaB", "BIF", "FCN", "OB", "FCK", "AGF", "VB"};
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        strcpy(team[i].name, team_name[i]);
        team[i].points = calculate_team_points(match, team, i);
        team[i].goals_scored = calculate_team_goals_scored(match, team, i);
        team[i].goals_conceded = calculate_team_goals_conceded(match, team, i);
        team[i].difference = team[i].goals_scored - team[i].goals_conceded;
    }
    qsort(team, AMOUNT_OF_TEAMS, sizeof(Team), compare);
}

int calculate_team_points(Match *match, Team *team, int n)
{
    int points = 0;
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++)
    {
        if ((!strcmp(team[n].name, match[i].team_1) && match[i].goal_1 > match[i].goal_2) ||
            (!strcmp(team[n].name, match[i].team_2) && match[i].goal_2 > match[i].goal_1))
        {
            points += 3;
        } 
        else if ((!strcmp(team[n].name, match[i].team_1) && match[i].goal_1 == match[i].goal_2) ||
                 (!strcmp(team[n].name, match[i].team_2) && match[i].goal_2 == match[i].goal_1))
        {
            points += 1;   
        }
    }
    return points;
}

int calculate_team_goals_scored(Match *match, Team *team, int n)
{
    int scored = 0;
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++)
    {
        if (!strcmp(team[n].name, match[i].team_1))
        {
            scored += match[i].goal_1;
        }
        else if (!strcmp(team[n].name, match[i].team_2))
        {
            scored += match[i].goal_2;
        }
    }
    return scored;
}

int calculate_team_goals_conceded(Match *match, Team *team, int n)
{
    int conceded = 0;
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++)
    {
        if (!strcmp(team[n].name, match[i].team_1))
        {
            conceded += match[i].goal_2;
        }
        else if (!strcmp(team[n].name, match[i].team_2))
        {
            conceded += match[i].goal_1;
        }
    }
    return conceded;
}

int compare(const void *a, const void *b){
    Team *team1 = (Team *) a;
    Team *team2 = (Team *) b;

    int result = team2->points - team1->points;

    /* Compare difference if points is same */
    if (team1->points == team2->points)
    {
        result = team2->difference - team1->difference;
    }
    return result;
}

void display_team_stats(Team *team)
{
    printf("\nTEAM | POINTS | GOALS SCORED | GOALS CONCEDED | DIFFERENCE\n");

    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        printf("\n%4s   %6d   %12d   %14d   %10d", team[i].name, team[i].points, team[i].goals_scored, team[i].goals_conceded, team[i].difference);
    }
    printf("\n");
}