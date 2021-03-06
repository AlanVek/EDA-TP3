#pragma once
#include <allegro5/allegro.h>

class EventClass {
public:
	EventClass(ALLEGRO_EVENT_QUEUE* Queue_ = nullptr);
	bool createEventQueue(void);
	
	int getNextEventType();
	ALLEGRO_EVENT_QUEUE* getQueue(void);
	~EventClass();
	ALLEGRO_EVENT getEvent();

private:
	ALLEGRO_EVENT Event;
	ALLEGRO_EVENT_QUEUE* Queue;
};