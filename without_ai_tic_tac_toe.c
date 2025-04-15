#include<stdio.h>

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char current_marker;
int current_player;

void drawBoard(){
    printf("\n");
    for(int i=0; i<3; i++){
        printf(" ");
        for(int j=0; j<3; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int placeMarker(int slot){
    int row = (slot - 1)/3;
    int col = (slot - 1)%3;

    if(slot<1 || slot >9){
        return 0;
    }

    if(board[row][col] != 'X' && board[row][col] != 'O'){
        board[row][col] = current_marker;
        return 1;
    }

    return 0;
}

void swapPlayerAndMarker(){
    current_marker = (current_marker == 'X') ? 'O' : 'X';
    current_player = (current_player == 1)? 2 : 1;
}

int checkWinner(){

    for (int i = 0; i < 3; i++) {
        if (board[i][0]==board[i][1] && board[i][1]==board[i][2])
            return current_player;
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i])
            return current_player;
    }

    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
        return current_player;
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
        return current_player;

    return 0;
}

void game(){
    printf("Player 1 choose your marker (X or O): ");
    scanf("%c",&current_marker);
    current_player = 1;

    for(int i=0; i<9; i++){
        int slot;
        printf("Player %d [%c] enter your slot (0-9): ", current_player, current_marker);
        scanf("%d", &slot);

        if(!placeMarker(slot)){
            printf("Invalid move! Please try again.\n");
            i--;
            continue;
        }

        drawBoard();

        if(checkWinner()){
            printf("Player %d wins!\n", current_player);
            return;
        }

        swapPlayerAndMarker();
    }
}

int main(){
    printf("\t\t\t Game Started\n");
    game();
    return 0;
}