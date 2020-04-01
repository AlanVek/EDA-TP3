#pragma once
#include "Blob.h"
class BabyBlob : public Blob{
public:
	BabyBlob (unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_,float deathProb_);
};

