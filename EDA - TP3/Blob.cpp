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

//Updates blob position.
void Blob::blobMove(void) {
	this->position.x = this->maxSpeed * this->relativeSpeed * cos(this->angle);
	this->position.y = this->maxSpeed * this->relativeSpeed * sin(this->angle);
}

//Checks for food within smellRadius.
void Blob::blobSmell(Food* foodVector_, int lenght) {
	Position temp;
	float xDist, yDist;

	//Has to check the whole array.
	for (int i = 0; i < lenght; i++) {

		//Gets food position.
		temp.x = (foodVector_+i)->getXPosit();
		temp.y = (foodVector_+i)->getYPosit();

		//Defines distances.
		xDist = (temp.x - position.x);
		yDist = (temp.y - position.y);

		//If food is within smellRadius, the blob changes its direction to point to the food.
		if (abs(xDist) < this->smellRadius && abs(yDist) < this->smellRadius)
			this->angle = atan(yDist / xDist);
	}
}

//Gets blob's position.
Position* Blob::getBlobPosition(void) { return &this->position; }