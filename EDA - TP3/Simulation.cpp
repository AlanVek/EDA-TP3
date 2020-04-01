#include "Simulation.h"
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_ttf.h>


#define defaultSmellRadius 30
#define defaultDeathProb 0.3
using namespace std;

//Simulation constructor.
Simulation::Simulation(unsigned int width_, unsigned int height_, double FPS_, unsigned int blobAmount_, 
	unsigned int generalMaxSpeed_, unsigned int generalRelativeSpeed_, int mode_) : 

	width(width_), height(height_), FPS(FPS_), blobAmount(blobAmount_), generalMaxSpeed(generalMaxSpeed_),
	generalRelativeSpeed(generalRelativeSpeed_), mode(mode_){

	this->graphicControl = nullptr;
	this->timeControl = nullptr;
	this->eventControl = nullptr;
}

bool Simulation::initializeAll(void) {
	bool result = true;

	/*Allegro initialization error check*/
	if (!setAllegro()) {
		cout << "Failed to initialize Allegro.\n";
		result = false;
	}

	/*Initialization of graphic resources. Checks for errors.
	True parameter indicates to create a new display. */
	if (!setSimulation(true)) {
		cout << "Failed to set simulation.\n";
		result = false;
	}

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
	else if (!al_init_primitives_addon()) {
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
	}

	return true;
}

/*Creates needed resources and checks for initialization errors.
If there's been one, returns false. If not, returns true. 
If displayCreation is true, it creates a new display.*/
bool Simulation::setSimulation(bool displayCreation) {
	
	bool result = true;

	this->graphicControl = new (nothrow) GraphicClass(this->width, this->height);
	this->eventControl = new (nothrow) EventClass();
	this->timeControl = new (nothrow) TimeClass();
	if (!graphicControl) {
		cout << "Failed to create graphic pointer\n";
		result = false;
	}
	//Attempts to create event queue.
	if (!eventControl->createEventQueue()) {
		cout << "Failed to create event queue\n";
		result = false;
	}

	//Attempts to create timer.
	else if (!timeControl->createTimer(1/this->FPS)) {
		cout << "Failed to create timer\n";
		result = false;
	}

	//Attempts to load font.
	else if (!graphicControl->loadFont()) {
		cout << "Failed to load font\n";
		result = false;
	}
	//Attempts to create display (if requested).
	else if (displayCreation && !graphicControl->createDisplay()) {
		cout << "Failed to create display\n";
		result = false;
	}
	else{
		//Attempts to Initialize allBlobs to default values (for now).
		for (int i = 0; i < this->blobAmount; i++) {
			this->allBlobs[i] = new (nothrow) BabyBlob(this->width, this->height, defaultRelativeSpeed, 
				defaultMaxSpeed, defaultSmellRadius, defaultDeathProb);
			
			//If a certain blob couldn't be created, it deletes the whole array.
			if (!this->allBlobs[i]) {
				this -> deleteBlobs(i);
				result = false;
				i = this->blobAmount;
			}
		}
	}

	//Sets event source for timer.
	if (result)
		al_register_event_source(eventControl->getQueue(), al_get_timer_event_source(timeControl->getTimer()));

	return result;
}

//Deletes all not null Blob pointers up to a certain given index.
void Simulation::deleteBlobs(int index) {
	for (int j = 0; j < index; j++) {
		if (this->allBlobs[j]) {
			this->allBlobs[j]->destroyBitmap();
			delete this->allBlobs[j];
		}
	}
}

//Frees memory.
void Simulation::destroyAll() {
	graphicControl->destroyGraphics();
	eventControl->destroyEventQueue();
	timeControl->destroyTimer();
	deleteBlobs(blobAmount);
}

//Class getters.
GraphicClass* Simulation::getGraphicControl(void) { return this->graphicControl; }
TimeClass* Simulation::getTimeControl(void) { return this->timeControl; }
EventClass* Simulation::getEventControl(void) { return this->eventControl; }