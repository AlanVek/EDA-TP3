#include "Blob.h"
#include <random>

#define CORRECTOR 0.0001
#define MAX_ANGLE 360

//Blob constructor.
Blob::Blob(unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_,
	unsigned int maxSpeed_,unsigned int smellRadius_, float deathProb_) {
	
	//Generates random X and Y position, and random angle.
	this->position.x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenWidth - CORRECTOR));
	this->position.y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenHeight - CORRECTOR));
	this->angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (MAX_ANGLE));
	
	
	//Sets given speeds and smellRadius.
	this->relativeSpeed = relativeSpeed_;
	this->maxSpeed = maxSpeed_;
	this->smellRadius = smellRadius_;
	
	//When "born", all Blobs have eaten 0 food and can merge.
	this->foodEaten = 0;
	this->deathProb = deathProb_;

	this->blobImage = nullptr;

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