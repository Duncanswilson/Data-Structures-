#include<map>
#include<string>
#include <iostream>
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

parkingLot::car::car(){

	id = -1; 
	col = row = size = 0; 
	direction = 'X';

}

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
void parkingLot:: print(){

	for(int i = 0; i<6; i++){
	
		for(int j = 0; j<6; j++)
          {
			cout<<lot[i][j] <<" ";
	}
   
    cout<<endl;
   }
}
bool parkingLot::done(){
    if(carTree.begin()->second.col + carTree.begin()->second.size == 6)
    {
        return true;
    }
    return false;
}
 

string parkingLot::convert(){

	string y = ""; 
    for( int i = 0; i < 6; i++ )
    {
        y += lot[i];
    }
    return y;
}

void parkingLot::setUp(int& count, parkingLot& x)
 {
    parkingLot::car temp;
    x.carTree.clear();
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

