#include "GrownBlob.h"

#define MAXGROWNFOOD 4
#define GROWNBITWIDTH 35

GrownBlob::GrownBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_):

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_){

	this->maxFoodAmount = MAXGROWNFOOD;
	this->bitmapWidth = GROWNBITWIDTH;
}

GrownBlob::GrownBlob() {};

GrownBlob::GrownBlob(Blob* otherBlob, float randomJ) {
	this->position = *otherBlob->getBlobPosition();
	this->maxSpeed = otherBlob->getMaxSpeed();
	this->relativeSpeed = otherBlob->getRelativeSpeed();
	this->angle = otherBlob->getAngle() + randomJ;
	this->maxFoodAmount = MAXGROWNFOOD;
	this->smellRadius = otherBlob->getSmellRadius();
	this->foodEaten = 0;
	this->bitmapWidth = GROWNBITWIDTH;
	this->deathProb = otherBlob->getDeathProb();
}

GrownBlob::~GrownBlob() {}