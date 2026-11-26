#include <stdio.h>

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

void drawBoard(void) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkWin(void) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

int makeMove(int choice, char mark) {
    if (choice < 1 || choice > 9) {
        return 0; // Invalid range
    }

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    // Check if cell is still an unplayed digit
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = mark;
        return 1;
    }
    
    return 0; // Cell already occupied
}

int main(void) {
    int turn = 0;
    int choice;
    int winner = 0;

    printf("=== Tic-Tac-Toe ===\n");

    while (turn < 9) {
        drawBoard();

        char currentMark = (turn % 2 == 0) ? 'X' : 'O';
        int playerNum = (turn % 2 == 0) ? 1 : 2;

        printf("Player %d (%c), enter a number (1-9): ", playerNum, currentMark);
        
        // Handle non-integer input safely
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear buffer
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }

        if (!makeMove(choice, currentMark)) {
            printf("Invalid move! Spot is either taken or out of bounds.\n");
            continue;
        }

        if (checkWin()) {
            winner = playerNum;
            break;
        }

        turn++;
    }

    drawBoard();

    if (winner != 0) {
        printf("Congratulations! Player %d wins!\n", winner);
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}