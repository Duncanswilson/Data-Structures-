#include <iostream> 
#include "rush.h" 
using namespace std;



int solveIt(int startingCar, int numMoves, car carArr[], char board[6][6], int& bestSol,
             int numCars);
bool moveForward(int currentCar, car carArr[], char board[6][6]);

bool moveBackward(int currentCar, car carArr[], char board[6][6]);

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
//////////////
      cout<< endl; 
   for(int i =0; i < 6; i++)
    {
     for(int j = 0; j<6; j++)
       {
        cout<< board[i][j];
       }
      cout<< endl;
    }

for(int i =0; i <numCars; i++)
   {
          cout << "Car number "<<i <<" is at orientation: " <<carArr[i].orientation <<endl
               << "Car number "<<i <<" is at: (R(F)) " <<carArr[i].rowTop <<endl
               << "Car number "<<i <<" is at: (C(F)) " <<carArr[i].colFront <<endl
               << "Car number "<<i <<" is at: (R(B)) " <<carArr[i].rowBottom <<endl
               << "Car number "<<i <<" is at: (C(B)) " <<carArr[i].colBack <<endl
               <<endl;
   }

///////////////
   for(int i= 0; i < numCars && numMoves <= bestSol; i++)
     {
     bestSol = solveIt(i, numMoves, carArr, board, bestSol, numCars); 
     } 
     solutions[numBoards] = bestSol; 
     cin >> numCars; 
    }
    for(int j = 1; j <= numBoards; j++)
     {
      cout << "Scenario " <<j  <<" requires " <<solutions[j] <<" moves" <<endl;
     }
  } 

int solveIt(int startingCar, int numMoves, car carArr[], char board[6][6], int& bestSol,
             int numCars)
    {
      if(numMoves <= bestSol && carArr[0].colFront != 5)
       {
        for(int i = startingCar; i < numCars && numMoves <= bestSol; i++)
        { 
///////////////
          cout << "Car number "<<i <<" is at orientation: " <<carArr[i].orientation <<endl
               << "Car number "<<i <<" is at: (R(F)) " <<carArr[i].rowTop <<endl
               << "Car number "<<i <<" is at: (C(F)) " <<carArr[i].colFront <<endl
               << "Car number "<<i <<" is at: (R(B)) " <<carArr[i].rowBottom <<endl
               << "Car number "<<i <<" is at: (C(B)) " <<carArr[i].colBack <<endl
               <<endl
               <<"This is NumMoves " <<numMoves <<endl;
//////////////////

           if( moveForward(i, carArr, board) && carArr[0].colFront != 5)
            {
// Testers 
cout << "Moved forwards " <<endl;
   for(int j =0; j < 6; j++)
    {
     for(int t = 0; t<6; t++)
       {
        cout<< board[j][t];
       }
      cout<< endl;
    }
             numMoves = solveIt(i, numMoves+1, carArr, board, bestSol, numCars);
cout << "This is numMoves (f) " <<numMoves <<endl;

            }
           else if(moveBackward(i, carArr, board) && carArr[0].colFront != 5)
            {
// Testers 
cout << "Moved backwards " <<endl;
   for(int j =0; j < 6; j++)
    {
     for(int t = 0; t<6; t++)
       {
        cout<< board[j][t];
       }
      cout<< endl;
    }
             numMoves = solveIt(i, numMoves+1, carArr, board, bestSol, numCars); 
cout << "This is numMoves (B) " <<numMoves <<endl;
            }
        } 
       }
     return numMoves; 
    }

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
            row--;  
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
            && col != 0 && carArr[0].colFront != 5 )
      {
       for(int i = 0; i < carArr[currentCar].size; i++)
           {
           board[row][col-1] = board[row][col]; 
           col--; 
           } 
        board[row][carArr[currentCar].colBack] = 'X'; 
        carArr[currentCar].colFront--; 
        carArr[currentCar].colBack--; 
      }
    else 
       {
         return false; 
       }
       return true;  
   }
