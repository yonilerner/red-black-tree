#include "RedBlackYone.h"
#include <iostream>

#define SPACE 5

using namespace std;

RBYone::RBYone()
//constructor
{
    root = NULL;
}

Node* RBYone::findParent(Node* root, Node* previous, int k)
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

bool RBYone::isEmpty()
//checks if the tree is empty
{
    if (root == NULL)
        return true;
    else
        return false;
}

Node* RBYone::recolor(Node* node)
{
    node->isRed = true;
    node->left->isRed = false;
    node->right->isRed = false;
    return node;
}

Node* RBYone::rightRotate(Node* grandparent)
//rotates the AVL tree to the right
{
    Node* parent = grandparent->left;
    Node* brother = parent->right;

    cout << endl;
    cout << "grandparent " << grandparent->value;
    cout << " parent " << parent->value;
    cout << " child " << parent->left->value << endl;

    if (grandparent->left != nullptr)
        cout << "grandparent left " << grandparent->left->value;
    if (grandparent->right != nullptr)
        cout << "grandparent right " << grandparent->right->value;
    if (parent->left != nullptr)
        cout << "parent left " << parent->left->value;
    if (parent->right != nullptr)
        cout << "parent right " << parent->right->value;
    if (brother != nullptr)
        cout << "BROTHER " << brother->value;
    else
        cout << "BROTHER NONE";
    cout << endl;

    printTree();

    parent->right = grandparent;
    grandparent->left = brother;

    parent->right->isRed = true;
    parent->isRed = false;

    cout << endl;
    cout << "grandparent " << grandparent->value;
    cout << " parent " << parent->value;
    cout << " child " << parent->left->value << endl;

    if (grandparent->left != nullptr)
    cout << "grandparent left " << grandparent->left->value;
    if (grandparent->right != nullptr)
        cout << "grandparent right " << grandparent->right->value;
    if (parent->left != nullptr)
    cout << "parent left " << parent->left->value;
    if (parent->right != nullptr)
        cout << "parent right " << parent->right->value;
    cout << endl;

    cout << "grandparent -> ??: " << grandparent->value << endl;

    printTree();
    return parent;
}

Node* RBYone::leftRotate(Node* x)
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

void RBYone::insert(int value)
//seperate so that the other insert function can be private
{
    root = insert(root, value, 0);
    cout << "root insert: " << root->value << endl;
    printTree();
}
Node* RBYone::insert(Node* current, int key, int depth)
//inserts a node into the tree and self-balances
{
    Node* newNode = new Node();
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->value = key;
    newNode->isRed = true;

    cout << "current at start ";
    if (current == NULL) {
        cout << "NULL";
    } else {
        cout << current->value;
    }
    cout << endl;


    if (current == NULL)
    {

        current = newNode;
        if (root == NULL)
            current->isRed = false;
        return current;
    }

    if (newNode->value < current->value)
    {
        current->left = insert(current->left, newNode->value, depth + 1);
        cout << "current left after set " << current->left->value;
    }
    else if (newNode->value > current->value)
    {
        current->right = insert(current->right, newNode->value, depth + 1);
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

    if (root != nullptr) {
        cout << endl << "depth " << depth << endl;
        current = insertionFixer(newNode);
        cout << "current after fixer " << current->value << endl;
    }

    root->isRed = false;

    cout << "[" << depth << "]" << "root inner insert: " << root->value << endl;

    return current;
}
/*
int RBYone::height(Node* node)
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

int RBYone::balanceFactor(Node* node)
//returns the balance factor
{
	if (node == NULL)
		return -1;
	return
		height(node->left) - height(node->right);
}
*/
Node* RBYone::insertionFixer(Node*& child)
{
    cout << "Fixing " << child->value << endl;
    cout << "root insertion fixer: " << root->value << endl;
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
            cout << endl << "recoloring..." << endl;
            grandparent = recolor(grandparent);
            child = grandparent;
        }
        else
        {
            if (parent->value < grandparent->value && child->value < parent->value)
            {
                cout << endl << "Right rotation...";
                parent = rightRotate(grandparent);
//                child = parent->right;
//                child->left = NULL;
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

    cout << "root after fixer: " << root->value << endl;

    root->isRed = false;

    return parent;
}


void RBYone::printTree()
{
    cout << endl << endl;
    printTree(root, 13, false);
}


void RBYone::printTree(Node* node, int space, bool leftChild)
{
    if (node == nullptr)
        return;
    space += SPACE; //increases the distance between the levels

    cout << "new level " << node->value << endl;
    if (node->right != nullptr) {
        cout << "has right: " << node->right->value << endl;
    }
    if (node->left != nullptr) {
        cout << "has left: " << node->left->value << endl;
    }

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


RBYone::~RBYone()
{
    deleteTree(root);
}
void RBYone::deleteTree(Node* Ptr)
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

