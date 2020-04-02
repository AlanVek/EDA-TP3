#pragma once

#include <allegro5/allegro.h>

typedef struct {
	unsigned int x;
	unsigned int y;
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
	Position blobSmell(void);

	Position* getBlobPosition(void);

	bool createBitmap(unsigned int W, unsigned int H,const char* bitName);
	bool loadBitmap(const char* bitmapName);
	void drawBitmap(void);
	void destroyBitmap(void);

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
	ALLEGRO_BITMAP* blobImage;
};

