#include <stdio.h>
#include <stdlib.h>

#define N 8 

int board[N];

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}

int solve(int row) {
    if (row == N) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf(j == board[i] ? "Q " : ". ");
            printf("\n");
        }
        printf("\n");
        return 1;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            if (solve(row + 1))
                return 1;
        }
    }
    return 0;
}

int main() {
    if (!solve(0))
        printf("No solution exists.\n");
    return 0;
}
