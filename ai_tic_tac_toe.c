#include <stdio.h>
#include <limits.h>

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

char player = 'X';
char ai = 'O';

void drawBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" ");
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
        }
         printf("\n");
    }
    printf("\n\n");
}

int checkWinner(char mark) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==mark && board[i][1]==mark && board[i][2]==mark) return 1;
        if (board[0][i]==mark && board[1][i]==mark && board[2][i]==mark) return 1;
    }
    if (board[0][0]==mark && board[1][1]==mark && board[2][2]==mark) return 1;
    if (board[0][2]==mark && board[1][1]==mark && board[2][0]==mark) return 1;
    return 0;
}

int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 1;
    return 0;
}

int minimax(int depth, int isMax) {
    if (checkWinner(ai)) return 10 - depth;
    if (checkWinner(player)) return depth - 10;
    if (!isMovesLeft()) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = ai;
                    best = (minimax(depth + 1, 0) > best) ? minimax(depth + 1, 0) : best;
                    board[i][j] = temp;
                }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = player;
                    best = (minimax(depth + 1, 1) < best) ? minimax(depth + 1, 1) : best;
                    board[i][j] = temp;
                }
        return best;
    }
}

// AI move
void bestMove() {
    int bestVal = INT_MIN;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = ai;
                int moveVal = minimax(0, 0);
                board[i][j] = temp;

                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }

    board[moveRow][moveCol] = ai;
    printf("AI placed 'O' at position %d\n", (moveRow * 3 + moveCol + 1));
}

// Player move
void playerMove() {
    int move;
    printf("Enter your move (1-9): ");
    scanf("%d", &move);

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        printf("Invalid move! Try again.\n");
        playerMove();
    } else {
        board[row][col] = player;
    }
}

int main() {
    drawBoard();

    while (1) {
        playerMove();
        drawBoard();
        if (checkWinner(player)) {
            printf("You win!\n");
            break;
        }
        if (!isMovesLeft()) {
            printf("It's a draw!\n");
            break;
        }

        bestMove();
        drawBoard();
        if (checkWinner(ai)) {
            printf("AI wins!\n");
            break;
        }
        if (!isMovesLeft()) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
