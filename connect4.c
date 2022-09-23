#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>


//jmp_buf savebuf;
//void init();

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
    
    //int directions[][] { {-1, 1}, {0, 1}, {1, 1}, {1, 0} };
    //List<int[]> possibleDirections[][];
     
/*void init(){
 board = new Color[rows][columns];  
  possibleDirections = new List[rows][columns];
  for(int r = 0; r < rows; r++){
    for(int c = 0; c< columns; c++){
        board[r][c] = Color.Empty;
    }
  }
}*/
void init(){
    for (int i = 0; i < 6; i++){
        for(int j =0; j < 7; j++){
            board[i][j] = '0';
            printf("| %c ", board[i][j]);
        }
        printf("\n");
    }
}

void printBoard(){
    //char spaces[] = "----|---|---|---|---|---|---|";
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf("| %c ", board[i][j]);
        }
        printf("|\n");    
        //printf("%s\n", spaces);    
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
        // get input
            printf("player %c enter column #(1-7): \n", getCode(player));
            scanf("%d", &numberChosen);
            --numberChosen; //index -1
            // need to add a try and catch

        if(insert(player, numberChosen)){
            break;
        }
        printf("input another #(1-7)\n");

        }
        printBoard();

        turn++;

    }
}
    
bool insert(Color name, int col){
    if(col < 0 || col > columns){ // out of bound
        return false;
    }

    int r;
    for( r = rows -1; r >= 0; r--){
        if(board[r][col] == Empty){
            board[r][col] == getCode(name);
            break;
        }
    }
    if(r == rows){
        return false;
    }
    else if( r == -1){
        r++;
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

