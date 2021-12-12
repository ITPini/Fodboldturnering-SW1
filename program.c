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

void read_matches_from_file();
void display_matches();
void calculate_team_stats();
void set_name();
void calculate_team_points();
void display_team_stats();
void calculate_team_goals_scored();
void calculate_team_goals_conceded();
void calculate_goal_difference();
//unsigned int hash();
//int line_numbers_in_file();

int main()
{
    Match match[AMOUNT_OF_MATCHES];
    Team team[AMOUNT_OF_TEAMS];

    read_matches_from_file(match);
    calculate_team_stats(match, team);
    display_team_stats(team);

    return 0;
}

/*int line_numbers_in_file(){
    int count = 0;
    char c;
    FILE *fp = fopen(PATH_TO_FILE, "r");

    if(fp){
        while(c != EOF){
            c = getc(fp);
            if (c == '\n'){
                count++;
            }
        }
    }
    printf("Lines: %d", count + 1);
    return count + 1;
}*/
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

void display_matches(Match *match)
{
    for (int i = 0; i < AMOUNT_OF_MATCHES; i++)
    {
        printf("\n%s     %s %s     %-3s - %-3s     %2d - %-2d     %d",
               match[i].day, match[i].date, match[i].time, match[i].team_1, match[i].team_2,
               match[i].goal_1, match[i].goal_2, match[i].spectator_count);
    }
}

void calculate_team_stats(Match *match, Team *team)
{
    set_name(team);
    calculate_team_points(match, team);
    calculate_team_goals_scored(match, team);
    calculate_team_goals_conceded(match, team);
    calculate_goal_difference(team);
}

void set_name(Team *team)
{
    char team_name[][4] = {"SDR", "FCM", "ACH", "RFC", "LBK", "AaB", "BIF", "FCN", "OB", "FCK", "AGF", "VB"};
    int length = sizeof(team_name) / sizeof(int);

    for (int i = 0; i < length; i++) // AMOUNT_OF_TEAMS?
    {
        strcpy(team[i].name, team_name[i]);
    }
}

void calculate_team_points(Match *match, Team *team)
{
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        team[i].points = 0;
        for (int j = 0; j < AMOUNT_OF_MATCHES; j++)
        {
            if (!strcmp(team[i].name, match[j].team_1) && match[j].goal_1 > match[j].goal_2)
            {
                team[i].points += 3;
            }
            if (!strcmp(team[i].name, match[j].team_2) && match[j].goal_2 > match[j].goal_1)
            {
                team[i].points += 3;
            }
            if (!strcmp(team[i].name, match[j].team_1) && match[j].goal_1 == match[j].goal_2)
            {
                team[i].points += 1;
            }
            if (!strcmp(team[i].name, match[j].team_2) && match[j].goal_2 == match[j].goal_1)
            {
                team[i].points += 1;
            }
        }
    }
}

void calculate_team_goals_scored(Match *match, Team *team)
{
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        team[i].goals_scored = 0;
        for (int j = 0; j < AMOUNT_OF_MATCHES; j++)
        {
            if (!strcmp(team[i].name, match[j].team_1))
            {
                team[i].goals_scored += match[j].goal_1;
            }
            else if (!strcmp(team[i].name, match[j].team_2))
            {
                team[i].goals_scored += match[j].goal_2;
            }
        }
    }
}

void calculate_team_goals_conceded(Match *match, Team *team)
{
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        team[i].goals_conceded = 0;
        for (int j = 0; j < AMOUNT_OF_MATCHES; j++)
        {
            if (!strcmp(team[i].name, match[j].team_1))
            {
                team[i].goals_conceded += match[j].goal_2;
            }
            else if (!strcmp(team[i].name, match[j].team_2))
            {
                team[i].goals_conceded += match[j].goal_1;
            }
        }
    }
}

void calculate_goal_difference(Team *team)
{
    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        team[i].difference = 0;
        team[i].difference = team[i].goals_scored - team[i].goals_conceded;
    }
}

void display_team_stats(Team *team)
{
    printf("\nTEAM | POINTS | GOALS SCORED | GOALS CONCEDED | DIFFERENCE\n");

    for (int i = 0; i < AMOUNT_OF_TEAMS; i++)
    {
        //printf("\n%s: %d", team[i].name, hash(team[i].name));
        printf("\n%4s   %6d   %12d   %14d   %10d", team[i].name, team[i].points, team[i].goals_scored, team[i].goals_conceded, team[i].difference);
    }
    printf("\n");
}

/*unsigned int hash(char *team_name){
    int length = strnlen(team_name, 4);
    unsigned int value = 0;
    for (int i = 0; i < length; i++)
    {
        value += team_name[i];
    }
    return value % 100;
}*/