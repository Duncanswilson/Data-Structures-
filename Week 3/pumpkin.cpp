#include <iostream> 
#include <fstream> 

using namespace std; 

const int MAX_ROW = 42; 
const int MAX_COL = 42; 

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
    char pumpkinPatch[MAX_ROW][MAX_COL];  

    while(patchRowSize != 0 && patchColSize != 0)
      {
       cin >> patchRowSize >>patchColSize;   
       if(patchRowSize != 0 && patchColSize != 0)
         {
          for(int i = 0; i < MAX_ROW; i++)
            {
             for(int j = 0; j < MAX_COL; j++)
                {
                 if(i == 0 || j == 0 || i >= patchRowSize+1
                    || j >= patchColSize+1)
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
             row = patchRowSize+1; 
            col = patchColSize+1; 
            found = patchFinder (pumpkinPatch, row, col); 
            if(found == true) 
              {
               patchNumber++; 
               size = patchCounter(pumpkinPatch, row, col); 
               dataArr[gardenIndex][index] = size; 
               index++; 
              } 
           }
    //  cout << "this is the number of patches, garden index: " <<patchNumber 
     //       <<" , "  <<gardenIndex <<endl;  
      dataArr[gardenIndex] [0] = patchNumber; 
      gardenIndex++;
          }
      }
//////////
   /*         for(int n = 0; n < 5; n++)
            {
             cout << endl; 
             for(int x = 0; x < 5; x++)
                { 
                  cout<< dataArr[n][x] <<' ';
                }
            } 
/////////*/
    for(index = 0; index < gardenIndex; index++)
       {
        cout<< "Garden # " <<index+1 <<" : " <<dataArr[index][0] 
            << " patches, sizes:";
             sort(dataArr, index); 
        for(int h = 1; h <= dataArr[index][0]; h++)
           {       
             cout <<" " << dataArr[index][h]; 
           }
        cout << endl; 
       }
   }
   
char fetchData()
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
        //check above for more pumpkins 
        total += patchCounter(patch, rowI+1, colI); 
        //check left for more pumpkins 
        total += patchCounter(patch, rowI, colI+1);
        //check below for more pumpkins 
        total += patchCounter(patch, rowI-1, colI);
        //check right for more pumpkins  
        total += patchCounter(patch, rowI, colI-1); 
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
          /* cout << endl << "# of patches: " <<arr[rowNum][0] <<endl;
           cout << "i =  : "<< i <<" thee val @ i =: " <<arr[rowNum][i] <<" & i+1: " <<arr[rowNum][i+1] <<endl;*/  
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


bool patchFinder(char field[][MAX_COL], int& rowNum, int& colNum)
   {
    int rowI = 0; 
    int colI  = 0;
    while (field[rowI][colI] != 'p' && rowI < rowNum)
      {
       colI = 0; 
       while(field[rowI][colI] != 'p' && colI < colNum)
          {
           colI++;
     
           if(field[rowI][colI] == 'p')
             {
              
              rowNum = rowI; 
              colNum = colI;
              return true; 
             }
          }
       if(field[rowI][colI] != 'p')
         {
          rowI++; 
         }
     }
  return false;
  }


