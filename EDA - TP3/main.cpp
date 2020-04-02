#include <iostream>
#include "Simulation.h"

//#define fontName "BOSQUE.ttf"
#define babyBitmap "food.png"

using namespace std;

int main()
{
    bool result = true;
    bool endOfInput = false;

    Simulation* mySim = new (nothrow) Simulation;

    srand(time(NULL));
    //Checks for memory allocation error.
    if (!mySim) {
        cout << "Failed to crate simulation\.";
        result = false;
    }

    //If mySim was successfully created...
    if (result) {
        //mySim->getGraphicControl()->setFontName(fontName);

        //Attempts to initialize simulation.
        if (!mySim->initializeAll()) {
            cout << "Failed to initialize simulation\n";
            result = false;
        }
    }
    mySim->getTimeControl()->startTimer();

    int suma = 0;
    while (result && !endOfInput) {
        if (mySim->getEventControl()->getNextEventType() == ALLEGRO_EVENT_TIMER) {
            mySim->moveCycle();
            suma++;
        }
        if (suma == 500) {
            break;
        }
    }

    mySim->destroyAll();
    delete mySim;
    return 0;
}
