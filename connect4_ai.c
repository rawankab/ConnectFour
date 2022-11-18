#include<stdio.h>
#include <stdbool.h>
#include <setjmp.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
time_t start,end;
int time1 = 0;
int time2 = 0;
#define min(a,b) a > b ? b : a;
#define max(a,b) a > b ? a : b;

void flipCoin();
char player1[10];
const int columns = 7; 
const int rows = 6; 
int turn = 0;
int PlayerTurn = 0;

int computermove();
int playersmove();


int Player = 0;
int Computer = 0;
int maxdepth = 5;
int** board;
bool isRunning = true;
int* minimax();
void printgameboard();
int checkWhiteSpace();
void makemove();
void askplayername();
void currentplayermove();
char getChar();
bool checkWin();
int tabScore();
int scoreSet();
int** copyboard();
int heurFunction();

int computermove() {
    printf("AI is thinking about a move...\n");
    int* minimaxarray= minimax(board, maxdepth,0 -INT_MAX, INT_MAX,Computer);
    printf("%d",minimaxarray[1]);
    return minimaxarray[1]+1;
}

int* minimax(int** b , int depth, int alpha, int beta, int player) {
    int* result = calloc(2, sizeof(int)); 
   if (depth == 0 || depth >= (columns * rows) - turn) {
		// get current score to return
		result[0] = tabScore(b, Computer);
        result[1] =  -1;
        return result;
    }

    if (player == Computer) { // if AI player
		int* movesofar = calloc(2, sizeof(int));
        movesofar[0] = INT_MIN;
        movesofar[1] =  -1; // since maximizing, we want lowest possible value
		if (checkWin(b, Player)) { // if player about to win
			return movesofar; // force it to say it's worst possible score, so it knows to avoid move
		} 
        for (int c = 0 ; c < columns; c++) {
            if(b[rows -1][c] ==0) {
                int** newboard = copyboard(b);
                makemove(newboard, c, player);
                int* scorearray = minimax(newboard, depth -1, alpha, beta, Player);
                int score = scorearray[0];
                if (score > movesofar[0]) {
                    movesofar[0] = score;
                    movesofar[1]= c;
                }
                alpha = max(alpha, movesofar[0]);
                if (alpha >= beta) { break;}
            }
        }
            return movesofar;
    }
    else {
                int* movesofar = calloc(2, sizeof(int));
                movesofar[0] = INT_MAX;
                movesofar[1] =  -1; 

                if (checkWin(b,Computer)) {
                    return movesofar;
                }

                for (int c = 0 ; c < columns ; c++) {
                    if(b[rows -1][c] == 0) {
                        int** newboard = copyboard(b);
                        makemove(newboard, c, player);
                        int* scorearray = minimax(newboard, depth - 1, alpha, beta, Computer);
                        int score = scorearray[0];
                        if (score < movesofar[0]) {
                            movesofar[0] = score;
                            movesofar[1] = c;
                        }
                        beta = min(beta, movesofar[0]);
                        if (alpha >= beta) {  break;}
                    }
                }
                return movesofar;
    }
}



int tabScore(int** bb, int player){
    int score = 0;
    int rs[columns];
    int cs[rows];
    int set[4];

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < columns; c++){
            rs[c] = (bb[r][c]);
        }
        for(int c =0; c < columns - 3; c++){
            for(int i = 0; i < 4; i++){
                set[i] = rs[c +i];
            }
            score += scoreSet(set, player);
        }
    }

    for(int c = 0; c < columns; c++){
        for(int r = 0; r < rows; r++){
            cs[r] = bb[r][c];
        }
        for(int r =0; r < rows- 3; r++){
            for(int i = 0; i < 4; i++){
                set[i] = cs[r +i];
            }
            score += scoreSet(set, player);
        }
    }

    for(int r = 0; r < rows - 3; r++){
        for(int c = 0; c < columns; c++){
            rs[c] = bb[r][c];
        }
        for(int c =0; c < columns - 3; c++){
            for(int i = 0; i < 4; i++){
                set[i] = bb[r +i][c + i];
            }
            score += scoreSet(set, player);
        }
    }

    for(int r = 0; r < rows -3; r++){
        for(int c = 0; c < columns; c++){
            rs[c] = bb[r][c];
        }
        for(int c =0; c < columns - 3; c++){
            for(int i = 0; i < 4; i++){
                set[i] = bb[r + 3 - i][c + i];
            }
            score += scoreSet(set, player);
        }
    }
    return score;
}


