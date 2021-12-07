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
} Team;


void read_matches_from_file();
void display_matches();
void calculate_team_stats();

int main(){
    Match match[AMOUNT_OF_MATCHES];
    Team team[AMOUNT_OF_TEAMS];

    read_matches_from_file(match);
    display_matches(match);
    printf("\n");

    return 0;
}

void read_matches_from_file(Match match[]){
    FILE *fp = fopen(PATH_TO_FILE, "r");

    if(fp){
        Match new_match;
        int number = 0;
        
        while (fscanf(fp, "%s     %s %s     %s - %s     %d - %d     %d", 
            new_match.day, new_match.date, new_match.time, new_match.team_1, new_match.team_2, 
            &(new_match.goal_1), &(new_match.goal_2), &(new_match.spectator_count)) == 8){

            match[number] = new_match;
            number++;
        }
        fclose(fp);
    }
}

void display_matches(Match *match){
    for(int i = 0; i < AMOUNT_OF_MATCHES; i++){
        printf("\n%s     %s %s     %-3s - %-3s     %2d - %-2d     %d",
        match[i].day, match[i].date, match[i].time, match[i].team_1, match[i].team_2,
        match[i].goal_1, match[i].goal_2, match[i].spectator_count);
    }
}