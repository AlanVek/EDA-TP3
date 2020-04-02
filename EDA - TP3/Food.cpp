#include "Food.h"
#include <random>

#define foodBit "food.png"
Food::Food(unsigned int width_, unsigned int height_) {
	xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_));
	yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_));

};

//Get food position.
float Food::getXPosit(void) { return xPosit; }
float Food::getYPosit(void) { return yPosit; }


void Food::NewPosition(unsigned int width_, unsigned int height_) {
	xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_));
	yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_));
}
