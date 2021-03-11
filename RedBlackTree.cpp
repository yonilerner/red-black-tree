#include "RedBlackTree.h"
#include <iostream>

#define SPACE 15

using namespace std;

RBTree::RBTree()
//constructor
{
	root = NULL;
}

Node* RBTree::findParent(Node* root, Node* previous, int k)
{
	if (this->root->value == k || this->root == nullptr || root == nullptr)
		return nullptr;
		
	if ( root->value == k)
	{
		return previous;
	}
	if (k < root->value)
	{
		return findParent(root->left, root, k);
	}
	else
	{
		return findParent(root->right, root, k);
	}
}

bool RBTree::isEmpty()
//checks if the tree is empty
{
	if (root == NULL)
		return true;
	else
		return false;
}

Node* RBTree::recolor(Node* node)
{
	node->isRed = true;
	node->left->isRed = false;
	node->right->isRed = false;
	return node;
}

Node* RBTree::rightRotate(Node* y)
//rotates the AVL tree to the right
{
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	x->right->isRed = true;
	x->isRed = false;

	printTree();
	return x;
}

Node* RBTree::leftRotate(Node* x)
//performs a left rotation
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	y->left->isRed = true;
	y->isRed = false;
	return y;

	
}

void RBTree::insert(int value)
//seperate so that the other insert function can be private
{
	root = insert(root, value);
	printTree();
}
Node* RBTree::insert(Node* current, int key)
//inserts a node into the tree and self-balances
{
	Node* newNode = new Node();
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->value = key;
	newNode->isRed = true;

	
	if (current == NULL)
	{
		
		current = newNode;
		if (root == NULL)
			current->isRed = false;
		return current;
	}

	if (newNode->value < current->value)
	{
		current->left = insert(current->left, newNode->value);
	}
	else if (newNode->value > current->value)
	{
		current->right = insert(current->right, newNode->value);
	}
	else
	{
		cout << "Value already in tree!" << endl;
		return current;
	}

	/*
	int bf = balanceFactor(current);

	//left  heavy --> will need right rotation
	if (bf > 1 && newNode->value < current->left->value)
		return rightRotate(current);

	//right heavy --> will need left rotation
	if (bf < -1 && newNode->value > current->right->value)
		return leftRotate(current);

	//left right --> will neeed left right rotation
	if (bf > 1 && newNode->value > current->left->value)
	{
		current->left = leftRotate(current->left);
		return rightRotate(current);
	}

	//right left --> will need right left rotation
	if (bf < -1 && newNode->value < current->right->value)
	{
		current->right = rightRotate(current->right);
		return leftRotate(current);
	}*/

	if (root != nullptr)
		insertionFixer(newNode);
	
	root->isRed = false;

	return current;
}
/*
int RBTree::height(Node* node)
//returns the height of the tree (or from the given node)
{
	if (node == NULL)
		return -1;
	else
	{
		//computer the height of each subtree
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);

		//then use the larger of the two heights 
		//(since height measured byt he longest path)
		if (leftHeight > rightHeight)
			return (leftHeight + 1);
		else
			return (rightHeight + 1);
	}
}

int RBTree::balanceFactor(Node* node)
//returns the balance factor
{
	if (node == NULL)
		return -1;
	return
		height(node->left) - height(node->right);
}
*/
void RBTree::insertionFixer(Node*& child)
{
	Node* parent = findParent(this->root, this->root, child->value);
	Node* uncle = nullptr;

	//cannot have 2 nodes in a row that are red--> if parent and child are red, need to do something (one of the following if statements)
	// cylce through the following loop until there are no more reds after reds. 
	while (child != root && parent != nullptr && parent->isRed && child->isRed)
	{
		Node* grandparent = findParent(this->root, this->root, parent->value);
		cout << endl << "Insertion Fixer...";
		cout << endl << "Child: " << child->value << " Parent: " << parent->value << " Granny: " << grandparent->value;
		uncle = ((parent == grandparent->left) ? grandparent->right : grandparent->left);

		if (uncle && uncle->isRed)
		{
			grandparent = recolor(grandparent);
			child = grandparent;
		}
		else 
		{
			if (parent->value < grandparent->value && child->value < parent->value)
			{
				cout << endl << "Right rotation...";
				parent = rightRotate(parent);
				child = parent->right;
				
			}
			else if (parent->value > grandparent->value && child->value > parent->value)
			{
				cout << endl << "Left rotation...";
				parent = leftRotate(parent);
				child = parent->left;
				
			}
			else if (parent->value > grandparent->value && child->value < parent->value)
			{
				cout << endl << "Right-Left rotation...";
				parent->right = rightRotate(parent->right);
				parent = leftRotate(parent);	
			}
			else if (parent->value < grandparent->value && child->value > parent->value)
			{
				cout << endl << "Left-Right rotation...";
				parent->left = leftRotate(parent->left);
				parent = rightRotate(parent);
			}
		}
	}
	
	root->isRed = false;
}


void RBTree::printTree()
{
	cout << endl << endl;
	printTree(root, 13, false);
}


void RBTree::printTree(Node* node, int space, bool leftChild)
{
	if (node == nullptr)
		return;
	space += SPACE; //increases the distance between the levels
	printTree(node->right, space, false);

	for (int i = SPACE; i < space; i++)
	{

		if (i == 0)
		{
			cout << '<';
		}
		cout << ' ';
	}
	if (node == root)
	{
		cout << "Root: ";
	}
	if (node != root)
	{
		if (!leftChild)
		{
			cout << "/--";
		}
		else
		{
			cout << "\\--";
		}
	}

	
	if (node->isRed)
		cout << node->value << " (red) " << '<' << endl;
	else
		cout << node->value << " (black) " << '<' << endl;


	printTree(node->left, space, true);
}


RBTree::~RBTree()
{
	deleteTree(root);
}
void RBTree::deleteTree(Node* Ptr)
{
	if (Ptr != NULL)
	{
		if (Ptr->left != NULL)
		{
			deleteTree(Ptr->left);
		}
		if (Ptr->right != NULL)
		{
			deleteTree(Ptr->right);
		}
		delete Ptr;
	}
}

