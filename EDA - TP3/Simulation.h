#pragma once
#include "EventClass.h"
#include "TimeClass.h"
#include "GraphicClass.h"
#include "Blob.h"
#include "Food.h"



#define MAXBLOBAMOUNT 500
#define FOODAMOUNT 100
//Temporary values to check correct initialization.
/**************************************************/
#define defaultDisplay true

#define defaultWidth 900
#define defaultHeight 470
#define defaultFPS 11.0
#define defaultBlobAmount 20
#define defaultMaxSpeed 30
#define defaultRelativeSpeed 0.5
#define defaultMode 1
#define defaultFoodAmount 15
#define defaultSmellRadius 150
#define defaultDeathProb 0.001
#define randomJiggle 0.5
/**************************************************/
class Simulation {
public:

	//Simulation constructor.
	Simulation(unsigned int width_ = defaultWidth, unsigned int height_ = defaultHeight, double FPS_ = defaultFPS,
		unsigned int blobAmount_ = defaultBlobAmount,unsigned int generalMaxSpeed_ = defaultMaxSpeed,
		float generalRelativeSpeed_ = defaultRelativeSpeed,int mode_ = defaultMode, int foodAmount_ = defaultFoodAmount);

	bool setSimulation(bool displayCreation = defaultDisplay);

	void destroyAll();

	bool setAllegro(void);

	GraphicClass* getGraphicControl(void);
	TimeClass* getTimeControl(void);
	EventClass* getEventControl(void);

	bool initializeAll(void);

	unsigned int getBlobAmount(void);

	Blob** getAllBlobs(void);

	bool initializeFood(void);
	bool initializeBlob(void);

	void drawAccordingBitmap(Blob* thisBlob);


	void moveCycle(void);

	void mustMerge(void);
	void actuallyMerge(void);
	
	bool blobBirth(void);
	void blobDeath(int index);

	void drawItAll(void);

	void Merges(void);
private:

	//Datos miembro de Simulation.
	unsigned int blobAmount, foodAmount;
	unsigned int width, height;
	int mode;

	GraphicClass* graphicControl;
	TimeClass* timeControl;
	EventClass* eventControl;
	Blob* allBlobs[MAXBLOBAMOUNT];

	//For mode 1.
	unsigned int generalMaxSpeed;

	//For mode 2.
	float generalRelativeSpeed;

	double FPS;

	Food* foodVector[FOODAMOUNT];
};