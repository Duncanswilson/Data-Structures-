/** @file Timer.cpp
@author Frank Mascarich
@version Revision 1.1
@brief this is the implemenation file for the car and board classes.
@date February 23, 2014
**/
#include "carBoard.h"


/**
This is the constructor for the Car class.
 
This function simply sets all default values for a car object. Orientation is set to 'O' to indicate an empty car.
 
@param none
 
@return none
 
@exception none
 
@pre none
 
@post A car will be created with the appropriate default values
 
**/
car::car()
{
    carNum = -1;
    size = 0;
    orientation = 'O';
    col = 0;
    row = 0;
}
/**
This is the copy constructor for the Car class.
 
This function creates a new car which is copied from the source car. All data members are copied except for the next pointer which is set to NULL.
 
@param A source car to copy into the this car
 
@return none
 
@exception none
 
@pre none
 
@post A new car will be allocated with the same data members as the source.
 
**/
 
car::car(const car &source)
{
    carNum = source.carNum;
    size = source.size;
    orientation = source.orientation;
    col = source.col;
    row = source.row;
}

/**
This is the overloaded operator = function for the Car class.
 
This function creates a new car which is copied from the source car. All data members are copied except for the next pointer which is set to NULL.
 
@param A source car to copy into the this car
 
@return none
 
@exception none
 
@pre none
 
@post A new car will be allocated with the same data members as the source.
 
**/
car& car::operator=(const car &source)
{
    carNum = source.carNum;
    size = source.size;
    orientation = source.orientation;
    col = source.col;
    row = source.row;
}
/**
This is the constructor for the board class
 
This function creates a new board with it's character map set to 'O's to indicate an empty map. bestSln is initialized to 11 in order to find a solution of 10  or less. The solve function will not look for a solution which is equal to or longer than the best solution, which initially will max out the branch length to 10.
 
@param none
 
@return none
 
@exception none
 
@pre none
 
@post A new board will be created with default data member values
 
**/
board::board()
{

    for(int i = 0;i<6;i++)
    {
        for(int j = 0;j<6;j++)
        {
            carMap[i][j] = '-';
        }
    }
    numCars = 0;
    numMoves = 0;
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
bool board::moveForward(int carNum)
{
    car* target = &(carList.find(carNum)->second);
    // if the car is horizontal
    if(target->orientation == 'H')
    {
        // if the car is at the top of row/column
        if(target->col == 5 - target->size  + 1)
        {
            return false;
        }
        // if there's another car in the way
        else if(carMap[target->col + target->size][target->row] != '-')
        {
            return false;
        }
        else
        {
        // increment the car's column
            (target->col)++;
            return true;
        }
    }
    // if the car is vertical
    else
    {
        // if the car is at the top of row/column
        if(target->row == 5 - target->size  + 1)
        {
            return false;
        }
        // if there's another car in the way
        else if(carMap[target->col][target->row + target->size] != '-')
        {
            return false;
        }
        else
        {
        // increment the car's row
            (target->row)++;
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
void board::undoForward(int carNum)
{
    car* target = &(carList.find(carNum)->second);

    if(target->orientation == 'V')
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
bool board::moveBackward(int carNum)
{
    car* target = &(carList.find(carNum)->second);
    // if the car is horizontal
    if(target->orientation == 'H')
    {
        // if the car is at the bottom of row/column
        if(target->col == 0)
        {
            return false;
        }
        // if there's another car in the way
        else if(carMap[target->col - 1][target->row] != '-')
        {
            return false;
        }
        else
        {
        // increment the car's column
            (target->col)--;
            return true;
        }
    }
    // if the car is vertical
    else
    {
        // if the car is at the top of row/column
        if(target->row == 0)
        {
            return false;
        }
        // if there's another car in the way
        else if(carMap[target->col][target->row - 1] != '-')
        {
            return false;
        }
        else
        {
        // increment the car's row
            (target->row)--;
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
void board::undoBackward(int carNum)
{
    car* target = &(carList.find(carNum)->second);
    if(target->orientation == 'V')
    {
        (target->row)++;
    }
    else
    {
        (target->col)++;
    }
}
string board::toString() const
{
    string total = "";
    for( int i = 0; i < 6; i++ )
    {
        total += carMap[i];
    }
    return total;
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
void board::setMap()
{
    car* cursor;
    map<int,car>::iterator iterate;
    for(int i =0;i<6;i++)
    {
        for(int j =0; j<6;j++)
        {
            carMap[j][i] = '-';
        }
    }
    for( iterate = carList.begin(); iterate != carList.end(); iterate++ )
    {
        cursor = &(iterate->second);
        carMap[cursor->col][cursor->row] = cursor->carNum+'0';
        if(cursor->orientation == 'H')
        {
            carMap[cursor->col + 1 ][cursor->row] = cursor->carNum+'0';
            if(cursor->size == 3)
            {
                carMap[cursor->col + 2 ][cursor->row] = cursor->carNum+'0';         
            }
        }
        else if(cursor->orientation == 'V')
        {
            carMap[cursor->col ][cursor->row + 1] = cursor->carNum+'0';
            if(cursor->size == 3)
            {
                carMap[cursor->col][cursor->row + 2] = cursor->carNum+'0';          
            }
        }
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
void board::printMap()
{
        cout << "Printing Board************************" << endl;
        for(int i = 0; i < 6;i++)
        {
            for(int j = 0; j< 6; j++)
            {
                cout << carMap[j][i];
            }
            cout << endl;
        }
}
/**
This function determines if the puzzle has been solved and if it is better than the current best solution.
 
This function determines if the puzzle has been solved and if it is better than the current best solution. The board is solved when the first car in the board stack is at the edge of the board.
 
 
@param none
 
@return a bool represeting if the board is solved or not.
 
@exception none
 
@pre none
 
@post If the board is solved and the solution is shorter than the bestSln, bestSln is updated.
 
**/
bool board::isSolved()
{
    if(carList.begin()->second.col + carList.begin()->second.size == 6)
    {
        return true;
    }
    return false;
}
 
 
 
 
 
 
 
 
 
 