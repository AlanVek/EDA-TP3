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
        cout << "Failed to create simulation\.";
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
    //Gets first data input.
    mySim->getGUI()->GUI_firstLoop();
    if (!mySim->getFirstData())
        endOfInput = true;

    //Starts timer.
    mySim->getTimeControl()->startTimer();

    while (mySim->getBlobAmount() && !endOfInput) {

        //Ends if user presses ESC.
        if (!mySim->getGUI()->GUI_Game_Loop())
            endOfInput = true;

        //Gets data from GUI.
        mySim->getData();

        //Updates display every time there's a timer event.
        if (mySim->getEventControl()->getNextEventType() == ALLEGRO_EVENT_TIMER && !(mySim->getGUI()->pause)) {
            if (!mySim->moveCycle()) {
                cout << "Runtime error. Couldn't create new blob.\n";
                endOfInput = true;
            }
        }
    }

    delete mySim;
    return 0;
}
