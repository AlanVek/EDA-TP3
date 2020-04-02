#include "Simulation.h"
#include <allegro5/allegro_image.h>
#include "Templates.h"
#include <typeinfo>
#include "GrownBlob.h"
#include "GoodOldBlob.h"
#include "BabyBlob.h"
#include <allegro5/keyboard.h>

#define radius 15

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

	al_install_keyboard();

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
	else if (!this->graphicControl->initializeBitmaps(this->width, this->height)) {
		cout << "Failed to load background bitmaps\n";
		result = false;
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
		al_register_event_source(this->eventControl->getQueue(), al_get_keyboard_event_source());
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

	deleteArray < Food* > (this->foodVector, this->foodAmount);
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
			this->graphicControl->drawBitmap(this->graphicControl->getFoodBit(),
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
	//Temporary place to point flag.
	int a = 0;
	int* birthFlag = &a;

	//First, it checks for blobDeaths and adjusts blobAmount accordingly.
	for (int i = 0; i < this->blobAmount; i++) {
		if (this->allBlobs[i]->checkBlobDeath()) {
			this->blobDeath(i);
			i--;
		}
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
	}

	//Checks for merges and does the necessary changes.
	this->Merges();

	this->drawItAll();

	al_flip_display();
}

void Simulation::drawAccordingBitmap(Blob* thisBlob) {
	float xPos = thisBlob->getBlobPosition()->x;
	float yPos = thisBlob->getBlobPosition()->y;

	float typeID = typeid (*thisBlob).hash_code();

	//If it's a BabyBlob, it draws the babyBit. 
	if (typeID == typeid (BabyBlob).hash_code()) {
		this->graphicControl->drawBitmap(this->graphicControl->getBabyBit(), xPos, yPos);
	}

	//If it's a GrownBlob, it draws the grownBit.
	else if (typeID == typeid (GrownBlob).hash_code()) {
		this->graphicControl->drawBitmap(this->graphicControl->getGrownBit(),xPos, yPos);
	}

	//If it's a GoodOldBlob, it draws the goodBit.
	else if (typeID == typeid (GoodOldBlob).hash_code()) {
		this->graphicControl->drawBitmap(this->graphicControl->getGoodBit(),xPos, yPos);
	}
}


//Checks for overlapped same-age-group blobs and blobMerges them.
void Simulation::Merges() {

	float xPos1, xPos2;
	float yPos1, yPos2;

	float typeID;
	float xDist, yDist;
	int thisMerge;
	if (this->blobAmount) {
		for (int i = 0; i < this->blobAmount - 1; i++) {

			typeID = typeid (*this->allBlobs[i]).hash_code();

			//First, checks if allBlobs{i] can actually merge (is not a GoodOldBlob).
			if (typeID != typeid (GoodOldBlob).hash_code()) {

				//xPos1 and yPos1 are the coordenates of allBlobs[i]-
				xPos1 = this->allBlobs[i]->getBlobPosition()->x;
				yPos1 = this->allBlobs[i]->getBlobPosition()->y;

				//Each iteration has a thisMerge parameter, which serves to do the final speed and direction average.
				thisMerge = 1;

				//For every blob in the array, the loop iterates through the rest of the array (going forward).
				for (int j = i + 1; j < this->blobAmount; j++) {

					//Coordenates of another (j>i) blob.
					xPos2 = this->allBlobs[j]->getBlobPosition()->x;
					yPos2 = this->allBlobs[j]->getBlobPosition()->y;

					xDist = xPos2 - xPos1;
					yDist = yPos2 - yPos1;

					//If coordenates and type match, they have to merge.
					if (abs(xDist) < this->allBlobs[i]->getBitmapWidth() && abs(yDist) < this->allBlobs[i]->getBitmapWidth()
						&& typeID == typeid(*this->allBlobs[j]).hash_code()) {

						//Adds to allBlobs[i] the speed and direction of allBlobs[j].
						this->allBlobs[i]->willMerge(this->allBlobs[j]);

						//It treats the blobMerge as the death of allBlobs[j] (read specifications above).
						this->blobDeath(j);
						j--;

						//Increments the thisMerge parameter associated to allBlobs[i].
						thisMerge++;
					}
				}

				if (thisMerge > 1) {
					/*Once allBlobs[i] has the added speeds and directions of all the blobs with which it merged,
					hasMerged divides everything by thisMerge to obtain the mean. */
					this->allBlobs[i]->hasMerged(thisMerge);

					//Finally, allBlobs[i] evolves (distinguish between cases).
					if (typeID == typeid(BabyBlob).hash_code()) {
						GrownBlob tempBlob(this->allBlobs[i], randomJiggle);

						delete allBlobs[i];
						allBlobs[i] = new (nothrow) GrownBlob(tempBlob);
					}

					else {
						GoodOldBlob tempBlob(this->allBlobs[i], randomJiggle);

						delete allBlobs[i];
						allBlobs[i] = new (nothrow) GoodOldBlob(tempBlob);
					}
				}
			}
		}
	}
}

//Attempts to create a new BabyBlob and appends it to the allBlobs array and increment blobAmount.
bool Simulation::blobBirth(void) {
	bool result = true;
	if (!(this->allBlobs[this->blobAmount] = new (nothrow) BabyBlob(this->width, this->height, this->generalMaxSpeed,
		this->generalRelativeSpeed, defaultSmellRadius, defaultDeathProb)))
		result = false;
	
	if (result)
		this->blobAmount++;

	return result;
}

//Deletes the dead blob and moves all subsecuent blobs to adjust the array.
void Simulation::blobDeath(int index) {
	delete this->allBlobs[index];

	for (int i = index; i < this->blobAmount-1; i++) {
		this->allBlobs[i] = this->allBlobs[i + 1];
	}

	this->blobAmount--;
}

//Draws background, blobs and food.
void Simulation::drawItAll(void) {
	
	//Draws background.
	this->graphicControl->drawBitmap(this->graphicControl->getBackgrBit(), 0, 0);

	//Draws blobs.
	for (int i = 0; i < this->blobAmount; i++) {
		this->drawAccordingBitmap(this->allBlobs[i]);
	}

	//Draws food.
	for (int i = 0; i < this->foodAmount; i++) {
		this->graphicControl->drawBitmap(this->graphicControl->getFoodBit(), foodVector[i]->getXPosit(), 
			foodVector[i]->getYPosit());
	}
}