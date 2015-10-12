#include <string>
#include <map>
#include <iostream> 

using namespace std;
// Class Header File
class car{
    public:
        // member functions
            car();
            car(const car &source);
            car& operator=(const car &source); 
        // data members
            int carNum;
            int size;
            char orientation;
            int col;
            int row;
};
 
class board{
    public:
        // member functions
            board();
            bool moveForward(int carNum);
            void undoForward(int carNum);
            bool moveBackward(int carNum);
            void undoBackward(int carNum); //
            string toString() const;
            void setMap(); // iterates through the carList, setting the characters in the carMap
            void printMap(); // loops through the map, printing in a proper format
            bool isSolved(); // checks if the map is a solution to the board
        // data members
            char carMap[6][6]; // character map of the cars on the board
            map<int, car> carList; // BST of cars on the board
            int numCars; // number of cars on the board
            int numMoves; // number of moves so far
};
