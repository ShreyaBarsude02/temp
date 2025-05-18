#include <iostream>
#include <cstdlib> // for abs()

using namespace std;

const int N = 8;
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
            for (int j = 0; j < N; j++) {
                if (j == board[i])
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
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
        cout << "No solution exists.\n";
    return 0;
}
