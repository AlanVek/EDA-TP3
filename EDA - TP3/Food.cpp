#include "Food.h"
#include <random>

#define foodBit "food.png"
Food::Food(unsigned int width_, unsigned int height_) {
	this->xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_));
	this->yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_));

	this->foodImage = nullptr;
};
bool Food::createBitmap(unsigned int width_, unsigned int height_) {
	bool result = true;
	if (!(this->foodImage = al_create_bitmap(width_, height_)))
		result = false;
	else if (!(this->foodImage = al_load_bitmap(foodBit)))
		result = false;

	return result;
}
void Food::drawBitmap(void) { al_draw_bitmap(this->foodImage, this-> xPosit, this->yPosit, 0); }
void Food::destroyBitmap(void) {
	if (this->foodImage)
		al_destroy_bitmap(foodImage);
}
