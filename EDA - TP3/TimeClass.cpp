#include "TimeClass.h"


//TimeClass constructor.
TimeClass::TimeClass(ALLEGRO_TIMER* timer_) : Timer(timer_) {};

//Starts timer.
void TimeClass::startTimer(void) { al_start_timer(this->Timer);}

//Class getter.
ALLEGRO_TIMER* TimeClass::getTimer(void) { return this->Timer; }

//Creates timer.
bool TimeClass::createTimer(double FPS_) {
	return (this->Timer = al_create_timer(1 / FPS_));
}

//Frees memory.
void TimeClass::destroyTimer(void) { 
	if (this->Timer) 
		al_destroy_timer(this->Timer); 
}



