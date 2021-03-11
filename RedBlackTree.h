#pragma once
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

struct Node
{
	int value;
	Node* left;
	Node* right;
	bool isRed;

};

class RBTree {
//private:
public:
	bool isEmpty();
	//Node* rightRotate(Node* z);
	Node* rightRotate(Node* y);
	Node* leftRotate(Node* x);
	void printTree(Node* node, int space, bool leftChild);
	Node* insert(Node* current, int key);
	void deleteTree(Node* Ptr);

	Node* root;
	Node* findParent(Node* root, Node* previous, int k);
	void insertionFixer(Node*& child);
	Node* recolor(Node* node);




public:
	RBTree();
	void insert(int);
	void printTree();
	~RBTree();

	


	//int height(Node* node);
	//int balanceFactor(Node* node);


};

#endif


