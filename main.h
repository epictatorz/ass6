#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>			//used for converting words to lowercase
#include <iostream>
#include "occurenceType.h"
#include "indexType.h"
#include "occurenceType.h"
using namespace std;

#ifndef main_h
#define main_h

Tree index;

void createIndex();
string getFileName(int);
void readFile(string, int);
void menu();

void searchMenu();
void searchWord(string);
void searchPhrase(string);

int main() {
	createIndex();
	menu();
	return 0;
}
#endif
