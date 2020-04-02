#include "Simulation.h"
#include <allegro5/allegro_image.h>
#include "Templates.h"
#include <typeinfo>
#include "GrownBlob.h"
#include "GoodOldBlob.h"
#include "BabyBlob.h"


using namespace std;

//Simulation constructor.
Simulation::Simulation(unsigned int width_, unsigned int height_, double FPS_, unsigned int blobAmount_, 
	unsigned int generalMaxSpeed_, float generalRelativeSpeed_, int mode_, int foodAmount_) : 

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

	deleteArray < Blob* > (this->allBlobs, this->blobAmount);

	deleteArray< Food* > (this->foodVector, this->foodAmount);
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
	float xPos, yPos;
	bool result = true;
	for (int i = 0; i < this->blobAmount; i++) {
		
		if (!(this->allBlobs[i] = new (nothrow) BabyBlob(this->width, this->height, this->generalMaxSpeed,
			this->generalRelativeSpeed, defaultSmellRadius, defaultDeathProb)))
			result = false;

		else {
			xPos = this->allBlobs[i]->getBlobPosition()->x;
			yPos = this->allBlobs[i]->getBlobPosition()->y;
			this->drawAccordingBitmap(this->allBlobs[i]);
		}
	}
	return result;
}



void Simulation::moveCycle(void) {

	float xPos, yPos;

	int hasBeenEaten;
	//Temporary places to point flags.
	int a = 0 , b = 0;

	//Vector with indexes of positions that must merge.
	int mergeIndexVector[MAXBLOBAMOUNT] = { 0 };
	int* mergeFlag = &a;
	int index = 0;
	int* birthFlag = &b;

	//Draws background first (to cover everything).
	this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getBackgrBit(), 0, 0);

	
	//First, it checks for blobDeaths and adjusts blobAmount accordingly.
	for (int i = 0; i < this->blobAmount; i++) {
		if (this->allBlobs[i]->checkBlobDeath())
			this->blobDeath(i);
	}

	//Then, every blob smells for food (and adjusts angles).
	for (int i = 0; i < this->blobAmount; i++) 
		this->allBlobs[i]->blobSmell(this->foodVector, this->foodAmount);

	//Separately, so as to first finish calculations, the blobs move.
	for (int i = 0; i < this->blobAmount; i++) {
		this->allBlobs[i]->blobMove(this->width, this->height);

		//Checks for eaten food.
		hasBeenEaten = this->allBlobs[i]->blobFeeding(this->foodVector, this->foodAmount,birthFlag);
		if ( hasBeenEaten != -1)
			this->foodVector[hasBeenEaten]->NewPosition(this->width, this->height);

		//Checks for potential blobBirth.
		if (*birthFlag) {
			if (!this->blobBirth())
				cout << "Runtime Error. Failed to create new BabyBlob.\n";
		}

		/*//Checks for potential blobMerge. 
		if (*mergeFlag) {
			//Merges the colliding blobs.
			this->mustMerge(mergeIndexVector, index);
		}*/
		this->drawAccordingBitmap(allBlobs[i]);
	}

	//Lastly, the food is redrawn.
	for (int i = 0; i < this->foodAmount; i++) {

		xPos = this->foodVector[i]->getXPosit();
		yPos = this->foodVector[i]->getYPosit();

		this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getFoodBit(), xPos, yPos);
	}

	al_flip_display();
}

void Simulation::drawAccordingBitmap(Blob* thisBlob) {
	float xPos = thisBlob->getBlobPosition()->x;
	float yPos = thisBlob->getBlobPosition()->y;

	float typeID = typeid (*thisBlob).hash_code();

	//If it's a BabyBlob, it draws the babyBit. 
	if (typeID == typeid(BabyBlob).hash_code()) {
		this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getBabyBit(), xPos, yPos);
	}
	else if (typeID == typeid(GrownBlob).hash_code()) {
		this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getGrownBit(),xPos, yPos);
	}
	else if (typeID == typeid(GoodOldBlob).hash_code()) {
		this->getGraphicControl()->drawBitmap(this->getGraphicControl()->getBabyBit(),xPos, yPos);
	}
}


void Simulation::mustMerge(int* mergeVector, int length) {

	float xPos1, xPos2;
	float yPos1, yPos2;
	for (int i = 0; i < length - 1; i++) {
		xPos1 = this->allBlobs[mergeVector[i]]->getBlobPosition()->x;
		yPos1 = this->allBlobs[mergeVector[i]]->getBlobPosition()->y;
		for (int j = 0; j < length; j++) {

			xPos2 = this->allBlobs[mergeVector[j]]->getBlobPosition()->x;
			yPos2 = this->allBlobs[mergeVector[j]]->getBlobPosition()->y;

			if (xPos1 == xPos2 && yPos1 == yPos2) {

				delete this->allBlobs[mergeVector[j]];
				allBlobs[mergeVector[j]] = nullptr;
				allBlobs[mergeVector[j]]->willMerge = true;
			}
		}
	}

	this->actuallyMerge();

}

void Simulation::actuallyMerge(void) {

	float typeID;
	for (int i = 0; i < this->blobAmount; i++) {

		typeID = typeid(*this->allBlobs[i]).hash_code();

		if (this->allBlobs[i]->willMerge) {
			if (typeID == typeid(BabyBlob).hash_code())
				evolve <GrownBlob>(this->allBlobs[i]);

			else if (typeID == typeid(GrownBlob).hash_code())
				evolve <GoodOldBlob>(this->allBlobs[i]);
		}
	}

}

bool Simulation::blobBirth(void) {
	bool result = true;
	if (!(this->allBlobs[this->blobAmount] = new (nothrow) BabyBlob(this->width, this->height, this->generalMaxSpeed,
		this->generalRelativeSpeed, defaultSmellRadius, defaultDeathProb)))
		result = false;
	if (result)
		this->blobAmount++;

	return result;
}

void Simulation::blobDeath(int index) {
	delete this->allBlobs[index];
	cout << "A blob has died.\n";

	for (int i = index; i < this->blobAmount-1; i++) {
		this->allBlobs[i] = this->allBlobs[i + 1];
	}

	this->blobAmount--;

}