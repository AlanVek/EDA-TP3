#include "GrownBlob.h"

#define MAXGROWNFOOD 4
#define GROWNBITWIDTH 35

GrownBlob::GrownBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_):

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_){

	maxFoodAmount = MAXGROWNFOOD;
	bitmapWidth = GROWNBITWIDTH;
}

GrownBlob::GrownBlob() {};

GrownBlob::GrownBlob(Blob* otherBlob, float randomJ) {
	position = *otherBlob->getBlobPosition();
	maxSpeed = otherBlob->getMaxSpeed();
	relativeSpeed = otherBlob->getRelativeSpeed();
	angle = otherBlob->getAngle() + randomJ;
	maxFoodAmount = MAXGROWNFOOD;
	smellRadius = otherBlob->getSmellRadius();
	foodEaten = 0;
	bitmapWidth = GROWNBITWIDTH;
	deathProb = otherBlob->getDeathProb();
}

GrownBlob::~GrownBlob() {}