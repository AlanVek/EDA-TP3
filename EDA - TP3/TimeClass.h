#pragma once
#include <allegro5/allegro.h>

#define defaultFPS 10.0
class TimeClass {
public:
	TimeClass(ALLEGRO_TIMER* timer_ = NULL,double FPS = defaultFPS);
	
	void setTimer(double FPS_ = defaultFPS);
	void startTimer(void);
	bool createTimer(void);
	ALLEGRO_TIMER* getTimer(void);

	void destroyTimer(void);
private:
	ALLEGRO_TIMER* Timer;
	double FPS;
};