#pragma once
#include "Simulation.h"

void GUILoop(Simulation* mySim);

//void GUISetTHIS(Simulation* mySim);

void GUI_loop_setup(bool* mode, int* blobCount, float* relSpeed, float* maxSpeed, int* smellRadius,
	float* randomJL, float* babyDeathProb, float* grownDeathProb, float* goodOldDeathProb, int* foodCount, bool* pause, Simulation* mySim);

bool GUI_start_setup(bool* mode, int* blobCount, Simulation* mySim);

bool checkEndOfProgram(Simulation* mySim);
