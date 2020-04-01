#include "TimeClass.h"


//TimeClass constructor.
TimeClass::TimeClass(ALLEGRO_TIMER* timer_, double FPS_) : Timer(timer_), FPS(FPS_) {};

//Starts timer.
void TimeClass::startTimer(void) { al_start_timer(this->Timer);}

//Class setter.
void TimeClass::setTimer(double FPS_) { FPS = FPS_; }

//Class getter.
ALLEGRO_TIMER* TimeClass::getTimer(void) { return this->Timer; }

//Creates timer.
bool TimeClass::createTimer(void) {
	return (this->Timer = al_create_timer(1 / this->FPS));
}

//Frees memory.
void TimeClass::destroyTimer(void) { 
	if (this->Timer) 
		al_destroy_timer(this->Timer); 
}



