#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int entered, int minimum, int maximum);
int isBoardFull(char board[N][N]);
void createInitialBoard(char board[N][N]);
void readUserMove(int *, int *, int *);
void printCurrentBoard(char board[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char board[N][N], char symbol);
int computerPlaysToWin(char board[N][N], int *cRow , int *cCol);
void computerPlaysNotSoRandom(int * cRow, int * cCol, int uRow, int uCol);
void sumAllDimensions(char board [N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD);
int memberOf(int aNum, int someArray[N]);
int computerPlaysToBlock(char [N][N], int * , int * );


int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   int stepsWon = 0;  
   char board[N][N];
   char winner = 'N';
   
   printf("This tic-tac-toe board is of size %d by %d\n", N, N);
   
   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);     // create a 3 X 3 board with '?' in each cell 
   
   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {     
     taken = 0;
     
    while (!(taken))                  // loop used to accept valid row and col values from the user
    {
      readUserMove(&userRow, &userCol, &stepsWon);                  //get user's move
      printf("You chose row %d and column %d \n", userRow, userCol);
      
      while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
      {
        printf("That's is an invalid row or column number - try again\n");
        readUserMove(&userRow, &userCol, &stepsWon);
        printf("You chose row %d and column %d \n", userRow, userCol);
      }
      
     
      if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
      {
        board[userRow-1][userCol-1] = 'X';      // store an X there
        taken = 1;
      }
      else
      {
        taken = 0;                  // otherwise inform the user to enter values again
        printf("That spot is taken - please try another one\n");
      }
      
    } //end of while (!taken)
  
     if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
     {
       printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
       winner = 'Y';
     }
     
     else  if (!(isBoardFull(board)))            //check if the board is already full
     {
       taken = 0;
       
       while (!(taken))
       {
        getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col
       
        if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
        {
          board[computerRow][computerCol] = 'O';
          taken = 1;
  
        }
        else
        {
          taken = 0;    //That spot is taken - computer - try another one
        } 
       }
       
       printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
       
       if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
       {
         printf("Oh the computer won this time :(( think hard next time\n");
         winner = 'Y';
       }  
     }
   
  printCurrentBoard(board);  
  
  printf("\nPress enter to continue \n");             
  getchar();
       
   } //end of while
   
   if (winner != 'Y')
      printf("Game was a tie - no winner!\n\n");
    
   return 0;
}


int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/* 
  This function gathers the computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysNotSoRandom in its attempt to place its symbol in 
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;            //this declaration is required if you attempt the bonus part
   
   winningSpot = computerPlaysToWin(board, computerRow, computerCol);
   
   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user 
   {
     //computerPlaysNotSoRandom(computerRow, computerCol, userRow, userCol);
     
     /*
     If you attempt the bonus part, then use the code below to first try and block user move
     If unsuccessful, then it pick row and col (pseudo) randomly
     */
     
     blocked = computerPlaysToBlock(board, computerRow, computerCol);
     if (blocked == 0)
       computerPlaysNotSoRandom(computerRow, computerCol, userRow, userCol);
     
     
   }
 
   return winningSpot;
}


void readUserMove(int * userRow, int * userCol, int * steps){
/* 
  This function prompts the user to input values to place symbol X on the board
  It also calculates the number of times the user enters such values
 */

   printf("Your move - enter numbers between 1 and %d \n\n", N);

   printf("Enter row number: ");
   scanf("%d", userRow);

   printf("Enter column number: ");
   scanf("%d", userCol);
   
   *steps = *steps  + 1;
}

int isInputValid(int entered, int minimum, int maximum){
  return minimum <= entered && entered <= maximum;
}

int isBoardFull(char board[N][N]){
  int i = 0, j = 0;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if(board[i][j] == '?'){
        return 0;
      } 
    }
  }
  return 1;
}

void createInitialBoard(char board[N][N]){
  int i = 0, j = 0;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      board[i][j] = '?';
    }
  }
  printCurrentBoard(board);
}

void printCurrentBoard(char board[N][N]){
  int i = 0, j = 0;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      printf(" %c ", board[i][j]);
      if(j != N-1) {
        printf("|");
      }
    }
    if(i != N-1){
      printf("\n-----------\n");
    }
  }
  printf("\n");
}

int gameWon(char board[N][N], char symbol){
  int i = 0;
  int sumR[N], sumC[N], sumLD = 0, sumRD = 0;
  for (i = 0; i < N; ++i)
  {
    sumR[i] = 0;
    sumC[i] = 0;
  }
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

  if (sumLD == 12 || sumLD == 3 || sumRD == 12 || sumRD == 3)
  {
    return 1;
  }

  for (i = 0; i < N; ++i)
  {
    if (sumR[i] == 12 || sumR[i] == 3 || sumC[i] == 12 || sumC[i] == 3)
    {
      return 1;
    }
  }

  return 0;
}

