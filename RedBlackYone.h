#pragma once
#ifndef REDBLACKYONE_H
#define REDBLACKYONE_H

struct Node
{
    int value;
    Node* left;
    Node* right;
    bool isRed;

};

class RBYone {
//private:
public:
    bool isEmpty();
    //Node* rightRotate(Node* z);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    void printTree(Node* node, int space, bool leftChild);
    Node* insert(Node* current, int key, int depth);
    void deleteTree(Node* Ptr);

    Node* root;
    Node* findParent(Node* root, Node* previous, int k);
    Node* insertionFixer(Node*& child);
    Node* recolor(Node* node);




public:
    RBYone();
    void insert(int);
    void printTree();
    ~RBYone();




    //int height(Node* node);
    //int balanceFactor(Node* node);


};

#endif


