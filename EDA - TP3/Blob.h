#pragma once

#include "Food.h"

typedef struct {
	float x;
	float y;
} Position;

class Blob
{
public:
	
	//Class constructor. 
	Blob(unsigned int screenWidth, unsigned int screenHeight, unsigned int relativeSpeed_, 
		unsigned int maxSpeed_, unsigned int smellRadius_, float deathProb_);
			
	void blobDeath(void);
	bool blobFeeding(void);
	bool checkFoodEaten(void);
	void blobMove(void);
	bool checkIfMerge(void);
	void blobCorrectMovement(void);
	void blobMerge(void);
	void blobSmell(Food* foodVector_, int lenght);

	Position* getBlobPosition(void);

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

