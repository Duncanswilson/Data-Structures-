// Timer.cpp
/**    
@file Timer.cpp
@brief This class can be instantiated in order to time operations. It consists of three functions: a
start(), a stop(), and a getElapsed(). It throws logic errors and notifies user if any foul data 
manipulation is attempted                     
@version Original Code 1.00 (02/18/2014)
@author Duncan Wilson     
*/
#ifndef TIMER_CPP
#define TIMER_CPP

Timer::Timer() : beginTime(), duration() {
timerWasStarted = false;
timerEnded = false; 
}
/**
start assigns, using the function gettimeofday a value to beginTime, then assigns the 
timerWasStarted to true

@post BeginTime is set using gettimeofday and timerWasStarted is set accurately 

@exception If the microseconds of begin time do not get set correctly, throw a runtime error and notify the user

@return N/A the functions void 
*/
void Timer::start() throw (runtime_error) {
    gettimeofday(&beginTime, NULL);
   if( beginTime.tv_usec == 0 && beginTime.tv_sec == 0) {
	throw runtime_error("gettimeofday() returned -1. Serious problem. Can't run timer.");
   }
  timerWasStarted = true; 
}
/**
stop assigns, using the function gettimeofday a value to duration, subtracts the values of duration with the \
values of beginTime then assigns the timerEnded to true

@post  Durarion is set using gettimeofday and subtraction and timerEnded is set accurately 

@exception If timerwasStarted is false, throw a logic error and notify the user

@return N/A the functions void 
*/
void Timer::stop() throw (logic_error){
    if( !timerWasStarted)  {
	throw logic_error("Timer was never started.");
   }
    gettimeofday(&duration, NULL);
    duration.tv_sec = (duration.tv_sec -  beginTime.tv_sec);
    duration.tv_usec = (duration.tv_usec -  beginTime.tv_usec);
    timerEnded = true; 
}
/**
getElapsedTime assigns the double value timeE with correct sum of duration's contents and returns it 

@post TimeE is set to the adjusted seconds in duration added to the microseconds 

@exception If timerEnded is false, throw a logic error and notify the user

@return A double value of the elapsed time 
*/
double Timer::getElapsedTime() const throw (logic_error) {
    if(!timerEnded)  {
      	throw logic_error("Timer was never started.");
}
   double timeE = (duration.tv_sec) * 1000000 + ((double)duration.tv_usec); ;
   return timeE/(double)CLOCKS_PER_SEC;
}

#endif	//#ifndef TIMER_CPP
