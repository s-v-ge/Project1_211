/*
      Program 1: Wumpus, version 1 (fixed size array)
      Player, wumpus, and both pits start in random rooms.
      Player can move to rooms adjacent to their room.
      Player must guess the Wumpus' room to win.
*/
#include <ctype.h>   // for tolower
#include <stdbool.h> // for booleans
#include <stdio.h>
#include <stdlib.h> // for srand
#include <time.h>   // for time functions

//--------------------------------------------------------------------------------
// displayCave(): This function displays the map, shows which rooms are adjacent
//                to each room. Displayed when player enters 'p'
//--------------------------------------------------------------------------------
void displayCave() {
  printf("\n");
  printf("       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
}
//--------------------------------------------------------------------------------
// displayInstructions(): This function displays the instructions, the rules,
//                        and the commands the player can use.
//--------------------------------------------------------------------------------
void displayInstructions() {
  displayCave();
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' to guess which room Wumpus is in, to win or lose the "
         "game!         \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
}
//--------------------------------------------------------------------------------
// roomTaken(): This is a helper function for the random room generation,
//              checks all previous rooms if they are the same as current room
//       input: the location array as a pointer, the number of rooms to check
//      output: true if there is a duplicate room, false if there is not.
//--------------------------------------------------------------------------------
bool roomTaken(int *arr, int k) {
  for (int i = 0; i < k; i++) {
    if (arr[i] == arr[k])
      return true;
  }
  return false;
}
//--------------------------------------------------------------------------------
// generateGame(): This function generates the room numbers of all notable rooms
//                 Notable rooms: Player, Wumpus, Pit1/2
//                 Uses roomTaken() to generate non duplicate room numbers
//          input: the location array as a pointer
//         output: updates location array with room numbers of notable rooms
//--------------------------------------------------------------------------------
void generateGame(int *arr) {
  for (int i = 0; i < 4; i++) {
    arr[i] = rand() % 20 + 1;
    while (i > 0 && roomTaken(arr, i)) {
      arr[i] = rand() % 20 + 1;
    }
  }
}
//--------------------------------------------------------------------------------
// resetGame(): This function resets the room numbers of the notable rooms
//              User enters numbers for each room
//       input: the location array as a pointer
//      output: updates location array with user generated room numbers
//--------------------------------------------------------------------------------
void resetGame(int *arr) {
  printf("Enter the room locations (1..20) for player, wumpus, pit1, and pit2: "
         "\n\n");
  scanf(" %d", &arr[3]);
  scanf(" %d", &arr[2]);
  scanf(" %d", &arr[0]);
  scanf(" %d", &arr[1]);
}
//--------------------------------------------------------------------------------
//     cheat(): This function displays the room numbers of each notable room.
//              Alligns room number below room contents
//       input: the location array as a pointer
//      output: displays contents of location array
//--------------------------------------------------------------------------------
void cheat(int *arr) {
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2  \n"
         "%4d %7d %5d %5d \n\n",
         arr[3], arr[2], arr[0], arr[1]);
}
//--------------------------------------------------------------------------------
//     guess(): This function is called when user wants to guess wumpus location
//              player wins if correct, else loses
//       input: the location array as a pointer
//      output: displays whether or not user wins/loses
//--------------------------------------------------------------------------------
void guess(int *arr) {
  int roomGuess = 0;
  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf(" %d", &roomGuess);

  if (roomGuess == arr[2]) {
    printf("You won!\n");
  } else {
    printf("You lost.\n");
  }
}
//--------------------------------------------------------------------------------
//  checkAdj(): This function checks whether the players room is adjacent to
//              a another room.
//       input: 2 room numbers, pointer to adjacenty array
//      output: true if room 1 is adjacent to room 2, else false
//--------------------------------------------------------------------------------
bool checkAdj(int room1, int room2, int *mat) {
  for (int i = 0; i < 3; i++) {
    if (room1 == mat[(room2 - 1) * 3 + i])
      return true;
  }
  return false;
}
//--------------------------------------------------------------------------------
// checkRoom(): This function determines what to do when player enters a room.
//       input: the location array as a pointer, pointer to adj. matrix, end
//       bool
//      output: sets bool to True if game is over, else displays room info
//--------------------------------------------------------------------------------
void checkRoom(int *arr, int *mat, bool *exit) {
  if (arr[3] == arr[0] || arr[3] == arr[1]) {
    printf("Aaaaaaaaahhhhhh....   \n");
    printf("    You fall into a pit and die. \n");
    *exit = true;
  } else if (arr[3] == arr[2]) {
    if (arr[2] % 2 != 0) {
      printf("You hear a slithering sound, as the Wumpus slips away. \n"
             "Whew, that was close! \n");
      arr[2] = mat[(arr[2] - 1) * 3];
    } else {
      printf(
          "You briefly feel a slimy tentacled arm as your neck is snapped. \n"
          "It is over.\n");
      *exit = true;
    }
  }
  if (!*exit) {
    printf("You are in room %d. ", arr[3]);
    if (checkAdj(arr[3], arr[2], mat)) {
      printf("You smell a stench. ");
    }
    if (checkAdj(arr[3], arr[0], mat) || checkAdj(arr[3], arr[1], mat)) {
      printf("You feel a draft. ");
    }
    printf("\n\n");
  }
}
//--------------------------------------------------------------------------------
// movePlayer(): This is a helper function for the random room generation,
//              checks all previous rooms if they are the same as current room
//        input: the location array as a pointer, pointer to adj. matrix, count
//       output: updates player location with desired move if adjacent and
//       count++,
//               else displays move is invalid
//--------------------------------------------------------------------------------
void movePlayer(int *arr, int *mat, int *count) {
  int toRoom = 0;
  scanf(" %d", &toRoom);
  if (checkAdj(toRoom, arr[3], mat)) {
    arr[3] = toRoom;
    *count += 1;
  } else {
    printf("Invalid move.  Please retry. \n");
  }
}
//--------------------------------------------------------------------------------

