#include "GrownBlob.h"

#define MAXGROWNFOOD 3

GrownBlob::GrownBlob(unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_,
	unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_):

	Blob(screenWidth, screenHeight, relativeSpeed_, maxSpeed_, smellRadius_, deathProb_){

	this->maxFoodAmount = MAXGROWNFOOD;
}