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
	unsigned int generalMaxSpeed_, float generalRelativeSpeed_, int mode_, int foodCount_) : 

	width(width_), height(height_), FPS(FPS_), blobAmount(blobAmount_), generalMaxSpeed(generalMaxSpeed_),
	generalRelativeSpeed(generalRelativeSpeed_), mode(mode_), foodCount(foodCount_){

	graphicControl = nullptr;
	timeControl = nullptr;
	eventControl = nullptr;
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
	else if (!setSimulation(true)) {
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

	graphicControl = new (nothrow) GraphicClass(width, height);
	eventControl = new (nothrow) EventClass();
	timeControl = new (nothrow) TimeClass();
	if (!graphicControl) {
		cout << "Failed to create graphic pointer\n";
		result = false;
	}
	else if (!eventControl) {
		cout << "Failed to create event pointer\n";
		result = false;
	}
	else if (!timeControl) {
		cout << "Failed to create time pointer\n";
		result = false;
	}
	//Attempts to create display (if requested).
	else if (displayCreation && !graphicControl->createDisplay()) {
		cout << "Failed to create display\n";
		result = false;
	}
	//Attempts to create event queue.
	else if (!eventControl->createEventQueue()) {
		cout << "Failed to create event queue\n";
		al_register_event_source(eventControl->getQueue(), al_get_display_event_source(graphicControl->getDisplay()));
		result = false;
	}

	//Attempts to create timer.
	else if (!timeControl->createTimer(FPS)) {
		cout << "Failed to create timer\n";
		result = false;
	}


	//Attempts to create bitmaps.
	else if (!graphicControl->initializeBitmaps(width, height)) {
		cout << "Failed to load background bitmaps\n";
		result = false;
	}

	if (result) {
		//Attempts to Initialize allBlobs to default values (for now) and create bitmaps.
		if (!(initializeBlob())) {
			cout << "Failed to create blobs\n";
			result = false;
		}
		//Attempts to Initialize allFoods to default values (for now) and create bitmaps.
		else if (!initializeFood()) {
			cout << "Failed to create food\n";
			result = false;
		}
	}

	//Sets event source for timer and shows drawings.
	if (result) {
		al_register_event_source(eventControl->getQueue(), al_get_timer_event_source(timeControl->getTimer()));
		al_register_event_source(eventControl->getQueue(), al_get_keyboard_event_source());
		al_install_mouse();		
		al_register_event_source(eventControl->getQueue(), al_get_mouse_event_source());
	}
	return result;
}

//Class getters.
GraphicClass* Simulation::getGraphicControl(void) { return graphicControl; }
TimeClass* Simulation::getTimeControl(void) { return timeControl; }
EventClass* Simulation::getEventControl(void) { return eventControl; }
unsigned int Simulation::getBlobAmount(void) { return blobAmount; }
Blob** Simulation::getAllBlobs(void) { return allBlobs; }

//Creates food, loads bitmaps and draws them.
bool Simulation::initializeFood (){

	bool result = true;
	for (int i = 0; i < foodCount; i++) {
		if (!(allFoods[i] = new (nothrow) Food(width, height)))
			result = false;
		else
			graphicControl->drawBitmap(graphicControl->getFoodBit(),
				allFoods[i]->getXPosit(),allFoods[i]->getYPosit());
	}
	return result;
}

//Creates blobs, loads bitmaps and draws them.
bool Simulation::initializeBlob() {
	float xPos, yPos;
	bool result = true;

	float gMaxSpeed;
	float gRelSpeed;


	for (int i = 0; i < blobAmount; i++) {
		
		if (mode == 1) {
			gMaxSpeed = defaultMaxSpeed;
			gRelSpeed = 0.001 * (rand() % 1000);
		}
		else {
			gMaxSpeed = rand() % defaultMaxSpeed;
			gRelSpeed = defaultRelativeSpeed;
		}
		if (!(allBlobs[i] = new (nothrow) BabyBlob(width, height, gMaxSpeed,
			gRelSpeed, defaultSmellRadius, defaultDeathProb)))
			result = false;

		else {
			xPos = allBlobs[i]->getBlobPosition()->x;
			yPos = allBlobs[i]->getBlobPosition()->y;
			drawAccordingBitmap(allBlobs[i]);
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
	for (int i = 0; i < blobAmount; i++) {
		if (allBlobs[i]->checkBlobDeath()) {
			blobDeath(i);
			i--;
		}
	}

	//Then, every blob smells for food (and adjusts angles).
	for (int i = 0; i < blobAmount; i++) 
		allBlobs[i]->blobSmell(allFoods, foodCount);

	//Separately, so as to first finish calculations, the blobs move.
	for (int i = 0; i < blobAmount; i++) {
		allBlobs[i]->blobMove(width, height);

		//Checks for eaten food.
		hasBeenEaten = allBlobs[i]->blobFeeding(allFoods, foodCount,birthFlag);
		if ( hasBeenEaten != -1)
			allFoods[hasBeenEaten]->NewPosition(width, height);

		//Checks for potential blobBirth.
		if (*birthFlag) {
			if (!blobBirth())
				cout << "Runtime Error. Failed to create new BabyBlob.\n";
		}
	}

	//Checks for merges and does the necessary changes.
	Merges();

	drawItAll();
}

void Simulation::drawAccordingBitmap(Blob* thisBlob) {
	float xPos = thisBlob->getBlobPosition()->x;
	float yPos = thisBlob->getBlobPosition()->y;

	float typeID = typeid (*thisBlob).hash_code();

	//If it's a BabyBlob, it draws the babyBit. 
	if (typeID == typeid (BabyBlob).hash_code()) {
		graphicControl->drawBitmap(graphicControl->getBabyBit(), xPos, yPos);
	}

	//If it's a GrownBlob, it draws the grownBit.
	else if (typeID == typeid (GrownBlob).hash_code()) {
		graphicControl->drawBitmap(graphicControl->getGrownBit(),xPos, yPos);
	}

	//If it's a GoodOldBlob, it draws the goodBit.
	else if (typeID == typeid (GoodOldBlob).hash_code()) {
		graphicControl->drawBitmap(graphicControl->getGoodBit(),xPos, yPos);
	}
}


//Checks for overlapped same-age-group blobs and blobMerges them.
void Simulation::Merges() {

	float xPos1, xPos2;
	float yPos1, yPos2;

	float typeID, randomJ;
	float xDist, yDist;
	int thisMerge;
	if (blobAmount) {
		for (int i = 0; i < blobAmount - 1; i++) {

			typeID = typeid (*allBlobs[i]).hash_code();

			//First, checks if allBlobs{i] can actually merge (is not a GoodOldBlob).
			if (typeID != typeid (GoodOldBlob).hash_code()) {

				//xPos1 and yPos1 are the coordenates of allBlobs[i]-
				xPos1 = allBlobs[i]->getBlobPosition()->x;
				yPos1 = allBlobs[i]->getBlobPosition()->y;

				//Each iteration has a thisMerge parameter, which serves to do the final speed and direction average.
				thisMerge = 1;

				//For every blob in the array, the loop iterates through the rest of the array (going forward).
				for (int j = i + 1; j < blobAmount; j++) {

					//Coordenates of another (j>i) blob.
					xPos2 = allBlobs[j]->getBlobPosition()->x;
					yPos2 = allBlobs[j]->getBlobPosition()->y;

					xDist = xPos2 - xPos1;
					yDist = yPos2 - yPos1;

					//If coordenates and type match, they have to merge.
					if (abs(xDist) < allBlobs[i]->getBitmapWidth() && abs(yDist) < allBlobs[i]->getBitmapWidth()
						&& typeID == typeid(*allBlobs[j]).hash_code()) {

						//Adds to allBlobs[i] the speed and direction of allBlobs[j].
						allBlobs[i]->willMerge(allBlobs[j]);

						//It treats the blobMerge as the death of allBlobs[j] (read specifications above).
						blobDeath(j);
						j--;

						//Increments the thisMerge parameter associated to allBlobs[i].
						thisMerge++;
					}
				}

				if (thisMerge > 1) {
					/*Once allBlobs[i] has the added speeds and directions of all the blobs with which it merged,
					hasMerged divides everything by thisMerge to obtain the mean. */
					allBlobs[i]->hasMerged(thisMerge);

					randomJ = (float) (rand() % (randomJiggleLimit*100))/100.0;

					//Finally, allBlobs[i] evolves (distinguish between cases).
					if (typeID == typeid(BabyBlob).hash_code()) {
						GrownBlob tempBlob(allBlobs[i], randomJ);

						delete allBlobs[i];
						allBlobs[i] = new (nothrow) GrownBlob(tempBlob);
					}

					else {
						GoodOldBlob tempBlob(allBlobs[i], randomJ);

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
	if (!(allBlobs[blobAmount] = new (nothrow) BabyBlob(width, height, generalMaxSpeed,
		generalRelativeSpeed, defaultSmellRadius, defaultDeathProb)))
		result = false;
	
	if (result)
		blobAmount++;

	return result;
}

//Deletes the dead blob and moves all subsecuent blobs to adjust the array.
void Simulation::blobDeath(int index) {
	delete allBlobs[index];

	for (int i = index; i < blobAmount-1; i++) {
		allBlobs[i] = allBlobs[i + 1];
	}

	blobAmount--;
}

//Draws background, blobs and food.
void Simulation::drawItAll(void) {
	
	//Draws background.
	graphicControl->drawBitmap(graphicControl->getBackgrBit(), 0, 0);

	//Draws blobs.
	for (int i = 0; i < blobAmount; i++) {
		drawAccordingBitmap(allBlobs[i]);
	}

	//Draws food.
	for (int i = 0; i < foodCount; i++) {
		graphicControl->drawBitmap(graphicControl->getFoodBit(), allFoods[i]->getXPosit(), 
			allFoods[i]->getYPosit());
	}
}

//Destructor. Frees memory.
Simulation::~Simulation() {
	
	delete graphicControl;
	delete timeControl;
	delete eventControl;

	deleteArray < Blob* >(allBlobs, blobAmount);

	deleteArray < Food* >(allFoods, foodCount);
}
