#include "Simulation.h"
//#include <allegro5\allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define foodBitmap "food.png"

#define defaultSmellRadius 30
#define defaultDeathProb 0.3
#define babyBitmap "babyblob.png"
using namespace std;

//Simulation constructor.
Simulation::Simulation(unsigned int width_, unsigned int height_, double FPS_, unsigned int blobAmount_, 
	unsigned int generalMaxSpeed_, unsigned int generalRelativeSpeed_, int mode_, int foodAmount_) : 

	width(width_), height(height_), FPS(FPS_), blobAmount(blobAmount_), generalMaxSpeed(generalMaxSpeed_),
	generalRelativeSpeed(generalRelativeSpeed_), mode(mode_), foodAmount(foodAmount_){

	this->graphicControl = nullptr;
	this->timeControl = nullptr;
	this->eventControl = nullptr;
}

bool Simulation::initializeAll(void) {
	bool result = true;

	/*Allegro initialization error check*/
	if (!this->setAllegro()) {
		cout << "Failed to initialize Allegro.\n";
		result = false;
	}

	/*Initialization of graphic resources. Checks for errors.
	True parameter indicates to create a new display. */
	else if (!this->setSimulation(true)) {
		cout << "Failed to set simulation.\n";
		result = false;
	}
	/*else if (!this->loadFood()) {
		cout << "Failed to load food.\n";
		result = false;
	}*/
	
	return result;
}

/*Initializes Allegro and its addons. Return false and prints
the correspondent message if any process failed. */
bool Simulation::setAllegro(void) {
	bool result = true;
	if (!al_init()) {
		cout << "Failed to Initialize Allegro\n";
		result = false;
	}

	//Attempts to initialize image addon.
	else if (!al_init_image_addon()) {
		cout << "Failed to initialize image addon\n";
		result = false;
	}
	/*else if (!al_init_primitives_addon()) {
		cout << "Failed to initialize primitives addon\n";
		result = false;
	}
	else if (!al_init_font_addon()) {
		cout << "Failed to initialize font addon\n";
		result = false;
	}
	else if (!al_init_ttf_addon()) {
		cout << "Failed to initialize ttf font addon\n";
		result = false;
	}*/

	return result;
}

/*Creates needed resources and checks for initialization errors.
If there's been one, returns false. If not, returns true. 
If displayCreation is true, it creates a new display.*/
bool Simulation::setSimulation(bool displayCreation) {

	bool result = true;

	this->graphicControl = new (nothrow) GraphicClass(this->width, this->height);
	this->eventControl = new (nothrow) EventClass();
	this->timeControl = new (nothrow) TimeClass();
	if (!this->graphicControl) {
		cout << "Failed to create graphic pointer\n";
		result = false;
	}
	else if (!this->eventControl) {
		cout << "Failed to create event pointer\n";
		result = false;
	}
	else if (!this->timeControl) {
		cout << "Failed to create time pointer\n";
		result = false;
	}
	//Attempts to create event queue.
	else if (!this->eventControl->createEventQueue()) {
		cout << "Failed to create event queue\n";
		result = false;
	}

	//Attempts to create timer.
	else if (!this->timeControl->createTimer(this->FPS)) {
		cout << "Failed to create timer\n";
		result = false;
	}

	/*//Attempts to load font.
	else if (!this->graphicControl->loadFont()) {
		cout << "Failed to load font\n";
		result = false;
	}*/
	//Attempts to create display (if requested).
	else if (displayCreation && !this->graphicControl->createDisplay()) {
		cout << "Failed to create display\n";
		result = false;
	}
	//Attempts to create bitmaps.
	else if (!this->getGraphicControl()->initializeBitmaps(this->width, this->height)) {
		cout << "Failed to load background bitmaps\n";
		result = false;
	}
	else {
		//Draws background.
		this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getBackgrBit(),0,0);
		al_flip_display();
	}
	if (result) {
		//Attempts to Initialize allBlobs to default values (for now) and create bitmaps.
		if (!(initializeBlob())) {
			cout << "Failed to create blobs\n";
			result = false;
		}
		//Attempts to Initialize foodVector to default values (for now) and create bitmaps.
		else if (!initializeFood()) {
			cout << "Failed to create food\n";
			result = false;
		}
		al_flip_display();
	}

	//Sets event source for timer and shows drawings.
	if (result) {
		al_register_event_source(this->eventControl->getQueue(), al_get_timer_event_source(this->timeControl->getTimer()));
		al_flip_display();
	}
	return result;
}

//Frees memory.
void Simulation::destroyAll() {
	this->graphicControl->destroyGraphics();
	this->eventControl->destroyEventQueue();
	this->timeControl->destroyTimer();

	delete this->graphicControl;
	delete this->timeControl;
	delete this->eventControl;

	this->deleteBlobs(this->blobAmount);
	this->deleteFood(this->foodAmount);
}


//Class getters.
GraphicClass* Simulation::getGraphicControl(void) { return this->graphicControl; }
TimeClass* Simulation::getTimeControl(void) { return this->timeControl; }
EventClass* Simulation::getEventControl(void) { return this->eventControl; }
unsigned int Simulation::getBlobAmount(void) { return this->blobAmount; }
Blob** Simulation::getAllBlobs(void) { return allBlobs; }

//Creates food, loads bitmaps and draws them.
bool Simulation::initializeFood (){

	bool result = true;
	for (int i = 0; i < this->foodAmount; i++) {
		if (!(this->foodVector[i] = new (nothrow) Food(this->width, this->height)))
			result = false;
		else
			this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getFoodBit(),
				this->foodVector[i]->getXPosit(),this->foodVector[i]->getYPosit());
	}
	return result;
}

//Creates blobs, loads bitmaps and draws them.
bool Simulation::initializeBlob() {

	bool result = true;
	for (int i = 0; i < this->blobAmount; i++) {
		if (!(this->allBlobs[i] = new (nothrow) BabyBlob(this->width, this->height, this->generalRelativeSpeed, this->generalMaxSpeed,
			defaultSmellRadius, defaultDeathProb)))
			result = false;

		else
			this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getBabyBit(), 
				this->allBlobs[i]->getBlobPosition()->x, this->allBlobs[i]->getBlobPosition()->y);
	}
	return result;
}

//Deletes blob pointers.
void Simulation::deleteBlobs(int index) {
	for (int i = 0; i < index; i++) {
		if (this->allBlobs[i]) 
			delete allBlobs[i];
	}
}

//Deletes food pointers.
void Simulation::deleteFood(int index) {
	for (int i = 0; i < index; i++) {
		if (this->foodVector[i])
			delete foodVector[i];
	}
}
