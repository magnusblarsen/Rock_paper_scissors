#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Value { Rock, Paper, Scissors, VALUE_LENGTH = 3 };

// Returns the number for the winning player (1 or 2) or returns 0 if noone won
int determine_winner(enum Value player_1, enum Value player_2) { 
  if (player_1 == player_2) { return 0; };

  if ((player_1 == Rock && player_2 == Scissors) || (player_1 == Paper && player_2 == Rock) || (player_1 == Scissors && player_2 == Paper)) {
    return 1;
  }
  return 2;
}

int singleplayer() {
  // generate random number
  srand(time(NULL));
  int random_number = rand() % VALUE_LENGTH;

  printf("Choose between rock (r), paper (p) or scissors (s), by typing one of the respective characters\n");

  char player_choice;
  //TODO: Have map from character to enum value and look up

  scanf("%c", &player_choice);
  printf("player: %c\n", player_choice);

  int winner = determine_winner(player_choice, random_number);

  switch (winner) {
  case 0:
    printf("nobody won...");
    break;
  case 1:
    printf("yay you won!");
    break;
  case 2:
    printf("The computer won...");
    break;
  default:
    abort();
  }

  return 0;
}

int main(int argc, char **argv) {
  int multiplayer_flag = 0;
  int singleplayer_flag = 0;
  int c;

  // Use options for gamemode just to try getopt out.
  opterr = 0;

  while ((c = getopt(argc, argv, "ms")) != -1) {
    switch (c) {
    case 'm':
      multiplayer_flag = 1;
      break;
    case 's':
      singleplayer_flag = 1;
      break;
    case '?':
      fprintf(stderr, "Unknown option '-%c'\n", optopt);
      return 1;
    default:
      abort();
    }
  }
  if ((multiplayer_flag == 1 && singleplayer_flag == 1) ||
      (multiplayer_flag == 0 && singleplayer_flag == 0)) {
    fprintf(stderr, "You need to choose a single gamemode\n");
    return 1;
  }

  if (singleplayer_flag == 1) {
    singleplayer();
  }
  return 0;
}
