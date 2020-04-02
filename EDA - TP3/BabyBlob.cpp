#include "BabyBlob.h"

#define BABYBITWIDTH 25
#define MAXBABYFOOD 5

BabyBlob::BabyBlob(unsigned int screenWidth, unsigned int screenHeight, 
	unsigned int maxSpeed_,float relativeSpeed_, unsigned int smellRadius_, float deathProb_):
	
	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_,deathProb_){

	this->maxFoodAmount = MAXBABYFOOD;
	this->bitmapWidth = BABYBITWIDTH;
}

BabyBlob::BabyBlob() {};

BabyBlob::BabyBlob(Blob* otherBlob, float randomJ) {
	this->position = *otherBlob->getBlobPosition();
	this->maxSpeed = otherBlob->getMaxSpeed();
	this->relativeSpeed = otherBlob->getRelativeSpeed();
	this->angle = otherBlob->getAngle() + randomJ;
	this->maxFoodAmount = MAXBABYFOOD;
	this->smellRadius = otherBlob->getSmellRadius();
	this->foodEaten = 0;
	this->bitmapWidth = BABYBITWIDTH;
}

BabyBlob::~BabyBlob() {};