int computerPlaysToWin(char board[N][N], int *cRow , int *cCol){
  int i = 0, j = 0;
  int sumR[N], sumC[N], sumLD = 0, sumRD = 0;
  for (i = 0; i < N; ++i)
  {
    sumR[i] = 0;
    sumC[i] = 0;
  }
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);
  
  //CHECK LEFT DIAGONAL
  if (sumLD == 8)
  {
    for (i = 0; i < N; ++i)
    {
      if (board[i][i] == '?')
      {
        *cRow = i;
        *cCol = i;
        return 1;
      }
    }
  }

  //CHECK RIGHT DIAGONAL
  if (sumRD == 8)
  {
    for (i = 0; i < N; ++i)
    {
      for (j = N-1; j >= 0; ++j)
      {
        if (board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
      
    }
  }

  //CHECK ROWS
  for (i = 0; i < N; ++i)
  {
    if (sumR[i] == 8)
    {
      for (j = 0; j < N; ++j)
      {
        if (board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }

  //CHECK COLS
  for (i = 0; i < N; ++i)
  {
    if (sumC[i] == 8)
    {
      for (j = 0; j < N; ++j)
      {
        if (board[j][i] == '?')
        {
          *cRow = j;
          *cCol = i;
          return 1;
        }
      }
    }
  }

  return 0;
}

void computerPlaysNotSoRandom(int * cRow, int * cCol, int uRow, int uCol){
  srand(time(NULL));
  int randomnumber = rand() % 3;
  int randomInc =0;
  //same row
  if (randomnumber == 0)
  {
    /* code */
    *cRow = uRow;
    if (uCol == 0)
    {
      *cCol = rand() % 2 + 1;
    }
    else if (uCol == 1)
    {
      if (rand() % 2)
      {
        *cCol = 0;
      }
      else
      {
        *cCol = 2;
      }
      
    }
    else if (uCol == 2)
    {
      if (rand() % 2)
      {
        *cCol = 0;
      }
      else
      {
        *cCol = 1;
      }
    }

  }
  //same col
  else if (randomnumber == 1)
  {
    /* code */
    *cCol = uCol;
    if (uRow == 0)
    {
      *cRow = rand() % 2 + 1;
    }
    else if (uRow == 1)
    {
      if (rand() % 2)
      {
        *cRow = 0;
      }
      else
      {
        *cRow = 2;
      }
      
    }
    else if (uRow == 2)
    {
      if (rand() % 2)
      {
        *cRow = 0;
      }
      else
      {
        *cRow = 1;
      }
      
    }
  }
  //same diagonally
  else if (randomnumber == 2)
  {
    /* code */
    if (uRow == 0 && uCol == 0)
    {
      randomInc = rand() % 2 + 1;
      *cRow = randomInc;
      *cCol = randomInc;
    }
    else if (uRow == 2 && uCol == 0)
    {
      randomInc = rand() % 2 + 1;
      *cRow = 2 - randomInc;
      *cCol = 0 + randomInc;
    }
    else if (uRow == 0 && uCol == 2)
    {
      randomInc = rand() % 2 + 1;
      *cRow = 0 + randomInc;
      *cCol = 2 - randomInc;
    }
    else if (uRow == 2 && uCol == 2)
    {
      randomInc = rand() % 2 + 1;
      *cRow = 2 - randomInc;
      *cCol = 2 - randomInc;
    }
    else if (uRow == 1 && uCol == 1)
    {
      randomInc = rand() % 4;
      if (randomInc == 0)
      {
        *cRow = uRow + 1;
        *cCol = uCol + 1;
      }
      else if (randomInc == 1)
      {
        *cRow = uRow - 1;
        *cCol = uCol - 1;
      }
      else if (randomInc == 2)
      {
        *cRow = uRow + 1;
        *cCol = uCol - 1;
      }
      else if (randomInc == 3)
      {
        *cRow = uRow - 1;
        *cCol = uCol + 1;
      }      
    }
  }
}

void sumAllDimensions(char board [N][N], int sumR[N], int sumC[N], int * sumLD, int * sumRD){
  int i = 0, j = 0;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if(board[i][j] == 'O'){
        sumR[i] += 4;
        sumC[j] += 4;
        if (i == 1 && j == 1)
        {
          *sumLD += 4;
          *sumRD += 4;
        }
        else if (i == j)
        {
          *sumLD += 4;
        }   
      }
      else if(board[i][j] == 'X'){
        sumR[i] += 1;
        sumC[j] += 1;
        if (i == 1 && j == 1)
        {
          *sumLD += 1;
          *sumRD += 1;      
        }
        else if (i == j)
        {
          *sumLD += 1;
        }   
      }
    }
  }
}

int memberOf(int aNum, int someArray[N]){
  int i = 0;
  for (i = 0; i < N; ++i)
  {
    if (someArray[i] == aNum)
    {
      return 1;
    }
  }
  return 0;
}

int computerPlaysToBlock(char board[N][N], int * cRow, int * cCol){
  int i = 0, j = 0;
  int sumR[N], sumC[N], sumLD = 0, sumRD = 0;
  for (i = 0; i < N; ++i)
  {
    sumR[i] = 0;
    sumC[i] = 0;
  }
  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);
  
  //CHECK LEFT DIAGONAL
  if (sumLD == 2)
  {
    for (i = 0; i < N; ++i)
    {
      if (board[i][i] == '?')
      {
        *cRow = i;
        *cCol = i;
        return 1;
      }
    }
  }

  //CHECK RIGHT DIAGONAL
  if (sumRD == 2)
  {
    for (i = 0; i < N; ++i)
    {
      for (j = N-1; j >= 0; ++j)
      {
        if (board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
      
    }
  }

  //CHECK ROWS
  for (i = 0; i < N; ++i)
  {
    if (sumR[i] == 2)
    {
      for (j = 0; j < N; ++j)
      {
        if (board[i][j] == '?')
        {
          *cRow = i;
          *cCol = j;
          return 1;
        }
      }
    }
  }

  //CHECK COLS
  for (i = 0; i < N; ++i)
  {
    if (sumC[i] == 2)
    {
      for (j = 0; j < N; ++j)
      {
        if (board[j][i] == '?')
        {
          *cRow = j;
          *cCol = i;
          return 1;
        }
      }
    }
  }

  return 0;
}
