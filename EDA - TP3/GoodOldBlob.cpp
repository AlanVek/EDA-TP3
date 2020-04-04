#include "GoodOldBlob.h"

#define MAXOLDFOOD 3
#define GOODOLDBITWIDTH 70

GoodOldBlob::GoodOldBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_) :

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_) {
	maxFoodAmount = MAXOLDFOOD;
	bitmapWidth = GOODOLDBITWIDTH;
}

GoodOldBlob::GoodOldBlob() {};


GoodOldBlob::GoodOldBlob(Blob* otherBlob, float randomJ) {
	position = *otherBlob->getBlobPosition();
	maxSpeed = otherBlob->getMaxSpeed();
	relativeSpeed = otherBlob->getRelativeSpeed();
	angle = otherBlob->getAngle() + randomJ;
	maxFoodAmount = MAXOLDFOOD;
	smellRadius = otherBlob->getSmellRadius();
	foodEaten = 0;
	bitmapWidth = GOODOLDBITWIDTH;
	deathProb = otherBlob->getDeathProb();
}

GoodOldBlob::~GoodOldBlob() {}