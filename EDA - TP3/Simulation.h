#pragma once
#include "EventClass.h"
#include "TimeClass.h"
#include "GraphicClass.h"
#include "BabyBlob.h"


//Temporary values to check correct initialization.
/**************************************************/
#define defaultDisplay false
#define MAXBLOBAMOUNT 50
#define defaultWidth 800
#define defaultHeight 800
#define defaultRelativeSpeed 0.5
#define defaultMaxSpeed width/40
#define defaultSmellRadius width/30
#define defaultDeathProb 0.3
/**************************************************/
class Simulation {
public:

	//Simulation constructor.
	Simulation();

	bool setSimulation(bool displayCreation = defaultDisplay);

	void destroyAll();

	bool setAllegro(void);

	GraphicClass* getGraphicControl(void);
	TimeClass* getTimeControl(void);
	EventClass* getEventControl(void);

	bool initializeAll(void);

	void deleteBlobs(int index);

private:

	//Datos miembro de Simulation.
	GraphicClass* graphicControl;
	TimeClass* timeControl;
	EventClass* eventControl;
	Blob* allBlobs[MAXBLOBAMOUNT];
	unsigned int blobAmount;
	unsigned int width, height;
	int mode;

	//For mode 1.
	unsigned int generalMaxSpeed;

	//For mode 2.
	float generalRelativeSpeed;
};