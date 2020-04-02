#define _USE_MATH_DEFINES

#include "Blob.h"
#include <random>
#include <cmath>
#include <math.h>
#include <iostream>

#define BITMAP_WIDTH 30
#define MAX_ANGLE 2*M_PI

//Blob constructors.
Blob::Blob() {};

Blob::Blob(const Blob* otherBlob) : position(otherBlob->position) {};


Blob::Blob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
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

//Checks for nearest food within smellRadius.
void Blob::blobSmell(Food** foodVector_, int lenght) {
	Position temp;
	
	//Vector to store all food within smellRadius.
	Position tempVector[1000];
	float xDist, yDist;
	int size = 0;
	//Has to check the whole array.
	for (int i = 0; i < lenght; i++) {

		//Gets food position.
		temp.x = foodVector_[i]->getXPosit();
		temp.y = foodVector_[i]->getYPosit();

		//Defines distances.
		xDist = (temp.x - this->position.x);
		yDist = (temp.y - this->position.y);

		//If food is within smellRadius, that potencial new food target is added to the vector.
		if (abs(xDist) < this->smellRadius && abs(yDist) < this->smellRadius) {
			tempVector[size] = temp;
			size++;
		}
	}

	if (size) {
		//Gets food with minimum distance to blob.
		temp = tempVector[getMinDist(tempVector, size)];
		xDist = (temp.x - this->position.x);
		yDist = (temp.y - this->position.y);

		//Changes angle to point to nearest food.
		this->angle = atan2(yDist, xDist);
	}
}

//Gets blob's position.
Position* Blob::getBlobPosition(void) { return &this->position; }

//Corrects movement in case blob went outside of display. Instead, it appears through the other side.
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

//Checks if blob is on top of food and modifies foodEaten accordingly.
int Blob::blobFeeding(Food** foodVector_, int amount, int* birthFlag) {
	float xPos, yPos, xDist, yDist;
	int result = -1;

	*birthFlag = 0;

	for (int i = 0; i < amount; i++) {

		xPos = foodVector_[i]->getXPosit();
		yPos = foodVector_[i]->getYPosit();

		xDist = this->position.x - xPos;
		yDist = this->position.y - yPos;

		if (abs(xDist)<BITMAP_WIDTH && abs(yDist)<BITMAP_WIDTH) {
			result = i;
			i = amount;
			this->foodEaten++;
		}
	}

	//Checks if blob "is full" (will trigger a blobBirth).
	if (this->checkFoodEaten())
		*birthFlag = 1;
	return result;
}

/*Generates a random number between 0 and 1 and, if it's smaller than
the blob's probability of death, then the blob dies. */
bool Blob::checkBlobDeath(void) {

	double specificity = 0.001;

	int dividend = 1 / specificity;

	double num = specificity * (rand() % dividend);

	
	return (num < this->deathProb);
}

//Adds the blob's parameters with those of the one that's merging with it.
void Blob::willMerge(Blob* thisBlob) {
	this->maxSpeed += thisBlob->maxSpeed;
	this->relativeSpeed += thisBlob->relativeSpeed;
	this->angle += thisBlob->angle;
}

//Sets mean value for each parameter.
void Blob::hasMerged(int thisMerge) {
	this->angle /= thisMerge;
	this->maxSpeed /= thisMerge;
	this->foodEaten = 0;
	this->relativeSpeed /= thisMerge;
}

//Class getters.
float Blob::getMaxSpeed(void) { return this->maxSpeed; }
float Blob::getRelativeSpeed(void) { return this->relativeSpeed; }
float Blob::getAngle(void) { return this->angle; }
int Blob::getSmellRadius(void) { return this->smellRadius; }
float Blob::getBitmapWidth(void) { return this->bitmapWidth; }
float Blob::getDeathProb(void) { return this->deathProb; }



//Finds the food that is closest to blob.
int Blob::getMinDist(Position* tempPosVector, int size) {
	int minPos = 0;
	float tempDist;
	float minDist = sqrt(pow(this->position.x - (*tempPosVector).x, 2) + pow(this->position.y - (*tempPosVector).y, 2));

	for (int i = 0; i < size; i++) {
		tempDist = sqrt(pow(tempPosVector[i].x - this->position.x, 2) + pow(tempPosVector[i].y - this->position.y, 2));
		if (tempDist < minDist) {
			minDist = tempDist;
			minPos = i;
		}	
	}
	return minPos;
}

Blob::~Blob() {};

