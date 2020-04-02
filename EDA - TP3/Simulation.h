#pragma once
#include "EventClass.h"
#include "TimeClass.h"
#include "GraphicClass.h"
#include "BabyBlob.h"
#include "Food.h"


#define MAXBLOBAMOUNT 50
#define FOODAMOUNT 10
//Temporary values to check correct initialization.
/**************************************************/
#define defaultDisplay true

#define defaultWidth 900
#define defaultHeight 470
#define defaultFPS 10.0
#define defaultBlobAmount 10
#define defaultMaxSpeed (int)(defaultWidth/40)
#define defaultRelativeSpeed 0.5
#define defaultMode 1
#define defaultFoodAmount 10
/**************************************************/
class Simulation {
public:

	//Simulation constructor.
	Simulation(unsigned int width_ = defaultWidth, unsigned int height_ = defaultHeight, double FPS_ = defaultFPS,
		unsigned int blobAmount_ = defaultBlobAmount,unsigned int generalMaxSpeed_ = defaultMaxSpeed,
		unsigned int generalRelativeSpeed_ = defaultRelativeSpeed,int mode_ = defaultMode, int foodAmount_ = defaultFoodAmount);

	bool setSimulation(bool displayCreation = defaultDisplay);

	void destroyAll();

	bool setAllegro(void);

	GraphicClass* getGraphicControl(void);
	TimeClass* getTimeControl(void);
	EventClass* getEventControl(void);

	bool initializeAll(void);

	void deleteBlobs(int index);

	unsigned int getBlobAmount(void);

	Blob** getAllBlobs(void);

	bool loadFood(void);

	void deleteFood(int index);

	bool initializeFood(void);
	bool initializeBlob(void);

private:

	//Datos miembro de Simulation.
	GraphicClass* graphicControl;
	TimeClass* timeControl;
	EventClass* eventControl;
	Blob* allBlobs[MAXBLOBAMOUNT];

	unsigned int blobAmount,foodAmount;
	unsigned int width, height;
	int mode;

	//For mode 1.
	unsigned int generalMaxSpeed;

	//For mode 2.
	float generalRelativeSpeed;

	double FPS;

	Food* foodVector[FOODAMOUNT];
};