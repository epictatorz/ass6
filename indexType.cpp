#include "indexType.h"
#include <iostream>
using namespace std;

int Max(int a, int b) {
	if (a < b) { return b; }
	return a;
}

Tree::Tree() {
	p = NULL;
	root = NULL;
}

bool Tree::IsPSet() {
	if (p == NULL) {
		return false;
	}
	return true;
}

iType Tree::Read() {
	return p->val;
}

void Tree::Write(iType x) {
	p->val = x;
}

bool Tree::IsEmpty() {
	if (root == NULL) {
		return true;
	}
	return false;
}

void Tree::FindHelper(iType x) {
	Find(x, root);
}

void Tree::Find(iType x, AVLNode*& q) {
	if (q == NULL || x.word == q->val.word) {
		p = q;
	}
	else if (x.word < q->val.word) {
		Find(x, q->left);
	}
	else {
		Find(x, q->right);
	}
	return;
}

void Tree::FindMin(AVLNode*& q) {
	if (q == NULL || q->left == NULL) {
		p = q;
	}
	else FindMin(q->left);
	return;
}

void Tree::FindMax(AVLNode*& q) {
	if (q == NULL || q->right == NULL) {
		p = q;
	}
	else {
		FindMax(q->right);
	}
	return;
}

void Tree::InsertHelper(iType x) {
	Insert(x, root);
}

void Tree::Insert(iType x, AVLNode*& q) {
	if (q == NULL) {
		q = new AVLNode;
		q->val = x;
		q->left = NULL;
		q->right = NULL;
		p = q;
	}
	else if (x.word < q->val.word) {
		Insert(x, q->left);
		if (p != NULL) {
			if ((Height(q->left) - Height(q->right)) == 2) {
				if (x.word < q->left->val.word) {
					LL(q);
				}
				else {
					LR(q);
				}
			}
		}
	}
	else if (x.word > q->val.word) {
		Insert(x, q->right);
		if (p != NULL) {
			if (Height(q->right) - Height(q->left) == 2) {
				if (x.word > q->right->val.word) {
					RR(q);
				}
				else {
					RL(q);
				}
			}
		}
	}
	//if word is equal adds occurence to current record
	else if (x.word == q->val.word) {
		q->val.occurences.Insert(x.occurences.Read());
		p = q;
	}
	return;
}

void Tree::LL(AVLNode*& q) {
	AVLNode* r = q->left;
	q->left = r->right;
	q->height = Max(Height(q->left), Height(q->right)) + 1;
	r->height = Max(Height(r->left), Height(r->right)) + 1;
	q = r;
	return;
}

void Tree::RR(AVLNode*& q) {
	AVLNode* r = q->right;
	q->right = r->left;
	r->left = q;
	q->height = Max(Height(q->left), Height(q->right)) + 1;
	r->height = Max(Height(r->left), Height(r->right)) + 1;
	q = r;
	return;
}

void Tree::LR(AVLNode*& q) {
	RR(q->left);
	LL(q);
	return;
}

void Tree::RL(AVLNode*& q) {
	LL(q->right);
	RR(q);
}

int Tree::Height(AVLNode*& q) {
	if (q == NULL) {
		return -1;
	}
	return q->height;
}

void Tree::printOccurencesHelper() {
	printOccurences(root, 1);
}

void Tree::printOccurences(AVLNode*& q, int level) {
	cout << q->val.word << endl;
	
}