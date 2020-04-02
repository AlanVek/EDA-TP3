#pragma once
using namespace std;

//Deletes pointers.
template <class T> void deleteArray(T* Vector, int index) {
	for (int i = 0; i < index; i++) {
		if (Vector[i])
			delete Vector[i];
	}
}



