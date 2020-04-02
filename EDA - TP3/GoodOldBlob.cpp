#include "GoodOldBlob.h"

#define MAXOLDFOOD 3

GoodOldBlob::GoodOldBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_) :

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_) {
	this->maxFoodAmount = MAXOLDFOOD;
}

GoodOldBlob::GoodOldBlob() {};


GoodOldBlob::GoodOldBlob(Blob* otherBlob) {
	this->position = *otherBlob->getBlobPosition();
	this->maxSpeed = otherBlob->getMaxSpeed();
	this->relativeSpeed = otherBlob->getRelativeSpeed();
	this->angle = otherBlob->getAngle();
	this->maxFoodAmount = 3;
	this->smellRadius = 30;
	this->foodEaten = 0;
}

GoodOldBlob::~GoodOldBlob() {
	int a = 1 + 3;
}