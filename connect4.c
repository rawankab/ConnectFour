//Connect 4 - CMPS 270 
// Team : Alice Karadjian, Khalil Bitar, Rawan Kabrit, Ryan Khalil

#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//functions
void init();
void gameBoard();
char getChar();
void playerMove();
int insert();
void playername();
void flipCoin();
void askPlayerName();
bool checkWin();
bool checkBoardFull();
int checkWhiteSpace();
int strcmp();

//time 
time_t start,end;
int time1 = 0;
int time2 = 0;

//player name
char player1[10];
char player2[10];

//board specs
const int rows = 6;
const int columns = 7;
char board[6][7];

/* enum Color gives the 3 possible numerical representations of the colors that are going to be used
   in our 2D array. Since we are going to keep track of the color of the players,  
   we decided to create 2 variables called "player1Color" and "player2Color". */
typedef enum Color {Empty = 0, Red = 1 , Yellow = 2} Color;
Color player1Color; 
Color player2Color;


/* checkBoartFull() does not take any parameters. 
It checks if the board is full or not by checking if there is an empty space in the
1st column of the board. If there is an empty space, then the board is not full. If there is no empty
space, then the board is full. */
bool checkBoardFull(){
    for (int i = 0; i <=columns; i++){
        if (board[0][i] == '0'){
            return false;
        }
    }
    return true;
}

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
   
    
/*init() does not require any parameters. It initializes the game Board having
seven columns and six rows to empty cells. */
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

/*gameBoard() does not require any parameters. It prints out the updated game board at each 
move the players undertake. */
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

/*askPlayerName() does not requires any parameters. It welcomes the players and asks for their names each one 
at a time. However the player are required to input their usernames as a single word with no space. That is, 
if the player enters his username with a white space the function will throws an exception for him to enter 
a correct one. */
void askPlayerName() {

    printf("Welcome to Connect Four! \n");
    while (true) {
    printf("Player 1, Enter your username as a single word: ");
    fgets(player1, 20, stdin);

    if (checkWhiteSpace(player1) == 0) {
        printf("Please enter a name with no white spaces\n");
        continue;
        }
        break;
    } 




    while (true) {
        printf("Player 2, Enter your username as a single word: ");
        fgets(player2, 20, stdin);

        if (checkWhiteSpace(player2) == 0 || strcmp(str1, str2) == 0) {
            printf("Please enter a different name with no white spaces\n");
            continue;
        } 
        break;

    }
}

/*checkWhiteSpace takes as parameter a pointer pointing to the first char of the player's name.
it return an int : 0 if a white space was found and 1 otherwise. */
int checkWhiteSpace(char *player) {
    while (*player != '\0') {
        if (*player == ' ') {
            return 0;
        }
        player++;
    }
    return 1;
}

/*flipCoin() does not require any parameters. It assigns randomly which one of the players will play Red. 
Since Rand returns a random integer it's either going to give us a modulus of 1 or 0, which guarantees 
the 50/50 percent chance. If the modulus returns 1 (meaning HEADS) the first player will be given the
color RED, and the second player will be YELLOW. In Contrary the Opposite will happen if it's TAILS. */
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

/* playerMove() does not requires any parameters. It stops the game when the number of turns exceeds 42 (after that the 
board will be full) or when one of the players wins. The main function of the playerMove() 
is to determine the current color based on odd/even sign of the turn. In addition, while the game is still 
running playerMove() gets the column number from the user and inserts the 'coin' in the board while printing it 
and then calls the function checkWin() to check if any of the player has won. If the game terminates with no winner
it assigns the winner based on the total time taken for each player */
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
        start = 0;      // Resets the start time to 0
        end = 0;        // Resets the end time to 0
        

        time(&start);                              // This is the start of the timer

    while(true){ 

            printf("%s Enter column #(1-7): ", playerUsername); 
             
            scanf("%d", &numberChosen);

            int insertion = insert(player, numberChosen);
            
             if(insertion != -1){
                time(&end);                                 // This is the end of the timer
                if (player == player1Color) {               // This condition checks if the current player is player 1
                    time1 += (int) difftime(end,start);     // This is the time of the first player
                } else {
                    time2 += (int) difftime(end,start);     // This is the time of the second player
                }
                turn++;
                int r = insertion;
                if(checkWin(r, numberChosen-1, player)) {
                    printf("%s WON!\n", playerUsername);
                    isRunning = false;
                }
                break;
        }
            printf("NOT VALID :(  => # should be in the range (1-7)\n");
        }
        

        gameBoard();

        /*Checks if the board is full. If it is, then the game will check who took less time to 
        complete the game and will declare him/her the winner.
        In order to check if it works, input the following sequence
        1 2 1 2 2 1 1 2 2 1 2 1 3 4 3 3 3 3 4 4 4 3 5 4 4 6 5 5 5 5 7 5 7 6 6 7 7 6 6 7 6 7 <-- this causes a tie. */
        if (checkBoardFull()) {
             printf("The board is full! the winner will be chosen based on speed: \n");
             if (time1 < time2) {
                 printf("%s wins! (with %s = %ds and %s = %ds)\n", player1, player1, time1, player2, time2);
            } else if (time2 < time1) {
                 printf("%s wins! (with %s = %ds and %s = %ds)\n", player2, player2, time2, player1, time1);
            } else {
                 printf("It's a tie! (with %s = %ds and %s = %ds) \n", player1, time1, player2, time2);
            }
            isRunning = false;
             break;
        }

    }
}

