#include <queue>
#include<map>
#include<string>
#include<iostream>
using namespace std; 

class parkingLot{
	public:
       parkingLot();
        void setUp(int& count, parkingLot& x);
        void setMap();
	bool moveForward(int carNum);	
	bool moveBackward(int carNum);
        void reverseF(int carNum); 
        void reverseB(int carNum);
	void print(); 
	bool done(); 
	string convert();
	struct car{		
		car();	
		int id, size, col, row;
		char direction; 
	};
   char  lot[6][6]; 
   map<int, car>carTree;
   int numberOfMoves;
   int numberOfCars;  
};
///////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	queue<parkingLot> solveQueue; 
	map<string, int> dejaVuMap;
 	parkingLot x; 
    int count = 0; 
    char holder; 
    bool isDone = 0; 
    cin >> x.numberOfCars;
    while(x.numberOfCars != 0)
    {
      isDone= 0; 
          x.setUp(count, x); 
        while(!solveQueue.empty())
        {
            solveQueue.pop();
        }
          dejaVuMap.clear();
 	  string mapInfo = x.convert();   
	  solveQueue.push(x); 
	  while(!solveQueue.empty() && isDone != 1)
           {
		    x = solveQueue.front(); 
	        for(int i = 0; i < x.numberOfCars; i++)
              {
			if(x.moveForward(i))
             {
              x.setMap();
			  mapInfo = x.convert();
			  if(dejaVuMap.find(mapInfo) == dejaVuMap.end())
                 {
			     dejaVuMap[mapInfo] = 1;
				 x.numberOfMoves++; 
		         if(x.done())
                  {
                  cout << "Scenario " << count << " requires " << x.numberOfMoves << " moves" << endl;
                 isDone = 1; 
		          }        
			     solveQueue.push(x); 
                 x.numberOfMoves--; 
                 }	
                x.reverseF(i);
                x.setMap();
			 }	
			if(x.moveBackward(i))
            {
             x.setMap();
			 mapInfo = x.convert();
			 if(dejaVuMap.find(mapInfo) == dejaVuMap.end())
                {
			     dejaVuMap[mapInfo] = 1;
                 x.numberOfMoves++;
		         if(x.done())
                  {
			       cout << "Scenario " << count << " requires " << x.numberOfMoves << " moves" << endl;
                  isDone = 1; 
		          }             
			     solveQueue.push(x); 
                 x.numberOfMoves--; 					
				} 
               x.reverseB(i);
               x.setMap();
			}	
		  }
     solveQueue.pop(); 	
	}
  cin >> x.numberOfCars;
 }
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/**
This is the constructor for the Car struct.
 
This function sets all default values for a car object. Direction is set to 'X' to indicate an empty car.
@param none
@return none
@exception none
@pre none
@post A car will be created with the appropriate default values
**/
parkingLot::car::car(){

	id = -1; 
	col = row = size = 0; 
	direction = 'X';

}
/**
This is the constructor for the parkingLot class
 
This function creates a new board with it's character map set to 'X's to indicate an empty map. 
@param none
@return none
@exception none
@pre none
@post A new board will be created with default data member values
 
**/
parkingLot::parkingLot()
{

    for(int i = 0;i<6;i++)
    {
        for(int j = 0;j<6;j++)
        {
            lot[i][j] = 'X';
        }
    }
    numberOfCars = 0;
    numberOfMoves = 0;
}
/**
This function moves a car's position forward.
 
This function first determines if a car is horizontal or vertical. The function then determines if there is a car in front of the target car(passed as a parameter). If there is a car in front of the target car, the function returns false. If there is no car, the function determines if the target car is at the edge of the board. If the target is at the edge of the board the function returns false. Otherwise, the function increments the target car's position member corresponding to it's orientation, and returns true.
 
@param The target car to be moved forward
@return Returns a boolean indicating if the move was successful.
@exception none
@pre A car must have been initialized and the map must be representative of the current positions of all the cars in the board's car stack.
@post The target car will be moved up if it is able to do so.
**/
bool parkingLot::moveForward(int carNum)
{
    car* mover = &(carTree.find(carNum)->second);
    // if the car is horizontal
    if(mover->direction == 'H')
    {
        // if the car is at the top of row/column
        if(mover->col == 5 - mover->size  + 1)
        {
            return false;
        }
        // if there's another car in the way
        else if(lot[mover->col + mover->size][mover->row] != 'X')
        {
            return false;
        }
        else
        {
        // increment the car's column
            (mover->col)++;
            return true;
        }
    }
    // if the car is vertical
    else
    {
        // if the car is at the top of row/column
        if(mover->row == 5 - mover->size  + 1)
        {
            return false;
        }
        // if there's another car in the way
        else if(lot[mover->col][mover->row + mover->size] != 'X')
        {
            return false;
        }
        else
        {
        // increment the car's row
            (mover->row)++;
            return true;
        }
    }
 
}
/**
This function reverse's the moveForward function.
This function assumes there is space for the target car to move back to it's original position before the moveforward function.
 
@param The target car to be moved forward
@return none
@exception none
@pre A car must have been move forward for this function to function properly.
@post The target car will be back to it's original position. 
**/
void parkingLot::reverseF(int carNum)
{
    car* target = &(carTree.find(carNum)->second);

    if(target->direction == 'V')
    {
        (target->row)--;
    }
    else
    {
        (target->col)--;
    }
}

