#include "occurenceType.h"

occurence::occurence() {
	p = -1;
	length = 0;
}


oType occurence::Read() {
	//reads the current value
	return a[p];
}

void occurence::Insert(oType x) {
	//adds an occurence to the list
	p = length;
	a[p] = x;
	length++;
}

void occurence::ResetP() {
	//sets "pointer" to nothing (before the start of list)
	p = -1;
}

int occurence::Length() {
	//returns length
	return length;
}

void occurence::Iterate() {
	//moves "pointer" to next in list
	p++;
}
