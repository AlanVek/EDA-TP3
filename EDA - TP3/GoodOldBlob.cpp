#include "GoodOldBlob.h"

#define MAXOLDFOOD 3
#define GOODOLDBITWIDTH 100

GoodOldBlob::GoodOldBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_) :

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_) {
	this->maxFoodAmount = MAXOLDFOOD;
	this->bitmapWidth = GOODOLDBITWIDTH;
}

GoodOldBlob::GoodOldBlob() {};


GoodOldBlob::GoodOldBlob(Blob* otherBlob, float randomJ) {
	this->position = *otherBlob->getBlobPosition();
	this->maxSpeed = otherBlob->getMaxSpeed();
	this->relativeSpeed = otherBlob->getRelativeSpeed();
	this->angle = otherBlob->getAngle() + randomJ;
	this->maxFoodAmount = MAXOLDFOOD;
	this->smellRadius = otherBlob->getSmellRadius();
	this->foodEaten = 0;
	this->bitmapWidth = GOODOLDBITWIDTH;
	this->deathProb = otherBlob->getDeathProb();
}

GoodOldBlob::~GoodOldBlob() {}