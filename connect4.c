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
bool checkWin();

char player1[10];
char player2[10];

const int rows = 6;
const int columns = 7;
char board[6][7];


typedef enum Color {Empty = 0, Red = 1 , Yellow = 2} Color;
Color player1Color; 
Color player2Color;
// Since we are going to keep track of the color of the players, we decided to create 2 variables called "player1Color"
// 
 


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
    int playername;
    while (playername != )
    scanf_s("%s", &player1);

    printf("Player 2, Enter your name: ");
    scanf_s("%s", &player2);
}
// Specifications : We decide to use the random fucntion to decide which one of the players will play Red. Since Rand returns a random integer
// It's either going to give us a modulus of 1 or 0, which guarantees the 50/50 percent chance . If the modulus returns 1 (meaning HEADS)
// the first player will be given the color RED, and the second player will be YELLOW. In Contrary the Opposite will happen if it's TAILS
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
    Color player; // This variable keeps track of the color of THE CURRENT PLAYER
    char* playerUsername; // Display the username of the current player
    // determine current color based on odd/even
    while(turn < rows * columns && isRunning){
        int playerTurn  =( (turn % 2) == 0 )? (player = Red) : (player = Yellow);
        if (player == Red) { //This first condition represents the following: If the current player should be Red and player1 is assigned the color red, then his name will be displayed
            if (player1Color == Red) {
                playerUsername = player1;
            } else { // This automatically means that the second player is assigned RED, so his/her name will be Displayed
                playerUsername = player2;
            }
        }  

        else if (player == Yellow) { // This second Condition represents the following : If the current player should be YELLOW and the first Player is assigned YELLOW
        // then his/her name will be displayed
            if (player1Color == Yellow) {
                playerUsername = player1;
            } else { // This automatically means that the second player is assigned YELLOW so his/her name will be displayed
                playerUsername = player2;
            }
        }
        while(true){
        // get the column number from user 
            printf("%s enter column #(1-7): \n", playerUsername); // will display the username of the player 
            scanf("%d", &numberChosen);

        if(insert(player, numberChosen)){
            turn++;
            int r = rows - 1;
            while(board[r][numberChosen] != getCode(Empty)) {
               r--;
            }
            r++;
            if(checkWin(r, numberChosen, player)) {
               printf("player %d won!\n", getCode(player));
                isRunning = false;
            }
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

bool checkWin(int r, int c, Color color_inserted) {
    int i = c - 3;
    while(i < 0)
        i++;
    int j = c + 3;
    while(j > 6)
        j--;
    int counter = 0;
    for(int k = i; k <= j; k++) {
        if(counter == 4)
            return true;
        if(board[r][k] == getCode(color_inserted))
            counter++;
        else
            counter = 0;
    }
    return false;
}

int main(){
    askplayername();
    flipCoin();
    init();
    playerMove();



    return 0;

}

