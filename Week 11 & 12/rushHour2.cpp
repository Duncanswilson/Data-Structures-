#include <queue>
#include <map>
#include <iostream>
#include "carBoard.cpp"
//#include "Timer.cpp"

using namespace std;
 
int main()
{
 
    // variables
    char tempChar;
    int count = 0;
    bool done = false;
    car tempCar;
    board game;
    queue<board> gameQueue;
    map<string, int> dejaVu;
//Timer gameTime;

    // read in the first board size
    cin >> game.numCars;
    // loop while not done
    while(game.numCars != 0 && cin.good())
    {
        done = false;
        while(!gameQueue.empty())
        {
            gameQueue.pop();
        }
        dejaVu.clear();
        // read in the cars (while input char != 0)
            // create a new board
            game.carList.clear();
            game.setMap();
            count++;
                // loop through the board size
                for(int i = 0; i < game.numCars; i++)
                {
                    // read in carSize
                        cin >> tempCar.size;
                    // read in orientation
                        cin >> tempCar.orientation;
                    // read in row
                        cin >> tempCar.row;
                    // read in column
                        cin >> tempCar.col;

                    //label the car
                        tempCar.carNum = i;

                    //put it on the board
                        game.carList[i] =tempCar;
                }
                //update the game's 2D array to match the car list
                game.setMap();
        // Solve the board
            // put the board on the queue
                gameQueue.push(game);
            // loop while the queue !empty & !done
//gameTime.start();

                while(!gameQueue.empty() && !done)
                {
                    // get the game at the front of the queue
                    game = gameQueue.front();
                    // loop through numCars
                    for(int i = 0; i < game.numCars && !done; i++)
                    {
                    // if moveforward
                        if(game.moveForward(i))
                        {
                            game.setMap();
                            if( dejaVu.find( game.toString() ) == dejaVu.end() )
                            {
                                dejaVu[ game.toString() ] = count;
                                game.numMoves++;
                            // check is solved
                                if(game.isSolved())
                                {
                                    done = true;
                                    cout << "Scenario " << count << " requires " << game.numMoves << " moves" << endl;
//gameTime.stop();
//cout << "Game Time : " << gameTime.getElapsedTime() << endl;
                                }
                            // put the new board on the queue
                                gameQueue.push(game);
                            // move back
                                game.numMoves--;
                            }
                            game.undoForward(i);
                            game.setMap();
                        }
                    // if moveback
                        if(game.moveBackward(i))
                        {
                            game.setMap();
                            if( dejaVu.find( game.toString() ) == dejaVu.end() )
                            {
                                dejaVu[ game.toString() ] = count;
                                game.numMoves++;
                            // check is solved
                                if(game.isSolved())
                                {
                                    done = true;
                                    cout << "Scenario " << count << " requires " << game.numMoves << " moves" << endl;
//gameTime.stop();
//cout << "Game Time : " << gameTime.getElapsedTime() << endl;
                                }
                            // put the new board on the queue
                                gameQueue.push(game);
                            // move forward
                                game.numMoves--;
                            }
                            game.undoBackward(i);
                            game.setMap();
                        }
                    }
                // remove the front board

                gameQueue.pop();
                }
        // read in the new size
        cin >> game.numCars;
    }
 
 
 
 
}
