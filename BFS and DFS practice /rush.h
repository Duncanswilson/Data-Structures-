#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std; 
#ifndef CAR_H
#define CAR_H
/**
@file rush.h
@author Duncan Wilson 
*/
struct boardStruct{
 boardStruct();
 class car {
  public:
  car(); 
  ~car();
  car(const car& src);
  car& operator= (const car& src);
////////////////////////////////////
  int size; 
  char orientation; 
  int row;
  int col;
 };
////////////////////////////////////
void create(int carNum);
///////////////////////////////////
char boardData[6][6];
string strConvert; 
int numMoves; 
car *carArr; 
};
#endif

boardStruct::car::car()
  {
   size =0 ; 
   orientation =0; 
   row = 0;
   col = 0;
  }
boardStruct::car::~car()
 {}
boardStruct::car:: car(const car& src)
{}

boardStruct::boardStruct()
  { 
   numMoves = 0; 
   ////create an X out board /////
   for(int i =0; i < 6; i++)
    {
     for(int j = 0; j<6; j++)
       {
        boardData[i][j] = 'X';
       }
    }
  }
void boardStruct::create(int carNum)
 {
   carArr = new car[carNum];
   int size, rowNum, colNum; 
   char orientation; 
     for(int i = 0; i<carNum; i++)
       {
        cin >> size >> orientation >> rowNum >> colNum;
        carArr[i].size = size; 
        carArr[i].orientation = orientation; 
        if (carArr[i].orientation == 'H') 
         {
          carArr[i].col = colNum;  
          carArr[i].row =  rowNum; 
         }
 //place in 2d array 
       for(int j = 0; j <size; j++)
          {
           boardData[rowNum][colNum] = (char)i;
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
}

