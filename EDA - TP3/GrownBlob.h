#pragma once
#include "Blob.h"
class GrownBlob : public Blob{
public:

	//GrownBlob cosntructor.
	GrownBlob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_);

	GrownBlob();
};

