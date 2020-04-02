#include "Blob.h"
#include <random>

#define MAX_ANGLE 360
#define babyBit "babyblob.png"
//Blob constructor.
Blob::Blob(unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_,
	unsigned int maxSpeed_,unsigned int smellRadius_, float deathProb_) {
	
	//Generates random X and Y position, and random angle.
	this->position.x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenWidth));
	this->position.y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenHeight));
	this->angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (MAX_ANGLE));
	
	
	//Sets given speeds and smellRadius.
	this->relativeSpeed = relativeSpeed_;
	this->maxSpeed = maxSpeed_;
	this->smellRadius = smellRadius_;
	
	//When "born", all Blobs have eaten 0 food and can merge.
	this->foodEaten = 0;
	this->deathProb = deathProb_;

	this->blobImage = NULL;

	//Sets canMerge to default "true" (most likely case scenario).
	this->canMerge = true;
}

/*Checks if blob has eaten maxFoodAmount of food.
If so, sets foodEaten to 0. */
bool Blob::checkFoodEaten(void) {
	bool result = (this->foodEaten == this->maxFoodAmount);
	if (result)
		this->foodEaten = 0;
	return result;
}

//Frees memory taken up by bitmap.
void Blob::destroyBitmap(void) {
	if (this->blobImage)
		al_destroy_bitmap(blobImage);
}


bool Blob::createBitmap(unsigned int W, unsigned int H,const char* bitName) {
	bool result = true;
	
	if (!(this->blobImage = al_create_bitmap(W, H)))
		result = false;
	else if (!(this->blobImage = al_load_bitmap(bitName)))
		result = false;
	else
		al_draw_bitmap(this->blobImage,position.x,position.y,0);

	return result;
}

bool Blob::loadBitmap(const char* bitmapName) {
	return (this->blobImage = al_load_bitmap(bitmapName));
}

void Blob::drawBitmap(void) { al_draw_bitmap(blobImage,position.x,position.y,0); }
