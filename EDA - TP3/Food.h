#pragma once
class Food{
public:

	Food(unsigned int width_, unsigned int height_);

	float getXPosit(void);
	float getYPosit(void);
	
	void NewPosition(unsigned int width_, unsigned int height_);

private:
	float xPosit, yPosit;
};

