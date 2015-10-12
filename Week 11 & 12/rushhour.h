#include<map>
#include<string>
using namespace std; 
class parkingLot{
	public:
     parkingLot();
    void setUp(parkingLot& x);
    void setMap();
	bool moveForward(int carNum);	
	bool moveBackward(int carNum);
	void build();
	void findCar(int carNum, int &x, int &y); 
	void print(); 
	bool done(); 
	string convert();
    void reverseF(int carNum); 
    void reverseB(int carNum);

	int numberOfMoves;
	int numberOfCars; 

	struct car{		
		car();	
		int id, size, col, row;
		char direction; 
	};
   char  lot[6][6]; 
   map<int, car>carTree; 
};

