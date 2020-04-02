#define _USE_MATH_DEFINES

#include "Blob.h"
#include <random>
#include <cmath>



#define MAX_ANGLE 2*M_PI
#define babyBit "babyblob.png"
//Blob constructor.

Blob::Blob() {};

Blob::Blob(const Blob* otherBlob) : position(otherBlob->position) {};


Blob::Blob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_,unsigned int smellRadius_, float deathProb_) {
	
	//Generates random X and Y position, and random angle.
	this->position.x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenWidth));
	this->position.y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenHeight));
	this->angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (MAX_ANGLE));
	
	this->willMerge = 0;
	
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
void Blob::blobMove(unsigned int width_, unsigned int height_) {
	this->position.x += this->maxSpeed * this->relativeSpeed * cos(this->angle);
	this->position.y += this->maxSpeed * this->relativeSpeed * sin(this->angle);

	//After moving, corrects final position.
	this->blobCorrectMovement(width_, height_);
}

//Checks for food within smellRadius.
void Blob::blobSmell(Food** foodVector_, int lenght) {
	Position temp;
	float xDist, yDist;

	//Has to check the whole array.
	for (int i = 0; i < lenght; i++) {

		//Gets food position.
		temp.x = foodVector_[i]->getXPosit();
		temp.y = foodVector_[i]->getYPosit();

		//Defines distances.
		xDist = (temp.x - this->position.x);
		yDist = (temp.y - this->position.y);

		//If food is within smellRadius, the blob changes its direction to point to the food.
		if (abs(xDist) < this->smellRadius && abs(yDist) < this->smellRadius)
			this->angle = atan2(yDist, xDist);
	}
}

//Gets blob's position.
Position* Blob::getBlobPosition(void) { return &this->position; }

void Blob::blobCorrectMovement(unsigned int width_, unsigned int height_) {
	if (this->position.x >= width_)
		this->position.x -= width_;
	else if (this->position.x <= 0)
		this->position.x += width_;

	if (this->position.y >= height_)
		this->position.y -= height_;
	else if (this->position.y <= 0)
		this->position.y += height_;
}

int Blob::blobFeeding(Food** foodVector_, int amount, int* birthFlag) {
	float xPos, yPos, xDist, yDist;
	int result = -1;

	*birthFlag = 0;

	float totalSpeed = this->maxSpeed * this->relativeSpeed;

	for (int i = 0; i < amount; i++) {

		xPos = foodVector_[i]->getXPosit();
		yPos = foodVector_[i]->getYPosit();

		xDist = this->position.x - xPos;
		yDist = this->position.y - yPos;

		if (abs(xDist)<totalSpeed/sqrt(2) && abs(yDist)<totalSpeed/sqrt(2)) {
			result = i;
			i = amount;
			this->foodEaten++;
		}
	}
	if (this->checkFoodEaten())
		*birthFlag = 1;
	return result;
}

bool Blob::checkBlobDeath(void) {

	double specificity = 0.001;
	double num = specificity * (rand() % (int) (1/specificity));

	return (num < this->deathProb);
}

Blob::~Blob() {};

