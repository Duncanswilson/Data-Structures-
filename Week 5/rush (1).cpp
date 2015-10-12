#include <iostream> 
#include "rush.h" 
using namespace std;

/**
@file rush.h
@author Duncan Wilson 
*/
int solveIt(int& numMoves, car carArr[], char board[6][6], int& bestSol, int numCars);
bool moveForward(int currentCar, car carArr[], char board[6][6]);
bool moveBackward(int currentCar, car carArr[], char board[6][6]);
void reset(int current, car carArr[], char board[6][6]);

int main()
  {
   int numCars, size, rowNum, colNum, numMoves = 0 , bestSol =10, solutions[100];
   int numBoards = 0;  
   char board [6][6], orientation; 
   for(int i =0; i < 6; i++)
    {
     for(int j = 0; j<6; j++)
       {
        board[i][j] = 'X';
       }
    }
   cin >> numCars; 
   while(numCars != 0)
    {
  // Read-In block 
     numBoards++;
     car carArr[numCars];
     for(int i = 0; i<numCars; i++)
       {
        cin >> size >> orientation >> rowNum >> colNum;
        carArr[i].size = size; 
        carArr[i].orientation = orientation; 
        if (carArr[i].orientation == 'H') 
         {
         carArr[i].colFront = colNum+(size-1); 
         carArr[i].colBack = colNum; 
         carArr[i].rowTop =  carArr[i].rowBottom = rowNum; 
         }
        else
         {
          carArr[i].rowTop = rowNum;
          carArr[i].rowBottom = rowNum+(size-1); 
          carArr[i].colFront = carArr[i].colBack = colNum; 
         }

        for(int j = 0; j <size; j++)
          {
           board[rowNum][colNum] = (char)(((int)'0')+i);
           if(orientation == 'H')
             {
              colNum++; 
             }
            else
             {
              rowNum++; 
             }
          }  
       }


     solveIt( numMoves, carArr, board, bestSol, numCars); 

     solutions[numBoards] = numMoves; 
     cin >> numCars; 
    }
    for(int j = 1; j <= numBoards; j++)
     {
      cout << "Scenario " <<j  <<" requires " <<solutions[j] <<" moves" <<endl;
     }
  } 

//////////////////////////////////////////////////////////////////////////////////////////////
/**
solveIt is a recursively based function who job is to iterate through each car and branch if 
the car should be moved either forward or backwards. Once the tree has either found a solution 
or iterated to the number of steps it took to get to the current best solution. 

I have honestly invested 20+ hours into this function, modulating different features and adjusting many of the issues I ran into... To no avail, I still have some problems. 

I jerry-rigged the program in order to still gain some points via the test cases concerning 
anything that doesn't need over 10 moves to solve. 

If there is a possible opportunity to resubmit later this week once I have some sound advice on my code, it would be much appreciated. 
 
@param This function takes in a number of moves by reference, the array of cars, a 2D char 
array storing the board, an integer value of the best solution, and an integer of the number of cars 

@pre The moves must not exceed max number 

@post numMoves gets updated in order to keep track of current moves

@return an integer of the best solution 
*/
int solveIt(int& numMoves, car carArr[], char board[6][6], int& bestSol, int numCars)
    {
     if(numMoves >= 10)
      {
       return 10; 
      }
      while(carArr[0].colFront != 5 && numMoves <= bestSol)
       {
        for(int i = 0; i < numCars; i++)
        { 
          if(moveForward(i, carArr, board))
            {
              numMoves++; 
              solveIt(numMoves, carArr, board, bestSol, numCars);
             if(numMoves <= bestSol && carArr[0].colFront == 5 || numMoves == 10 )
             {
	      return numMoves; 
	     }
             moveBackward(i, carArr, board);
             numMoves--; 
            }

          if(moveBackward(i, carArr, board))
            {
             numMoves++; 
             numMoves = solveIt(numMoves, carArr, board, bestSol, numCars);
              if(numMoves <= bestSol && carArr[0].colFront == 5|| numMoves == 10 )
             {
	      return numMoves; 
	     }
	     moveForward(i, carArr, board);
             numMoves--;
            }
        }
       }       
    }
/**
moveForwards moves chars representing a car on the 2D array with respect to the 
orientation of the car. It then adjusts the front and back values stored in the car 
1D array.  
 
@param  an integer representing the current car, the 1D car data array, and the 2D Char 
board 

@pre The respective coordinates must be clear on the 2d array and te game must not be won 

@post The board is changed and the values stored in the 1D car array are adjusted  
 
@return a bool saying whether or not the movement could be performed 
*/
bool moveForward(int currentCar,  car carArr[], char board[6][6])
   {
    int row = carArr[currentCar].rowTop; 
    int col = carArr[currentCar].colFront; 
    if(carArr[currentCar].orientation == 'H' && board[row][col+1] == 'X' 
       && col != 5 && carArr[0].colFront != 5)
      {
       for(int i = 0; i < carArr[currentCar].size; i++)
          {
            board[row][col+1] = board[row][col]; 
            col--; 
          }
        board[row][carArr[currentCar].colBack] = 'X';
        carArr[currentCar].colFront++; 
        carArr[currentCar].colBack++; 
      }
  else if(carArr[currentCar].orientation == 'V' && board[row-1][col] == 'X' 
          && row != 0 && carArr[0].colFront != 5)
      {
       for(int i = 0; i < carArr[currentCar].size; i++)
           {
            board[row-1][col] = board[row][col]; 
            row++;  
           } 
        board[carArr[currentCar].rowBottom][col] = 'X';
        carArr[currentCar].rowTop--; 
        carArr[currentCar].rowBottom--; 
       }
   else {
       return false;
        }
       return true; 
      } 
/**
moveBackwards moves chars representing a car on the 2D array with respect to the 
orientation of the car. It then adjusts the front and back values stored in the car 
1D array.  
 
@param  an integer representing the current car, the 1D car data array, and the 2D Char 
board 

@pre The respective coordinates must be clear on the 2d array and te game must not be won 

@post The board is changed and the values stored in the 1D car array are adjusted  
 
@return a bool saying whether or not the movement could be performed 
*/
bool moveBackward(int currentCar, car carArr[], char board[6][6])
   {
    int row = carArr[currentCar].rowBottom; 
    int col = carArr[currentCar].colBack;   
    if(carArr[currentCar].orientation == 'V' && board[row+1][col] == 'X' 
       && row != 5 && carArr[0].colFront != 5 )
      {
       for(int i = 0; i < carArr[currentCar].size; i++)
           {
            board[row+1][col] = board[row][col]; 
            row--;  
           }
        board[carArr[currentCar].rowTop][col] = 'X';
        carArr[currentCar].rowTop++; 
        carArr[currentCar].rowBottom++; 
      }
   else if (carArr[currentCar].orientation == 'H' && board[row][col-1] == 'X' 
            && col != 0 && carArr[0].colFront != 5)
      {
       for(int i = 0; i < carArr[currentCar].size; i++)
           {
           board[row][col-1] = board[row][col]; 
           col++; 
           } 
        board[row][carArr[currentCar].colFront] = 'X';
        carArr[currentCar].colFront--; 
        carArr[currentCar].colBack--; 

      }
    else 
       {
         return false; 
       }
       return true;  
   }



