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
#include "parkingLot.cpp"
