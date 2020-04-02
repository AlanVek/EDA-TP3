#pragma once

#include "Food.h"

typedef struct {
	float x;
	float y;
} Position;

class Blob
{
public:
	
	Blob();
	//Class constructor. 
	Blob(unsigned int screenWidth, unsigned int screenHeight, float relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_);


	Blob(const Blob* otherBlob);
			
	bool checkBlobDeath(void);
	int blobFeeding(Food** foodVector_, int amount, int* birthFlag);
	bool checkFoodEaten(void);
	void blobMove(unsigned int width_, unsigned int height_);
	bool checkIfMerge(void);
	void blobCorrectMovement(unsigned int width_, unsigned int height_);
	void blobMerge(void);
	void blobSmell(Food** foodVector_, int lenght);
	bool checkIfFull(void);

	Position* getBlobPosition(void);

	virtual ~Blob();

	bool willMerge;

protected:
	Position position;
	
	
	//Porcentual speed, between 0 and 1.
	float relativeSpeed;
	
	//Max speed reachable by this blob.
	float maxSpeed;

	float angle;
	int smellRadius;
	float deathProb;
	unsigned int foodEaten;
	bool canMerge;
	int maxFoodAmount;
};

