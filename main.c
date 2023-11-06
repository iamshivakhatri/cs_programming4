// Shiva Khatri
// Programming Assignment 4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// Function prototypes
char* findHaven(char* player, char* board, int size);
char* chuteLadder(char* player);
char* move(char* player, char* otherPlayer, int playerNumber, char* board, int size);
void output(char* board, char* player1, char* player2, FILE* outFile);

int main() {
    // Initialize the board and players
    char board[SIZE]="  mHk tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB ";

    char* player1 = board; // Initialize player 1 pointer
    char* player2 = board; // Initialize player 2 pointer



    // Open an output file
    FILE* outFile = fopen("output.txt", "w");
    
    // Seed the random number generator
    srand(time(NULL));

    // Main game loop
    while (1) {
        // Move player 1 and player 2
        player1 = move(player1, player2, 1, board, SIZE);
        player2 = move(player2, player1, 2, board, SIZE);

        // Output the current board to the file
        output(board, player1, player2, outFile);

        // Check if either player has won
        if (player1 >= board + SIZE || player2 >= board + SIZE) {
            break;
        }
    }

    // Determine and output the winner
    if (player1 > player2) {
        printf("Player 1 wins!\n");
    } else if (player2 > player1) {
        printf("Player 2 wins!\n");
    } else {
        printf("It's a tie!\n");
    }

    // Close the output file
    fclose(outFile);
    
    return 0;
}



char* findHaven(char* player, char* board, int size) {
    // Check if the player is outside the board
  //  printf("In findhaven, Player landed on the character %c\n", *player);
    // only B or F will be selected
    if (*player == 'B'){
          // Search backward for the previous 'H'
    while (player >= board && *player != 'H') {
        if (player == board) {
            player = board;
            return player;
        }
        player--;
    }
        
    }else {
         // Search forward for the next 'H'
        while (player <= board + size && *player != 'H') {
        if (player == board + size) {
            player = board + size;
            return player;
        }
        player++;
    }
    }

    *player = '*';  // Mark the haven as '*' as player must have been on H as program didn't returned and reached this part

    return player;


}


char* chuteLadder(char* player) {
  //  printf("In chuteladder, Player landed on the character %c\n", *player);
    char currentSquare = *player; //change
   
    
    char* tempPlayer = player;  // Create a temporary pointer to remember the current location

    // Calculate the number of steps to move
    int distance = currentSquare - 'n';
   player = player + distance;
    // Reset the letter as stored in the temp pointer to '-' (empty square) on the original board
    *tempPlayer = '-';
    return player;
}



char* move(char* player, char* otherPlayer, int playerNumber, char* board, int size) {
   

    // Generate a random move from 1 to 6
    int move = rand() % 6 + 1;
    int movement;
    int point;
    char message[60];
    char location;

    message[0] = '\0';
  

    // Move the player by the generated amount
    player = player + move ;
    point = player - board;

    // Check if the player is still within the bounds of the board
    if (player >= board && player < board + size) {
        // Check if the player has landed on a chute, ladder, 'B', or 'F'
        location = *(player); // change
        
        if (location >= 'a' && location <= 'm') {
            // Handle chutes (backward movement)
            player = chuteLadder(player);
            movement = player - board;
            sprintf(message, "Player landed on a chute and slid down to %d", movement);

            
        } else if (location >= 'o' && location <= 'z') {
            // Handle ladders (forward movement)
            player = chuteLadder(player);
            movement = player - board;
            sprintf(message, "Player landed on a ladder and climbed up to %d", movement);
        } else if (location == 'B') {
            // Handle 'B' and 'F'
            player = findHaven(player-1, board, size);
            movement = player - board;
            sprintf(message, "Player landed on a B, move backward to %d", movement);
        } else if (location == 'F'){
            player = findHaven(player, board, size);
            movement = player - board;
            sprintf(message, "Player landed on a F, and moved to %d", movement);
        }

        // Check for collisions with the other player
        if (player == otherPlayer) {
           // printf("Collision! Player %d moves back 1 square\n", playerNumber);
            player = player - 1;
            movement = player - board; 
            sprintf(message, "Player landed on the other player and moved back to %d", movement);
        }

        // Output the result
       // printf("Player %d rolled %d and is moved to %d\n", playerNumber, move, player - board);
    } 

        if (message[0] == '\0') {
        // The char array is empty
          printf("Player %d rolled %d and is moved to %d\n",playerNumber,move, point );
        } else {
            printf("Player %d rolled %d and is moved to %d and %s\n",playerNumber,move, point, message);
        }
    
   


    return player;
}

void output(char* board, char* player1, char* player2, FILE* outFile) {
    // Loop through the board and print each character
    for (char* current = board; *current != '\0'; current++) {
        if (current == player1) {
            // Print '1' if it's the location of player 1
            fputc('1', outFile);
        } else if (current == player2) {
            // Print '2' if it's the location of player 2
            fputc('2', outFile);
        } else {
            // Print the current character from the board
            fputc(*current, outFile);
        }
    }

    // Add a newline character at the end of the line
    fputc('\n', outFile);
}
