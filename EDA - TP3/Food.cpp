#include "Food.h"
#include <random>

#define foodBit "food.png"
Food::Food(unsigned int width_, unsigned int height_) {
	this->xPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (width_));
	this->yPosit = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (height_));

};

//Get food position.
float Food::getXPosit(void) { return this->xPosit; }
float Food::getYPosit(void) { return this->yPosit; }
