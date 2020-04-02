#include "GoodOldBlob.h"

#define MAXOLDFOOD 3

GoodOldBlob::GoodOldBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_) :

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_) {

	//Explicitly sets canMerge to false (GoodOldBlobs can't blobMerge).
	this->canMerge = false;

	this->maxFoodAmount = MAXOLDFOOD;
}

GoodOldBlob::GoodOldBlob() {};


GoodOldBlob::GoodOldBlob(Blob* otherBlob) {
	this->position = *otherBlob->getBlobPosition();
}