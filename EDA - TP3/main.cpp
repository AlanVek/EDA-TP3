#include <iostream>
#include "Simulation.h"

//#define fontName "BOSQUE.ttf"
#define babyBitmap "food.png"

using namespace std;

int main()
{
    bool result = true;

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

        if (result) {
            al_flip_display();

            al_rest(3);
        }
    }

    mySim->destroyAll();
    delete mySim;
    return 0;
}
