#include <iostream>
#include "Simulation.h"

using namespace std;

int main()
{
    Simulation* mySim = new (nothrow) Simulation;









    mySim->destroyAll();
    delete mySim;
    return 0;
}
