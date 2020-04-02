#include "BabyBlob.h"

#define BABYBITWIDTH 25
#define MAXBABYFOOD 5

BabyBlob::BabyBlob(unsigned int screenWidth, unsigned int screenHeight, 
	unsigned int maxSpeed_,float relativeSpeed_, unsigned int smellRadius_, float deathProb_):
	
	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_,deathProb_){

	maxFoodAmount = MAXBABYFOOD;
	bitmapWidth = BABYBITWIDTH;
}

BabyBlob::BabyBlob() {};

BabyBlob::BabyBlob(Blob* otherBlob, float randomJ) {
	position = *otherBlob->getBlobPosition();
	maxSpeed = otherBlob->getMaxSpeed();
	relativeSpeed = otherBlob->getRelativeSpeed();
	angle = otherBlob->getAngle() + randomJ;
	maxFoodAmount = MAXBABYFOOD;
	smellRadius = otherBlob->getSmellRadius();
	foodEaten = 0;
	bitmapWidth = BABYBITWIDTH;
	deathProb = otherBlob->getDeathProb();
}

BabyBlob::~BabyBlob() {};