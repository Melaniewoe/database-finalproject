/* Filename:  avlnode.h
 
 Programmer:  Br. David Carlson
 
 Reference:  Data Structures with C++, by Ford and Topp
 
 Date:  October 12, 1997
 
 Modified:  June 9, 1999 to create AVLNodePtr type.
 
 This is the header file to accompany avlnode.cpp.  It sets up the
 class AVLNodeClass as shown below.
 */

//#ifndef AVLNODE_H
//#define AVLNODE_H

/*
#include "bstnode.h"


class AVLNodeClass: public BSTNodeClass
{
private:
    int Balance;
public:
    // constructor:
    AVLNodeClass(const ItemType & Item, AVLNodeClass * LeftPtr = NULL,
                 AVLNodeClass * RightPtr = NULL, int BalanceValue = 0);
    friend class AVLClass;
    friend class AVLTableClass;   // may not get to implementing this
};

typedef AVLNodeClass * AVLNodePtr;
*/

#ifndef AVLNode_H
#define AVLNode_H

#include <iostream>
#include "itemtype.h"

class AVLNode {
public:
    AVLNode();
    AVLNode(ItemType data, AVLNode* parent);
    AVLNode(ItemType data, AVLNode* left, AVLNode* right);
    AVLNode(ItemType data, AVLNode* left, AVLNode* right, int balance);
    ~AVLNode();
    
    void setData(ItemType daata);
    void setBalance(int bal);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    
    ItemType getData() const;
    int getBalance() const;
    const AVLNode* const getLeft() const;
    const AVLNode* const getRight() const;
    
    bool operator < (const AVLNode& AVLNode) const;
    friend std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode);
    
    /* Tree structure pointers */
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    
    /* AVL Balance Factor */
    int balance;
    
    /* Node Internal Data */
    ItemType data;
};

#endif

