#pragma once
#include <allegro5/allegro.h>

class TimeClass {
public:
	TimeClass(ALLEGRO_TIMER* timer_ = nullptr);
	
	void startTimer(void);
	bool createTimer(double FPS_);
	ALLEGRO_TIMER* getTimer(void);

	void destroyTimer(void);

private:
	ALLEGRO_TIMER* Timer;
};