#include "structs.h"

#ifndef occurenceType_h
#define occurenceType_h

class occurence {
public:
	occurence();
	void ResetP();
	oType Read();
	void Insert(oType);
	int Length();
	void Iterate();

private:
	oType a[100];				//can hold a max of 100 occurences of a word
	int p;
	int length;
};

#endif
