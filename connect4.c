//Connect 4 - CMPS 270
//alice jojo
//ryan

#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>
#include <stdlib.h>

void init();
void gameBoard();
char getCode();
void playerMove();
bool insert();
void playername();
void flipCoin();
void askplayername();

char player1[10];
char player2[10];

const int rows = 6;
const int columns = 7;
char board[6][7];

typedef enum coin {HEADS, TAILS} coin; //here we're making a synonym "coin" for enum coin


typedef enum Color {Empty = 0, Red = 1 , Yellow = 2} Color;
Color player1Color;
Color player2Color;
 


 char getCode(Color convert){
        if (convert == 0){
            return '0';
        }
        else if (convert == 1){
            return 'R';
        }
        else {
            return 'Y';
        }
    }
   
    

void init(){
    printf("----------------------------- \n");
    for (int i = 0; i < rows; i++){
        for(int j =1; j <= columns; j++){
            board[i][j] = '0';
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("----------------------------- \n");
}


void gameBoard(){
    printf("-----------------------------  \n");
    for(int i = 0; i < rows; i++){
        for(int j = 1; j <= columns; j++){
            printf("| %c ", board[i][j]);
        }  
        printf("|\n");
    }
    printf("-----------------------------  \n");

}
void askplayername() {

    printf("Welcome to Connect Four! \n");

    printf("Player 1, Enter your name: ");
    scanf_s("%s", &player1);

    printf("Player 2, Enter your name: ");
    scanf_s("%s", &player2);
}

void flipCoin() {
    srand(time(0));
    if (rand() % 2 != 0) {
        player1Color = 1;
        player2Color = 2;
        printf("HEADS ! %s goes first, You are RED \n", player1);
    } 
    else {
        player1Color = 2;
        player2Color = 1;
        printf("TAILS ! %s goes first, You are RED \n", player2);
    }
}

void playerMove(){
    int turn = 0;
    bool isRunning = true;
    int numberChosen;
    Color player;
    char* playerUsername;
    // determine current color based on odd/even
    while(turn < rows * columns && isRunning){
        int playerTurn  =( (turn % 2) == 0 )? (player = Red) : (player = Yellow);
        if (player == Red) {
            if (player1Color == Red) {
                playerUsername = player1;
            } else {
                playerUsername = player2;
            }
        }  

        else if (player == Yellow) {
            if (player1Color == Yellow) {
                playerUsername = player1;
            } else {
                playerUsername = player2;
            }
        }
        while(true){
        // get the column number from user 
            printf("%s enter column #(1-7): \n", playerUsername);
            scanf("%d", &numberChosen);

        if(insert(player, numberChosen)){
            turn++;
            break;
        
        }
        printf("input another valid #(1-7)\n");
        

        }
        gameBoard();

    }
}

    
bool insert(Color name, int col){
    if(col <= 0 || col > columns){ // out of bound
        return false;
    }

    int r;
    for( r = rows -1; r >= 0; r--){
        if(board[r][col] == '0'){
            board[r][col] = getCode(name);
            break;
        }
    }
     if(r == -1){// color present at the top of the column 
    printf("column is full :(  \n");
        return false;
    }

    board[r][col] = getCode(name);
    return true;
}


int main(){
    askplayername();
    flipCoin();
    init();
    playerMove();



    return 0;

}

