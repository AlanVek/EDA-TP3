#include "Food.h"
#include <random>

#define FOODBITWIDTH 20

#define foodBit "food.png"
Food::Food(unsigned int width_, unsigned int height_) {
	xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_ - 2 * FOODBITWIDTH)) + FOODBITWIDTH;
	yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_ - 2 * FOODBITWIDTH)) + FOODBITWIDTH;

};

//Get food position.
float Food::getXPosit(void) { return xPosit; }
float Food::getYPosit(void) { return yPosit; }


void Food::NewPosition(unsigned int width_, unsigned int height_) {
	xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_));
	yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_));
}
