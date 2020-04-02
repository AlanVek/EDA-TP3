#pragma once
#include "Simulation.h"
using namespace std;

extern int width, height;
extern int generalMaxSpeed, mode, smellRadius;
extern float generalRelativeSpeed;

template <typename T> bool initializeThis(T** thisT, unsigned int amount) {
	bool result = true;

	for (int i = 0; i < amount; i++) {
		if (!(thisT[i] = new (nothrow) T(width, height)))
			result = false;

		else if (!(thisT[i]->createBitmap(width,height)))
			result = false;
	}

	return result;
}

template <typename T> void deleteThis(T** thisT, unsigned int index) {
	for (int j = 0; j < index; j++) {
		if (thisT[j]) {
			thisT[j]->destroyBitmap();
			delete thisT[j];
		}
	}
}
