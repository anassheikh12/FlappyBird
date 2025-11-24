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

// prints the board with vertical lines and horizontal separators
void printBoard() {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("|");
        for (int j = 0; j < COLS; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");

        for (int k = 0; k < COLS * 4+1; k++) {
            printf("-");
        }
        printf("\n");
    }
    // print column number for player reference
    printf(" ");
    for (int j = 0; j < COLS; j++) {
        printf(" %d  ", j);
    }
    printf("\n");
}

bool dropPiece(int col, char piece) {
    if (col < 0 || col >= COLS || board[0][col] != ' ') {
        return false;
    }
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = piece;
            return true;
        }
    }
    return false;
}

bool checkWin(char piece) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == piece && board[i][j+1] == piece && board[i][j+2] == piece && board[i][j+3] == piece) {
                return true;
            }
        }
    }
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == piece && board[i+1][j] == piece && board[i+2][j] == piece && board[i+3][j] == piece) {
                return true;
            }
        }
    }
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == piece && board[i+1][j+1] == piece && board[i+2][j+2] == piece && board[i+3][j+3] == piece) {
                return true;
            }
        }
    }
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

    while (playAgain == 'y' || playAgain == 'Y') {
        initializeBoard();
        char currentPlayer = 'X';
        int moves = 0;
        bool gameOver = false;

        printf("Connect 4 Console Game\n");
        printBoard();

        while (!gameOver) {
            int col;
            printf("Player %c, enter the column (0-%d) to drop your piece: ", currentPlayer, COLS - 1);
            if (scanf("%d", &col) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // flush bad input
                continue;
            }
            if (!dropPiece(col, currentPlayer)) {
                printf("Invalid move. Try again.\n");
                continue;
            }

            moves++;
            printBoard();

            if (checkWin(currentPlayer)) {
                printf("Player %c wins!\n", currentPlayer);
                gameOver = true;
            } else if (moves >= ROWS * COLS) {
                printf("It's a draw!\n");
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        printf("Do you want to play again? (y/n): ");
        while (getchar() != '\n');
        playAgain = getchar();
    }

    printf("Thanks for playing!\n");
    return 0;
}
