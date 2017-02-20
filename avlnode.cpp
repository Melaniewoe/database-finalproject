/* Filename:  avlnode.cpp
 
 Programmer:  Br. David Carlson
 
 Reference:  Data Structures with C++, by Ford and Topp
 
 Date:  October 12, 1997
 
 This file defines the constructor for the class AVLNodeClass, which
 is set up in avlnode.h.
 */

#include "avlnode.h"


/* Given:  Item          Data item to place in Info field.
 LeftPtr       Pointer to place in Left field.
 RightPtr      Pointer to place in Right field.
 BalanceValue  Value to place in Balance field.
 Task:   This is the constructor.  It's job is to create a new
 object containing the above 4 values.
 Return: Nothing directly, but the implicit object is created.
 */

/*
AVLNodeClass::AVLNodeClass(const ItemType & Item,
                           AVLNodeClass * LeftPtr, AVLNodeClass * RightPtr, int BalanceValue):
// call BSTNodeClass constructor, initialize field:
BSTNodeClass(Item, LeftPtr, RightPtr), Balance(BalanceValue)
{
#ifdef DEBUG
    cout << "DEBUG: AVLNodeClass constructor called" << endl;
#endif
}

*/

#include "AVLNode.h"

AVLNode::AVLNode() : data() {
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

AVLNode::AVLNode(ItemType data, AVLNode* parent) {
    this->data = data;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
}

AVLNode::AVLNode(ItemType data, AVLNode* left, AVLNode* right) {
    this->data = data;
    this->balance = 0;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::AVLNode(ItemType data, AVLNode* left, AVLNode* right, int balance) {
    this->data = data;
    this->balance = balance;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::~AVLNode() {
    if (this->left != nullptr)
        delete this->left;
    if (this->right != nullptr)
        delete this->right;
}

void AVLNode::setData(ItemType data) {
    this->data = data;
}

void AVLNode::setBalance(int bal) {
    this->balance = bal;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

ItemType AVLNode::getData() const {
    return this->data;
}

int AVLNode::getBalance() const {
    return this->balance;
}

const AVLNode* const AVLNode::getLeft() const {
    return this->left;
}

const AVLNode* const AVLNode::getRight() const {
    return this->right;
}

bool AVLNode::operator < (const AVLNode& AVLNode) const {
    return (this->data < AVLNode.data);
    //if ( this->data < AVLNode.data ) return true;
    //return false;
}

std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode) {
    out << AVLNode.data;
    return out;
}