/*insert() requires as parameters the enum Color corresponding to the current player and the chossen column 
in which the player would like to insert his 'coin'. insert() returns an int : -1 if the insertion failed and
the row in which the coin is inserted if the insertion was succeseful. It throws an exception if the 
column chosen is not the range 1 to 7 or if the column chosen is full. */ 
int insert(Color currentPlayer, int col){
    if(col <= 0 || col > columns ){ 
        return -1;
    }

    int r;
    for( r = rows -1; r >= 0; r--){
        if(board[r][col] == '0'){
            board[r][col] = getChar(currentPlayer);
            break;
        }
    }
     if(r == -1){
    printf("COLUMN IS FULL :(  \n");
        return -1;
    }

    board[r][col] = getChar(currentPlayer);
    return r;
}

/*checkWin() requires as parameters: row and column indexes where the last insertion occurred and the color of the coin inserted.
checkWin() returns true if last insertion resulted in a win for the player and false otherwise(there are 3 cases for checking:
horizontally, vertically, and diagonally(left to right and right to left), thus 4 counters). */
bool checkWin(int r, int c, Color color_inserted) {
    //first case: checking horizontally
    int i = c - 3;
    while(i < 0)
        i++;
    int j = c + 3;
    while(j > 6)
        j--;
    int counter1 = 0;
    
    for(int k = i; k <= j+1; k++) {
        if(counter1 == 4) {
            printf("horizontally\n");
            return true;
        }
        if(board[r][k+1] == getChar(color_inserted))
            ++counter1;
        else if(board[r][k+1] != getChar(color_inserted))
            counter1 = 0;  //reset counter; start counting agains
    }

    //second case: checking vertically
    //similar concept, except now i and j are representing change in row and not column
    i = r - 3;
    while (i < 0)
        i++;
    j = r + 3;
    while (j > 5)
        j--;
    int counter2 = 0;
    for(int k = i; k <= j+1; k++) {
        if(counter2 == 4) {
            printf("vertically\n");
            return true;
        }
        if(board[k][c+1] == getChar(color_inserted))
            ++counter2;
        else if(board[k][c+1] != getChar(color_inserted))
            counter2 = 0;
    }

    //third case: checking diagonally-left to right
    int i1 = r + 3; int i2 = c - 3; //start checking from these initial coordinates
    while(i1 > 5 || i2 < 0) {
        i1--;
        i2++;
    }

    int j1 = r - 3; int j2 = c + 3; //checking ends at these coordinates
    while(j1 < 0 || j2 > 6) {
        j1++;
        j2--;
    }
    
    int k1 = i1; int k2 = i2;
    int counter3 = 0;
    while(k1 >= j1 - 1 && k2 <= j2 + 1) {
        if(counter3 == 4) {
            printf("diagonally, left to right\n");
            return true;
        }
        if (board[k1][k2+1] == getChar(color_inserted))
            ++counter3;
        else if(board[k1][k2+1] != getChar(color_inserted))
            counter3 = 0;
        k1--;
        k2++;
    }

    //fourth case: checking diagonally-right to left
    //Similar concept, except coordinates of where we start and where we finish change a bit
    i1 = r + 3; i2 = c + 3;
    while(i1 > 5 || i2 > 6) {
        i1--;
        i2--;
    }
    
    j1 = r - 3; j2 = c - 3;
    while(j1 < 0 || j2 < 0) {
        j1++;
        j2++;
    }
    
    k1 = i1; k2 = i2;
    int counter4 = 0;
    while(k1 >= j1 - 1 && k2 >= j2 - 1) {
        
        if(counter4 == 4) {
            printf("diagonally, right to left\n");
            return true;
        }
        if(board[k1][k2+1] == getChar(color_inserted))
            ++counter4;
        else if(board[k1][k2+1] != getChar(color_inserted))
            counter4 = 0;
        k1--;
        k2--;
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
/*
Test cases : 

1- if the player1 enters his username as two words (with a white space character) the game requires him to enters 
an exception is thrown to ask the player to enter his name as a single word. 
i.e 
Player 2, Enter your name: Celia L
Please enter a name with no white spaces
Player 2, Enter your name: 

2- if the player2 enters his username as two words (with a white space character) the game requires him to enters 
an exception is thrown to ask the player to enter his name as a single word. 
i.e 
Welcome to Connect Four! 
Player 1, Enter your name: Celia L
Please enter a name with no white spaces

3- If the second user enters a name that's identical to the first player names , the game requires him/her to enter
a new name . The exception if thrown "Please enter a different name with no white spaces"
Player 2 , enter your name : Celia (where Celia is also the first players name)
output : Please enter a different name with no white spaces

3- Let's consider the case where one of the players enters a # of column between 1-7 denoted by
j and the insertion was successiful (that is the column chosen is not full) 
he will be a winner only if :

3.1- 4 consecutive horizontal connections where formed at any of the rows (1-6), from the jth column to the jth+3
(where j + 3 <= 7). Note that vertically there are 6*4 = 24 possible ones.
i.e. (Winner on the 2nd row) 
-----------------------------
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| R | 0 | 0 | Y | Y | 0 | 0 |
| Y | Y | R | R | R | R | Y |
| R | Y | R | Y | R | Y | R |
-----------------------------

3.2- 4 consecutive vertical connections where formed at one of the column (1-7) from the ith row to the ith+3 
(where i + 3 <= 6). Note that there are 7*3 = 21 possible ones.
i.e. (Winner on the 5th column)
-----------------------------
| R | 0 | 0 | 0 | Y | 0 | 0 |
| R | R | 0 | 0 | Y | 0 | 0 |
| Y | Y | 0 | 0 | Y | 0 | 0 |
| R | R | R | 0 | Y | Y | R |
| Y | R | Y | R | R | Y | Y |
| R | Y | Y | R | R | R | Y |
-----------------------------

3.3- 4 consecutive connections where formed by to a positive diagonal that could only be formed
between the boxs starting at board[3][1] (and going diagonally upwards) until the 
board[1][4] (and going diagonally upwards). Note that there are only 3*4 = 12 possible ones
(since only 3 rows could form a postive diagonal and on each row there are 4 possible cases)
i.e (Winner starting from the 3rd row and going diagonally positive) 
-----------------------------                   
| 0 | 0 | 0 | R | 0 | 0 | 0 |
| 0 | 0 | R | Y | 0 | 0 | 0 |
| 0 | R | R | Y | 0 | 0 | 0 |
| R | Y | R | Y | 0 | 0 | 0 |
| Y | R | Y | R | 0 | 0 | 0 |
| R | Y | Y | R | Y | 0 | 0 |
-----------------------------

3.4- 4 consecutive connections where formed by to a negative diagonal that could only be formed
between the boxs starting at board[4][1] (and going diagonally downwrds) until the 
board[6][4] (and going diagonally downwords). Note that there are only 3*4 = 12 possible ones
(since only 3 rows could form a negative diagonal and on each row there are 4 possible cases)
i.e (Winner starting from the 4th row and going diagonally downwards) 
-----------------------------
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | Y | 0 | 0 | 0 | 0 |
| 0 | 0 | R | Y | 0 | 0 | 0 |
| 0 | 0 | Y | Y | Y | 0 | R |
| 0 | 0 | R | R | R | Y | R |
-----------------------------

4- if the player enters a column number that that is between 1-7 but the chosen column is full. the player is asked 
to enter another column number.
i.e 
Celia enter column #(1-7): 
3
COLUMN IS FULL :(  
NOT VALID :(  => # should be in the range (1-7)
Celia enter column #(1-7): 

5- if the player enters '0' as an input an exception will be thrown requiring him to enter a column # (1-7).
i.e 
User1 enter column #(1-7):
0
NOT VALID :(  => # should be in the range (1-7)
User1 enter column #(1-7):

6- if the player enters any non zero negative number as an input an exception will be thrown 
requiring him to enter a column # (1-7).
i.e 
User2 enter column #(1-7):
-3
NOT VALID :(  => # should be in the range (1-7)
User2 enter column #(1-7):


*/