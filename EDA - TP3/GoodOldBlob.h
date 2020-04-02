#pragma once
#include "Blob.h"
class GoodOldBlob : public Blob{
public:
	GoodOldBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_);

	GoodOldBlob();
};