/**
This function moves a car's position backward.
 
This function first determines if a car is horizontal or vertical. The function then determines if there is a car behind the target car(passed as a parameter). If there is a car behind the target car, the function returns false. If there is no car, the function determines if the target car is at the edge of the board. If the target is at the edge of the board the function returns false. Otherwise, the function decrements the target car's position member corresponding to it's orientation, and returns true.
 
@param The target car to be moved forward
@return Returns a boolean indicating if the move was successful.
@exception none
@pre A car must have been initialized and the map must be representative of the current positions of all the cars in the board's car stack.
@post The target car will be moved down if it is able to do so.
**/
bool parkingLot::moveBackward(int carNum)
{
    car* mover = &(carTree.find(carNum)->second);
    // if the car is horizontal
    if(mover->direction == 'H')
    {
        // if the car is at the bottom of row/column
        if(mover->col == 0)
        {
            return false;
        }
        // if there's another car in the way
        else if(lot[mover->col - 1][mover->row] != 'X')
        {
            return false;
        }
        else
        {
        // increment the car's column
            (mover->col)--;
            return true;
        }
    }
    // if the car is vertical
    else
    {
        // if the car is at the top of row/column
        if(mover->row == 0)
        {
            return false;
        }
        // if there's another car in the way
        else if(lot[mover->col][mover->row - 1] != 'X')
        {
            return false;
        }
        else
        {
        // increment the car's row
            (mover->row)--;
            return true;
        }
    }
}
/**
This function reverse's the moveBackward function.
 
This function assumes there is space for the target car to move back to it's original position before the moveBackward function.
 
@param The target car to be moved forward
@return none
@exception none
@pre A car must have been move backward for this function to function properly.
@post The target car will be back to it's original position. 
**/
void parkingLot::reverseB(int carNum)
{
    car* target = &(carTree.find(carNum)->second);
    if(target->direction == 'V')
    {
        (target->row)++;
    }
    else
    {
        (target->col)++;
    }
}
/**
This function prints the board's map.
 
This function was for debugging purposes. It prints the board's map to the screen with two loops.
 
@param none
@return none
@exception none
@pre none
@post The map is printed to the console.
**/
void parkingLot:: print(){

	for(int i = 0; i<6; i++){
	
		for(int j = 0; j<6; j++)
          {
			cout<<lot[i][j] <<" ";
	}
   
    cout<<endl;
   }
}
/**
This function determines if the board has been solved and if it is better than the current best solution.
 
@param none
@return a bool represeting if the board is solved or not.
@exception none
@pre none
@post If the board is solved and the solution is shorter than the bestSln, bestSln is updated. 
**/
bool parkingLot::done(){
    if(carTree.begin()->second.col + carTree.begin()->second.size == 6)
    {
        return true;
    }
    return false;
}
 
/**
This function converts the board into a string to be used in the dejaVu comparison. 
 
@param none
@return a string of the board data
@exception none
@pre none
@post If the board is converted into a string.  
**/
string parkingLot::convert(){

	string y = ""; 
    for( int i = 0; i < 6; i++ )
    {
        y += lot[i];
    }
    return y;
}
/**
This function setups the the board at the beginning of the solution iteration. 
It clears previous data and then takes in the car data and places it in the car struct.  
It also increments the count value as well. 

@param count variable and the parkingLot 
@exception none
@pre none
@post the board is reset and setup 
**/
void parkingLot::setUp(int& count, parkingLot& x)
 {
    parkingLot::car temp;
    x.carTree.clear();
    numberOfMoves =0; 
    x.setMap();
    count++;
    for(int i = 0; i < x.numberOfCars; i++)
       {
        cin >> temp.size;
        cin >> temp.direction;
        cin >> temp.row;
        cin >> temp.col;
        temp.id = i;
        x.carTree[i] = temp;
       }
       x.setMap();
 }
/**
This function sets the board's map.
 
This function begins by looping through the board's map, setting all values to 'O' to represent an empty map. It then loops through the board's car stack setting the map based on each car's orientation and size.
 
@param none
@return none
@exception none
@pre The board's stack of car's must be initialized. If it is empty, the top pointer must point to NULL.
@post The map will be representative of the board's car stack data.
**/
void parkingLot::setMap()
{
    car* cursor;
    map<int,car>::iterator it;
    for(int i =0;i<6;i++)
    {
        for(int j =0; j<6;j++)
        {
            lot[j][i] = 'X';
        }
    }
    for( it = carTree.begin(); it != carTree.end(); it++ )
    {
        cursor = &(it->second);
        lot[cursor->col][cursor->row] = cursor->id+'0';
        if(cursor->direction == 'H')
        {
            lot[cursor->col + 1 ][cursor->row] = cursor->id+'0';
            if(cursor->size == 3)
            {
                lot[cursor->col + 2 ][cursor->row] = cursor->id+'0';         
            }
        }
        else if(cursor->direction == 'V')
        {
            lot[cursor->col ][cursor->row + 1] = cursor->id+'0';
            if(cursor->size == 3)
            {
                lot[cursor->col][cursor->row + 2] = cursor->id+'0';          
            }
        }
    }
 
}
