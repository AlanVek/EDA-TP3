#pragma once
class Food{
public:

	Food(unsigned int width_, unsigned int height_);

	float getXPosit(void);
	float getYPosit(void);
	

private:
	float xPosit, yPosit;
};