int scoreSet(int* v, int player){
    int good = 0;
    int bad = 0;
    int empty = 0;
    int arr_size = sizeof(v)/sizeof(v[0]);
    for(int i = 0; i < arr_size; i++){
        good += (v[i] == player) ? 1 : 0;
		bad += (v[i] == Player|| v[i] == Computer) ? 1 : 0;
		empty += (v[i] == 0) ? 1 : 0;
        bad -=good;
        return heurFunction(good,bad,empty);
    }
}


int heurFunction(int g, int b, int z) {
    int score = 0;
	if (g == 4) { score += 500001; } 
	else if (g == 3 && z == 1) { score += 5000; }
	else if (g == 2 && z == 2) { score += 500; }
	else if (b == 2 && z == 2) { score -= 501; } 
	else if (b == 3 && z == 1) { score -= 5001; } 
	else if (b == 4) { score -= 500000; }
	return score;
}

void makeboard() {
    board = (int*) calloc(rows, sizeof(int));
    for(int w = 0; w < columns; ++w) {
        board[w] = (int*) calloc(columns, sizeof(int));

    }
}



void makemove(int** board, int column, int player) {
    int r;
    for (r = rows - 1 ; r >= 0; --r) {
        if (board[r][column]==0) {
            board[r][column] = player;
            break;
        }
    }
}


void currentplayermove() {
    int playermove = 0;
    int computersmove = 0;
    int insertion;
    while (turn < rows * columns && isRunning) {
        start = 0;      // Resets the start time to 0
        end = 0;       // Resets the end time to 0
        time(&start);  
        if ((turn % 2) == 0 ) {
            PlayerTurn = Player;
            playermove = playersmove();
            printf("%d", playermove);
            makemove(board, playermove, Player);
            turn++;
        } else {
          PlayerTurn = Computer;
          computersmove = computermove();
          makemove(board, computersmove, Computer);
            turn++;
        }
        int winnerchecking = checkWin(board, PlayerTurn);
        printgameboard();
        if (winnerchecking == true) {
            if(PlayerTurn == Computer) {
                    printf("Computer WON!\n");
                } else {
                    printf("%s WON!\n", player1);
                }
            isRunning = false;
        } 
    }
}






void printgameboard() {
    printf("-----------------------------  \n");
    for(int i = 0; i < rows; i++){
        for(int j = 1; j <= columns; j++){
            printf("| %d ", board[i][j]);
        }  
        printf("|\n");
    }
    printf("-----------------------------  \n");

}

int playersmove(){
    int numberChosen;
    printf("Enter column #(1-7), %s ", player1); 
    while(true){
        char input[100];
        fgets(input, 100, stdin);
        //check if first char is an integer 
        if (!isdigit(input[0])){
            printf("please enter a number between 1-7 \n");
            continue;
        }
        //check if rest of string is a valid integer
        bool validNum = true;
        for(char* c = input + 1; (*c) !='\0' && (*c) != '\n'; c++){
            if (!isdigit(*c)){
                validNum = false;
                printf("please enter a number between 1-7 \n");
                break;
            }
        }
        if (board[rows -1][numberChosen]!= 0) {
            printf("The column in full");
            continue;
        }
        if (validNum) {
            numberChosen = atoi(input);
            if (numberChosen < 1 || numberChosen > 7) 
                printf("please enter a number between 1-7 \n");
            else {
                break;
            }
        }
    }

    numberChosen = (int) numberChosen;
    return numberChosen;
}

