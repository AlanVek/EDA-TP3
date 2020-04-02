#pragma once
#include "Simulation.h"
using namespace std;

//Deletes pointers.
template <class T> void deleteArray(T* Vector, int index) {
	for (int i = 0; i < index; i++) {
		if (Vector[i])
			delete Vector[i];
	}
}

//Deletes pointer and creates a new one with the "evolved" blob.
template <class T> bool evolve(Blob* thisBlob) {
	T tempBlob(thisBlob);

	delete thisBlob;
	return (thisBlob = new (nothrow) T(tempBlob));
}





