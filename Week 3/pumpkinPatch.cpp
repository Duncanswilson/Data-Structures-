#include <iostream> 
#include <fstream> 

using namespace std; 

const int MAX_ROW = 41; 
const int MAX_COL = 41; 

char fetchData(); 
int patchCounter(char [][MAX_COL], int, int); 
void sort(int [MAX_ROW][MAX_COL], int);
bool patchFinder(char [][MAX_COL], int&, int&); 
int main()
   {
    int patchRowSize = -1; 
    int patchColSize = -1;
    int dataArr[MAX_ROW][MAX_COL]; 
    int index = 0;
    int patchIndex = 0; 
    int  gardenIndex = 0; 

    while(patchRowSize != 0)
      {
       cin >> patchRowSize >>patchColSize;  
       if(patchRowSize != 0 && patchColSize != 0)
         {
          char pumpkinPatch[patchRowSize][patchColSize]; 
          for(int i = 0; i < patchRowSize +2; i++)
            {
             for(int j = 0; j < patchColSize+2; j++)
                {
                 if(i == 0 || j == 0 || i == patchRowSize+1
                    || j == patchColSize+1)
                    {
                     pumpkinPatch[i][j] = 'X'; 
                    }
                 else 
                    {
                     pumpkinPatch[i][j] = fetchData(); 
                    }
                }
            }

      int row, col, size, patchNumber = 0;
      bool found = true; 
      index = 1; 
      while(found == true)
           {
            row = patchRowSize +2; 
            col = patchColSize +2; 
            found = patchFinder (pumpkinPatch, row, col); 
            if(found = true) 
              {
               patchNumber++; 
               size = patchCounter(pumpkinPatch, row, col); 
               dataArr[patchIndex][index] = size; 
               index++; 
              } 
           }
      dataArr[gardenIndex] [0] = patchNumber; 
      gardenIndex++;
         }
      }
    for(index = 0; index < gardenIndex; index++)
       {
        sort(dataArr, index+1); 
        cout<< "Garden # " <<index+1 <<": " <<dataArr[index][0] 
            << "patches, sizes: " ;
        for(int h = 1; h <= dataArr[index][0]; h++)
           {
             cout << dataArr[index][h] <<" "; 
           }
        cout << endl; 
       }
   }
   
char fecthData()
   { 
    char data;
    cin >> data;
    return data; 
   }

int patchCounter(char patch[][MAX_COL], int rowI, int colI)
   { 
     int total = 0; 
     if(patch[rowI][colI] == 'p')
      {
        total++;
        patch[rowI][colI] = 'x';
        //check below for more pumpkins 
        total += patchCounter(patch, rowI-1, colI); 
        //check above for more pumpkins 
        total += patchCounter(patch, rowI+1, colI); 
        //check right for more pumpkins  
        total += patchCounter(patch, rowI, colI-1); 
        //check left for more pumpkins 
        total += patchCounter(patch, rowI, colI+1);
      }
      return total; 
      }

void sort(int arr[MAX_ROW][MAX_COL], int rowNum)
   {  
    bool sorted = true; 
    while(sorted == true)
      {
       sorted = false; 
       for(int i = 1; i < arr[rowNum][0]; i++)
          {
            if(arr[rowNum][i] > arr[rowNum][i+1])
              {
               int temp; 
               temp = arr[rowNum][i+1]; 
               arr[rowNum][i+1] = arr[rowNum][i]; 
               arr[rowNum][i] = temp; 
               sorted = true; 
              }
          }
      }   
   } 


bool patchFinder(char field[][MAX_COL], int rowNum, int colNum)
   {
    int rowI = 0; 
    int colI  = 0; 
    while (field[rowI][colI] != 'p' && rowI < rowNum)
      {
       colI = 0; 
       while(field[rowI][colI] != 'p' && colI < colNum)
          {
           colI++;
          }
       if(field[rowI][colI] != 'p')
         {
          rowI++; 
         }
     }
   if(field[rowI][colI] != 'p')
     {
       return false;
     }
  rowNum = rowI; 
  colNum = colI; 
  return true; 
  }