int** copyboard(int** board) {
    int** newboard = (int*) calloc(rows, sizeof(int));
    for(int w = 0; w < columns; ++w) {
        newboard[w] = (int*) calloc(columns, sizeof(int));
    }

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < columns ; c++) {
            newboard[r][c] = board[r][c];
        }
    }
    return newboard;
}






void askplayername() {

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
}

int checkWhiteSpace(char *player) {
    while (*player != '\0') {
        if (*player == ' ') {
            return 0;
        }
        player++;
    }
    return 1;
}

void flipCoin() {
    srand(time(0));
    if (rand() % 2 != 0) {
        Player = 1;
        Computer = 2;
        turn = 0;
        printf("HEADS ! The player who goes first as RED is .... %s \n", player1);
    } 
    else {
        Player = 2;
        Computer = 1;
        turn = 1;
        printf("TAILS ! The player who goes first as RED is.... The computer\n");
    }
}

/*checkWin() requires as parameters: row and column indexes where the last insertion occurred and the color of the coin inserted.
checkWin() returns true if last insertion resulted in a win for the player and false otherwise(there are 3 cases for checking:
horizontally, vertically, and diagonally(left to right and right to left), thus 4 counters). */
bool checkWin(int** board, int player) {
    //first case: checking horizontally
    int counter = 0;

    for (int c = 0 ; c < columns - 3 ; c++) {
        for(int r = 0 ; r < rows; r++) {
            for (int i = 0 ; i < 4 ;i++) {
                if (board[r][c+i] == player){
                    counter++;
                }
                if (counter == 4){
                    return true;
                }
            }
            counter = 0;
        }
    }
        for(int c = 0; c < columns; c++){
            for(int r = 0; r < rows -3; r++){
                for(int i = 0; i < 4; i++){
                    if(board[r+i][c] == player){
                        counter++;
                    }
                    if(counter == 4){
                        return true;
                    }
                }
                counter = 0;

            }
        }

        for (unsigned int c = 0; c < columns - 3; c++) {
		    for (unsigned int r = 3; r < rows; r++) {
			    for (int i = 0; i < 4; i++) {
				    if (board[r - i][c + i] == player) {
					   counter++;
				    }
				    if (counter == 4) { 
                        return true; 
                    }
			    }
			counter = 0;
		}
	}
        for(int c = 0; c < columns -3; c++){
            for(int r = 0; r < rows -3; r++){
                for(int i = 0; i < 4; i++){
                    if(board[r+i][c + i] == player){
                        counter++;
                    }
                    if(counter == 4){
                        return true;
                    }
                }
                counter = 0;

            }
        }
        return false;
    }


int main() {
    makeboard();
    askplayername();
    flipCoin();
    printgameboard();
    currentplayermove();
    return 0;
}

/*
Test cases : 

Let's consider the case where one of the players enters a # of column between 1-7 denoted by
j and the insertion was successiful (that is the column chosen is not full) 
he will be a winner only if :

1.1- 4 consecutive horizontal connections where formed at any of the rows (1-6), from the jth column to the jth+3
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

1.2- 4 consecutive vertical connections where formed at one of the column (1-7) from the ith row to the ith+3 
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

1.3- 4 consecutive connections where formed by to a positive diagonal that could only be formed
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

1.4- 4 consecutive connections where formed by to a negative diagonal that could only be formed
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

2- if the player enters a column number that that is between 1-7 but the chosen column is full. the player is asked 
to enter another column number.
i.e 
-----------------------------
| 0 | Y | 0 | 0 | 0 | 0 | 0 |
| 0 | R | 0 | 0 | 0 | 0 | 0 |
| 0 | Y | 0 | 0 | 0 | 0 | 0 |
| 0 | R | 0 | 0 | 0 | 0 | 0 |
| Y | R | Y | 0 | 0 | 0 | 0 |
| R | Y | Y | R | R | 0 | 0 |
-----------------------------
Celia enter column #(1-7):
2
Column is full please enter another element:

3- if the player enters '0' or any other input other than #1-7 as an input an exception will be thrown requiring him to enter a column number (1-7).
i.e 
Celia enter column #(1-7):
0
Invalid input, please enter a number between 1 & 7:


*/
