#include "occurenceType.h"
#include "structs.h"
#include <string>

using namespace std;

#ifndef indexType_h
#define indexType_h

int Max(int, int);

struct iType {

	string word;
	occurence occurences;
};

class AVLNode {
public:
	iType val;
	AVLNode *left;
	AVLNode *right;
	int height;
};

class Tree {
public:

	Tree();
	bool IsPSet();
	iType Read();
	void Write(iType);
	bool IsEmpty();
	void FindHelper(iType);
	void Find(iType, AVLNode*&);
	void FindMin(AVLNode*&);
	void FindMax(AVLNode*&);
	void InsertHelper(iType);
	void Insert(iType, AVLNode*&);
	int Height(AVLNode*&);

	void printOccurences();
	void printOccurencesHelper(AVLNode*&, int);

	void printWithoutOccurences();
	void printWithoutOccurencesHelper(AVLNode*&, int);

private:

	AVLNode* p;
	AVLNode* root;

	void LL(AVLNode*&);
	void RR(AVLNode*&);
	void LR(AVLNode*&);
	void RL(AVLNode*&);
};
#endif
