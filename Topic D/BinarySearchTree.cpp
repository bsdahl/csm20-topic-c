//
//  BinarySearchTree.cpp
//  Topic D
//
//  Created by user on 10/15/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//

#include <stdio.h>
#include "BinarySearchTree.h"

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
} // Default Constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) : BinaryNodeTree<ItemType>(rootItem)
{
} // Constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
    *this = treePtr;
} // Copy Constructor




template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>*  subTreePtr,BinaryNode<ItemType>* newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;
    else
    {
        if (subTreePtr->getItem() > newNodePtr->getItem()) {
            subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(),newNodePtr));
        }
        else {
            subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(),newNodePtr));
        }
        return subTreePtr;
    }
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,const ItemType target,bool& success)
{
    if (subTreePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    if (subTreePtr->getItem() == target)
    {
        subTreePtr = BinaryNodeTree<ItemType>::removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        if (subTreePtr->getItem() > target)
            subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
        else
            subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
        
        return subTreePtr;
    }
}




template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const
{
    if (subTreePtr == nullptr)
        return nullptr;
    else if (subTreePtr->getItem() == target)
        return subTreePtr;
    else if (subTreePtr->getItem() > target)
        return findNode(subTreePtr->getLeftChildPtr(), target);
    else
        return findNode(subTreePtr->getRightChildPtr(), target);
}





// need insertinorder
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    this->rootPtr = insertInorder(this->rootPtr, newNodePtr);
    
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
    bool isSuccessful = false;
    this->rootPtr = removeValue(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}


template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
    BinaryNode<ItemType>* nodeWithEntry = findNode(this->rootPtr, anEntry);
    if (nodeWithEntry == nullptr)
        throw NotFoundException("Entry does not exist in tree.");
        else
            return nodeWithEntry->getItem();
            }

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    return (findNode(this->rootPtr, anEntry) == nullptr ? false : true);
}


template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
    if (!this->isEmpty())
        this->clear();
    this->rootPtr = this->copyTree(rightHandSide.rootPtr);
    
    return *this;
}