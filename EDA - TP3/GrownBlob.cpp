#include "GrownBlob.h"

#define MAXGROWNFOOD 4

GrownBlob::GrownBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_):

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_){

	this->maxFoodAmount = MAXGROWNFOOD;
}

GrownBlob::GrownBlob() {};

GrownBlob::GrownBlob(Blob* otherBlob) {
	this->position = *otherBlob->getBlobPosition();
}