// Timer.h
/**
@file Timer.h
@author Duncan Wilson 
*/

#ifndef TIMER_H
#define TIMER_H

#include "sys/time.h"
#include <stdexcept>
#include <iostream>

using namespace std;


class Timer {
  public:
    Timer();
    void start() throw (runtime_error);
    void stop() throw (logic_error);
    double getElapsedTime() const throw (logic_error);

  private:
    timeval beginTime;
    timeval duration;
    bool timerWasStarted;
    bool timerEnded;
};
#endif	// ifndef TIMER_H
