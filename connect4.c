#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

// sets the board empty spaces
void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

// prints the board with vertical lines
void printBoard() {
    printf("\n");
    // print each row of the board
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    
    }
    // print column indexes underneath for player reference
    printf(" ");
    for (int j = 0; j < COLS; j++) {
        printf(" %d  ", j);
    }
    printf("\n");
}

bool dropPiece(int col, char piece) {
    // if invalid col or top already full then fail
    if (col < 0 || col >= COLS || board[0][col] != ' ') {
        return false;
    }
    // start from bottom of the col upwards to find first empty spot
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = piece;
            return true;
        }
    }
    return false;
}

bool checkWin(char piece) {
    // check horizontal 4 in a row
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == piece && board[i][j+1] == piece && board[i][j+2] == piece && board[i][j+3] == piece) {
                return true;
            }
        }
    }
    // check vertical 4 in a row
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == piece && board[i+1][j] == piece && board[i+2][j] == piece && board[i+3][j] == piece) {
                return true;
            }
        }
    }
    // check diagonal down-right
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == piece && board[i+1][j+1] == piece && board[i+2][j+2] == piece && board[i+3][j+3] == piece) {
                return true;
            }
        }
    }
    // check diagonal down-left
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 3; j < COLS; j++) {
            if (board[i][j] == piece && board[i+1][j-1] == piece && board[i+2][j-2] == piece && board[i+3][j-3] == piece) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    char playAgain = 'y';

    // loop while player want to play again
    while (playAgain == 'y' || playAgain == 'Y') {
        initializeBoard();
        char currentPlayer = 'X';
        int moves = 0;
        bool gameOver = false;

        printf("Connect 4 Console Game\n");
        printBoard();

        // main gameplay loop while the game is not finished
        while (!gameOver) {
            int col;
            printf("Player %c, enter the column (0-%d) to drop your piece: ", currentPlayer, COLS - 1);
            // get user input column
            if (scanf("%d", &col) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // flush bad input
                continue;
            }
            // try to drop the piece if invalid retry
            if (!dropPiece(col, currentPlayer)) {
                printf("Invalid move. Try again.\n");
                continue;
            }

            moves++;
            printBoard();

            // check if current player won or if draw happened
            if (checkWin(currentPlayer)) {
                printf("Player %c wins!\n", currentPlayer);
                gameOver = true;
            } else if (moves >= ROWS * COLS) {
                printf("It's a draw!\n");
                gameOver = true;
            } else {
                // switch turns
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // ask if want to play again
        printf("Do you want to play again? (y/n): ");
        while (getchar() != '\n'); // flush input buffer
        playAgain = getchar();
    }

    printf("Thanks for playing!\n");
    return 0;
}
