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
		float maxSpeed_, unsigned int smellRadius_, float deathProb_);


	Blob(const Blob* otherBlob);
	
	//Checkers.
	bool checkBlobDeath(void);
	int blobFeeding(Food** foodVector_, int amount, int* birthFlag);
	bool checkFoodEaten(void);
	void blobMove(unsigned int width_, unsigned int height_);
	void blobCorrectMovement(unsigned int width_, unsigned int height_);
	void blobSmell(Food** foodVector_, int lenght);

	//Getters.
	float getMaxSpeed(void);
	float getRelativeSpeed(void);
	float getAngle(void);
	int getSmellRadius(void);
	float getBitmapWidth(void);
	float getDeathProb(void);
	Position* getBlobPosition(void);

	//Merge.
	void willMerge(Blob* thisBlob);
	void hasMerged(int thisMerge);


	int getMinDist(Position* tempPosVector, int size);

	void setNewData(float generalMaxSpeed_, float generalRelativeSpeed_, float smellRadius_);

	void setDeathProb(float deathProb_);

	virtual ~Blob();


protected:
	Position position;
	int maxFoodAmount;
	
	//Porcentual speed, between 0 and 1.
	float relativeSpeed;
	
	//Max speed reachable by this blob.
	float maxSpeed;

	float angle;
	int smellRadius;
	float deathProb;
	unsigned int foodEaten;

	float bitmapWidth;
};