int main(void) {
  // Seed the random number generator.  Change seed to time(0) to change
  // output each time.
  // srand(time(0));
  srand(1);

  char userIn = 'a';
  bool gameover = false;
  int count = 1;
  int toRoom = 0;
  int locations[4] = {0, 0, 0, 0};
  // matrix that stores all the adjacent rooms
  // adjMat[currentRoom-1] = {adjacent rooms}
  int adjMat[20][3] = {{2, 5, 8},    {1, 3, 10},  {2, 4, 12},   {3, 5, 14},
                       {1, 4, 6},    {5, 7, 15},  {6, 8, 17},   {1, 7, 9},
                       {8, 10, 18},  {2, 9, 11},  {10, 12, 19}, {3, 11, 13},
                       {12, 14, 20}, {4, 13, 15}, {6, 14, 16},  {15, 17, 20},
                       {7, 16, 18},  {9, 17, 19}, {11, 18, 20}, {13, 16, 19}};
  generateGame(locations);

  while (userIn != 'x') {

    checkRoom(locations, adjMat, &gameover);

    // prompt user to enter command
    if (!gameover) {
      printf("%d. Enter your move (or 'D' for directions): ", count);
      scanf(" %c", &userIn);
      userIn = tolower(userIn);
    }
    if (gameover)
      userIn = 'x';
    if (userIn == 'r') {
      resetGame(locations);
    } else if (userIn == 'c') {
      cheat(locations);
    } else if (userIn == 'd') {
      displayInstructions();
    } else if (userIn == 'p') {
      displayCave();
    } else if (userIn == 'g') {
      guess(locations);
      userIn = 'x';
    } else if (userIn == 'm') {
      movePlayer(locations, adjMat, &count);
    }

    if (userIn == 'x') {
      printf("\nExiting Program ...\n");
    }
  }
  return 0;
}
