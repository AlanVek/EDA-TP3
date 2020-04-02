#pragma once
#include <allegro5/allegro.h>
class Food{
public:

	Food(unsigned int width_, unsigned int height_);
	bool createBitmap(unsigned int width_, unsigned int height_);
	void drawBitmap(void);
	void destroyBitmap(void);

private:
	float xPosit, yPosit;
	ALLEGRO_BITMAP* foodImage;

};

