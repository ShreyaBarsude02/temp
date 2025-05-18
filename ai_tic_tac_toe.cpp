#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

char player = 'X';
char ai = 'O';

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
    cout << "\n\n";
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

int minimax(int depth, bool isMax) {
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
                    best = max(best, minimax(depth + 1, false));
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
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = temp;
                }
        return best;
    }
}

void bestMove() {
    int bestVal = INT_MIN;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = ai;
                int moveVal = minimax(0, false);
                board[i][j] = temp;

                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }

    board[moveRow][moveCol] = ai;
    cout << "AI placed 'O' at position " << (moveRow * 3 + moveCol + 1) << endl;
}

void playerMove() {
    int move;
    cout << "Enter your move (1-9): ";
    cin >> move;

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        cout << "Invalid move! Try again.\n";
        playerMove();
    } else {
        board[row][col] = player;
    }
}

int main() {
    drawBoard();

    while (true) {
        playerMove();
        drawBoard();
        if (checkWinner(player)) {
            cout << "You win!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }

        bestMove();
        drawBoard();
        if (checkWinner(ai)) {
            cout << "AI wins!\n";
            break;
        }
        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
