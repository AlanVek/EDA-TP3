#pragma once
#include "Blob.h"
class GrownBlob : public Blob{
public:

	//GrownBlob cosntructor.
	GrownBlob(unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_);
};

