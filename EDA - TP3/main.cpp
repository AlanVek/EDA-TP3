#include <iostream>
#include "Simulation.h"

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

        //Attempts to initialize simulation.
        if (!mySim->initializeAll()) {
            cout << "Failed to initialize simulation\n";
            result = false;
        }
    }

    mySim->getGUI()->GUI_firstLoop();
    if (!mySim->getFirstData())
        endOfInput = true;
    mySim->getTimeControl()->startTimer();

    while (mySim->getBlobAmount() && !endOfInput) {
        if (!mySim->getGUI()->GUI_Game_Loop())
            endOfInput = true;
        
        mySim->getData();
        
        if (mySim->getEventControl()->getNextEventType() == ALLEGRO_EVENT_TIMER && !(mySim->getGUI()->pause))
            mySim->moveCycle();
    }

    delete mySim;
    return 0;
}
