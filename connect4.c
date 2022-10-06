//Connect 4 - CMPS 270 
// Team : Alice Karadjian, Khalil Bitar, Rawan Kabrit, Ryan Khalil

#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>
#include <stdlib.h>

void init();
void gameBoard();
char getChar();
void playerMove();
bool insert();
void playername();
void flipCoin();
void askPlayerName();
bool checkWin();

char player1[10];
char player2[10];

const int rows = 6;
const int columns = 7;
char board[6][7];

// enum Color gives the 3 possible numerical representations of the colors that are going to be used
// in our 2D array. Since we are going to keep track of the color of the players, 
// we decided to create 2 variables called "player1Color" and "player2Color". 

typedef enum Color {Empty = 0, Red = 1 , Yellow = 2} Color;
Color player1Color; 
Color player2Color;


// getCode() reuires as parameter the enum Color of each player and returns its corresponding char.

 char getChar(Color converter){
        if (converter == 0){
            return '0';
        }
        else if (converter == 1){
            return 'R';
        }
        else {
            return 'Y';
        }
    }
   
    
// init() does not require any parameters. It initializes the game Board having
// seven columns and six rows to empty cells.


void init(){
    printf("----------------------------- \n");
    for (int i = 0; i < rows; i++){
        for(int j =1; j <= columns; j++){
            board[i][j] = getChar(Empty);
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("----------------------------- \n");
}

// gameBoard() does not require any parameters. It prints out the updated game board at each 
// move the players undertake. 

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
// askPlayerName() does not requires any parameters. It welcomes the players and asks for their names. 

void askPlayerName() {

    printf("Welcome to Connect Four! \n");

    printf("Player 1, Enter your name: ");
    int playername;
    while (playername != )
    scanf_s("%s", &player1);

    printf("Player 2, Enter your name: ");
    scanf_s("%s", &player2);
}
// flipCoin() does not require any parameters. It assigns randomly which one of the players will play Red. 
// Since Rand returns a random integer it's either going to give us a modulus of 1 or 0, which guarantees 
// the 50/50 percent chance. If the modulus returns 1 (meaning HEADS) the first player will be given the
// color RED, and the second player will be YELLOW. In Contrary the Opposite will happen if it's TAILS.

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
// playerMove() does not requires any parameters and stops when the number of turns exceeds 42 (after that the 
//board will be full) or when one of the players wins. The main function of the playerMove() 
// is to determine the current color based on odd/even of the turn. In addition, while the game is still 
// running playerMove() gets the column number from the user and inserts the 'coin' in the board while printing it.  

void playerMove(){
    int turn = 0;
    bool isRunning = true;
    int numberChosen;
    Color player;                   // This variable keeps track of the color of THE CURRENT PLAYER
    char* playerUsername;          // Display the username of the current player
    while(turn < rows * columns && isRunning){
        int playerTurn  =( (turn % 2) == 0 )? (player = Red) : (player = Yellow);
        
        if (player == Red) {                     //This first condition represents the following: If the current player should be Red and player1 is assigned the color red, then his name will be displayed
            if (player1Color == Red) {
                playerUsername = player1;
            } else {                      // This automatically means that the second player is assigned RED, so his/her name will be Displayed
                playerUsername = player2;
            }
        }  

        else if (player == Yellow) {                // This second Condition represents the following : If the current player should be YELLOW and the first Player is assigned YELLOW
            if (player1Color == Yellow) {
                playerUsername = player1;
            } else {                               // This automatically means that the second player is assigned YELLOW so his/her name will be displayed
                playerUsername = player2;
            }
        }

        while(true){ 
            printf("%s enter column #(1-7): \n", playerUsername);  
            scanf("%d", &numberChosen);

        if(insert(player, numberChosen)){
            turn++;
            int r = rows - 1;
            while(board[r][numberChosen] != getChar(Empty)) {
               r--;
            }
            r++;
            if(checkWin(r, numberChosen, player)) {
               printf("player %d won!\n", getChar(player));
                isRunning = false;
            }
            break;
        }
        printf("input another valid #(1-7)\n");
        

        }
        gameBoard();

    }
}

// insert() requires as parameters the enum Color corresponding to the current player and the chossen column 
// in which he would like to insert his 'coin'. insert() returns a boolean : false if the insertion failed and
// true if the insertion was succeseful. It throws an exception if the column chosen is not the range
// 1 to 7 or full.

bool insert(Color currentPlayer, int col){
    if(col <= 0 || col > columns){ 
        return false;
    }

    int r;
    for( r = rows -1; r >= 0; r--){
        if(board[r][col] == '0'){
            board[r][col] = getChar(currentPlayer);
            break;
        }
    }
     if(r == -1){
    printf("column is full :(  \n");
        return false;
    }

    board[r][col] = getChar(currentPlayer);
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
        if(board[r][k] == getChar(color_inserted))
            counter++;
        else
            counter = 0;
    }
    return false;
}

int main(){
    askPlayerName();
    flipCoin();
    init();
    playerMove();



    return 0;

}

