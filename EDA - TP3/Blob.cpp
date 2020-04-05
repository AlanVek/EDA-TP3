#define _USE_MATH_DEFINES

#include "Blob.h"
#include <random>
#include <cmath>
#include <math.h>
#include <iostream>


#define BITMAPWIDTH 10
#define MAX_ANGLE 2*M_PI

//Blob constructors.
Blob::Blob() {};

Blob::Blob(const Blob* otherBlob) : position(otherBlob->position) {};


Blob::Blob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	float maxSpeed_,unsigned int smellRadius_, float deathProb_) {
	
	//Generates random X and Y position, and random angle.
	position.x = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenWidth - BITMAPWIDTH*2)) + BITMAPWIDTH ;
	position.y = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (screenHeight - 2*BITMAPWIDTH)) + BITMAPWIDTH;
	angle = static_cast <double> ((rand()) / (static_cast <double> (RAND_MAX)) * (MAX_ANGLE));
	
	//Sets given speeds and smellRadius.
	relativeSpeed = relativeSpeed_;
	maxSpeed = maxSpeed_;
	smellRadius = smellRadius_;
	
	//When "born", all Blobs have eaten 0 food and can merge.
	foodEaten = 0;
	deathProb = deathProb_;
}

/*Checks if blob has eaten maxFoodAmount of food.
If so, sets foodEaten to 0. */
bool Blob::checkFoodEaten(void) {
	bool result = (foodEaten >= maxFoodAmount);
	if (result)
		foodEaten = 0;

	return result;
}

//Updates blob position.
void Blob::blobMove(unsigned int width_, unsigned int height_) {
	position.x += (maxSpeed * relativeSpeed * cos(angle));
	position.y += (maxSpeed * relativeSpeed * sin(angle));

	//After moving, corrects final position.
	blobCorrectMovement(width_ + BITMAPWIDTH, height_ + BITMAPWIDTH);
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
		xDist = (temp.x - position.x);
		yDist = (temp.y - position.y);

		//If food is within smellRadius, that potencial new food target is added to the vector.
		if (abs(xDist) < smellRadius && abs(yDist) < smellRadius) {
			tempVector[size] = temp;
			size++;
		}
	}

	if (size) {
		//Gets food with minimum distance to blob.
		temp = tempVector[getMinDist(tempVector, size)];
		xDist = (temp.x - position.x);
		yDist = (temp.y - position.y);

		//Changes angle to point to nearest food.
		angle = atan2(yDist, xDist);
	}
}

//Gets blob's position.
Position* Blob::getBlobPosition(void) { return &position; }

//Corrects movement in case blob went outside of display. Instead, it appears through the other side.
void Blob::blobCorrectMovement(unsigned int width_, unsigned int height_) {
	if (position.x >= width_)
		position.x -= width_;
	else if (position.x <= 0)
		position.x += width_;

	if (position.y >= height_)
		position.y -= height_;
	else if (position.y <= 0)
		position.y += height_;
}

//Checks if blob is on top of food and modifies foodEaten accordingly.
int Blob::blobFeeding(Food** foodVector_, int amount, newBirth* thisBirth) {
	float xPos, yPos, xDist, yDist;
	int result = -1;

	thisBirth->birthFlag = 0;

	for (int i = 0; i < amount; i++) {

		xPos = foodVector_[i]->getXPosit();
		yPos = foodVector_[i]->getYPosit();

		xDist = position.x - xPos;
		yDist = position.y - yPos;

		if (abs(xDist)<bitmapWidth/2 && abs(yDist)<bitmapWidth/2) {
			result = i;
			i = amount;
			foodEaten++;
		}
	}

	//Checks if blob "is full" (will trigger a blobBirth).
	if (checkFoodEaten()) {
		thisBirth->birthFlag = 1;
		thisBirth->birthPosition = this->position;
	}
	return result;
}

/*Generates a random number between 0 and 1 and, if it's smaller than
the blob's probability of death, then the blob dies. */
bool Blob::checkBlobDeath(void) {

	double num = 0.0001 * (rand()%10000);
	return (num < deathProb);
}

//Adds the blob's parameters with those of the one that's merging with it.
void Blob::willMerge(Blob* thisBlob) {
	maxSpeed += thisBlob->maxSpeed;
	relativeSpeed += thisBlob->relativeSpeed;
	angle += thisBlob->angle;
}

//Sets mean value for each parameter.
void Blob::hasMerged(int thisMerge) {
	angle /= thisMerge;
	maxSpeed /= thisMerge;
	foodEaten = 0;
	relativeSpeed /= thisMerge;
}

//Class getters.
float Blob::getMaxSpeed(void) { return maxSpeed; }
float Blob::getRelativeSpeed(void) { return relativeSpeed; }
float Blob::getAngle(void) { return angle; }
int Blob::getSmellRadius(void) { return smellRadius; }
float Blob::getBitmapWidth(void) { return bitmapWidth; }
float Blob::getDeathProb(void) { return deathProb; }


/*Finds the food that is closest to blob. It returns its index 
in relation to tempPosVector.*/
int Blob::getMinDist(Position* tempPosVector, int size) {
	int minPos = 0;
	float tempDist;
	float minDist = sqrt(pow(position.x - (*tempPosVector).x, 2) + pow(position.y - (*tempPosVector).y, 2));

	for (int i = 0; i < size; i++) {
		tempDist = sqrt(pow(tempPosVector[i].x - position.x, 2) + pow(tempPosVector[i].y - position.y, 2));
		if (tempDist < minDist) {
			minDist = tempDist;
			minPos = i;
		}	
	}
	return minPos;
}


void Blob::setNewData(float generalMaxSpeed_, float generalRelativeSpeed_, float smellRadius_) {
	maxSpeed = generalMaxSpeed_;
	relativeSpeed = generalRelativeSpeed_;
	smellRadius = smellRadius_;
}

void Blob::setDeathProb(float deathProb_) { deathProb = deathProb_; }

Blob::~Blob() {};

/*
void Blob::setPosition(newBirth thisBirth) {
	position.x = thisBirth.birthPosition.x;
	position.y = thisBirth.birthPosition.y;
}*/
