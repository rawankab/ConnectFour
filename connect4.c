//Connect 4 - CMPS 270

#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>

void init();
void printBoard();
char getCode();
void playerMove();
bool insert();


typedef enum Color {Empty = 0, Red = 1 , Yellow = 2} Color;
 


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
   
    const int rows = 6;
    const int columns = 7;
    char board[6][7];
    

void init(){
    for (int i = 0; i < rows; i++){
        for(int j =1; j <= columns; j++){
            board[i][j] = '0';
            printf("| %c ", board[i][j]);
        }
        printf("\n");
    }
}

void printBoard(){
    
    for(int i = 0; i < rows; i++){
        for(int j = 1; j <= columns; j++){
            printf("| %c ", board[i][j]);
        }
        printf("|\n");    
           
    }
    
    printf("  1   2   3   4   5   6   7 \n");

}

void playerMove(){
    int turn = 1;
    bool isRunning = true;
    int numberChosen;
    Color player;
    // determine current color based on odd/even
    while(turn < rows * columns && isRunning){
        int playerTurn  =( (turn % 2) == 0 )? 2 : 1;
        if(playerTurn == 1){
            player = Red;
        }
        else{
            player = Yellow;
        }
        while(true){
        // get the column number from user 
            printf("player %c enter column #(1-7): \n", getCode(player));
            scanf("%d", &numberChosen);

        if(insert(player, numberChosen)){
            break;
        }
        printf("input another valid #(1-7)\n");
        turn--;

        }
        printBoard();

        turn++;

    }
}

    
bool insert(Color name, int col){
    if(col <= 0 || col > columns){ // out of bound
        return false;
    }

    int r;
    for( r = rows -1; r >= 0; r--){
        if(board[r][col] == Empty){
            board[r][col] == getCode(name);
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

    char winner = ' ';
    printBoard();
    playerMove();



    return 0;

}

