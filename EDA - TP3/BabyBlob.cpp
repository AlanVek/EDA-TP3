#include "BabyBlob.h"

#define MAXBABYFOOD 5

BabyBlob::BabyBlob(unsigned int screenWidth, unsigned int screenHeight, 
	unsigned int maxSpeed_,float relativeSpeed_, unsigned int smellRadius_, float deathProb_):
	
	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_,deathProb_){

	this->maxFoodAmount = MAXBABYFOOD;
}

BabyBlob::BabyBlob() {};

BabyBlob::BabyBlob(Blob* otherBlob) {
	this->position = *otherBlob->getBlobPosition();
	this->maxSpeed = otherBlob->getMaxSpeed();
	this->relativeSpeed = otherBlob->getRelativeSpeed();
	this->angle = otherBlob->getAngle();
	this-> maxFoodAmount = 5;
	this->smellRadius = 30;
	this->foodEaten = 0;
}

BabyBlob::~BabyBlob() {
	int a = 1 + 2;
}