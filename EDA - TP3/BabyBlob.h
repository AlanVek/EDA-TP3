#pragma once
#include "Blob.h"
class BabyBlob : public Blob{
public:
	BabyBlob(unsigned int screenWidth, unsigned int screenHeight,
		unsigned int maxSpeed_, float relativeSpeed_, unsigned int smellRadius_, float deathProb_);

	BabyBlob();


	BabyBlob(Blob* otherBlob, float randomJ);

	~BabyBlob();
};


