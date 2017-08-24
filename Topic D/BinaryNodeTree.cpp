//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.

/** @file BinaryTree.cpp */

#include "BinaryNodeTree.h" 
#include "BinaryNode.h" 
#include <algorithm>
#include <iostream>

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
   if (subTreePtr == nullptr)
      return 0;
   else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
                                                            BinaryNode<ItemType>* newNodePtr)
{
   if (subTreePtr == nullptr)
      return newNodePtr;
   else
   {
      BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
      BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
      
      if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
      {
         rightPtr = balancedAdd(rightPtr , newNodePtr);
         subTreePtr->setRightChildPtr(rightPtr );
      }
      else
      {
         leftPtr = balancedAdd(leftPtr, newNodePtr);
         subTreePtr->setLeftChildPtr(leftPtr);
      }  // end if
      
      return subTreePtr;
   }  // end if
}  // end balancedAdd

// Remove Value, inorder successor, use this in inheritence
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,const ItemType target, bool& success)
{
    
    if(subTreePtr == nullptr)
        return nullptr;
    
    if (subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        BinaryNode<ItemType>* targetNodePtr = removeValue(
                                                          subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(targetNodePtr);
        if (!success)
        {
            targetNodePtr = removeValue(subTreePtr->getRightChildPtr(),
                                        target, success);
            subTreePtr->setRightChildPtr(targetNodePtr);
        }
        
        return subTreePtr;
    }

}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeNode(BinaryNode<ItemType>* subTreePtr)
{
    BinaryNode<ItemType>* connectorPtr;
    ItemType newVal;
    
    // Case 1, node is a leaf
    if (subTreePtr->isLeaf())
    {
        delete subTreePtr;
        subTreePtr = nullptr;
        return subTreePtr;
    }
    
    // Case 2 Node has 1 child
    else if ((subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() == nullptr) || (subTreePtr->getRightChildPtr() != nullptr && subTreePtr->getLeftChildPtr() == nullptr))
    {
        if (subTreePtr->getLeftChildPtr() != nullptr)
        {
            connectorPtr = subTreePtr->getLeftChildPtr();
        }
        else
        {
            connectorPtr = subTreePtr->getRightChildPtr();
        }
        
        delete subTreePtr;
        subTreePtr = nullptr;
        return connectorPtr;
    }
    
    // Case 2, node has two children
    else
    {
        connectorPtr = removeLeftmostNode(subTreePtr->getRightChildPtr(), newVal);
        subTreePtr->setRightChildPtr(connectorPtr);
        subTreePtr->setItem(newVal);
        return subTreePtr;
    }
}

// from d2l
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& inorderSuccessor)
{
    if (nodePtr->getLeftChildPtr() == nullptr)
    {
        inorderSuccessor = nodePtr->getItem();
        return removeNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor));
        return nodePtr;
    } // end if
} // end removeLeftmostNode

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr,const ItemType& target,bool& success)const
{
    if (treePtr == nullptr)
        return nullptr;
    
    if (treePtr->getItem() == target)
    {
        success = true;
        return treePtr;
    }
    else
    {
        BinaryNode<ItemType>* targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, success);
        if (!success)
        {
            targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success);
        }
        
        return targetNodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
   BinaryNode<ItemType>* newTreePtr = nullptr;
   
   // Copy tree nodes during a preorder traversal
   if (treePtr != nullptr)
   {
      // Copy node
	   newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
	   newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
      newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
   }  // end if
   
   return newTreePtr;
}  // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      delete subTreePtr;
   }  // end if
}  // end destroyTree


// Recursive helper class, gets the total number of nodes
template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
    // case 1, tree is null
    if (subTreePtr == nullptr)
        return 0;
    else // add for the root, then add left and right children nodes
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
   if (treePtr != nullptr)
   {
      inorder(visit, treePtr->getLeftChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      inorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&),
                                        BinaryNode<ItemType>* treePtr) const
{
    if (treePtr != nullptr)
    {
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&),
                                         BinaryNode<ItemType>* treePtr) const
{
    if (treePtr != nullptr)
    {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
   rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const BinaryNodeTree<ItemType>* leftTreePtr,
                                         const BinaryNodeTree<ItemType>* rightTreePtr)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), 
                                                 copyTree(rightTreePtr->rootPtr));
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
   rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
   destroyTree(rootPtr);
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
   BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
   rootPtr = balancedAdd(rootPtr, newNodePtr);
   return true;
}  // end add

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
    destroyTree(rootPtr);
    rootPtr = nullptr;
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
    if (isEmpty()) {
        throw PrecondViolatedExcep("getRootData() called when the tree is empty.");
    }
    // else return the item
    return rootPtr->getItem();
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem)
{
    if (isEmpty())
        rootPtr = new BinaryNode<ItemType>(newItem, nullptr, nullptr);
    else
        rootPtr->setItem(newItem);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target)
{
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, target, isSuccessful);
    return isSuccessful;
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
    bool isSuccessful = false;
    BinaryNode<ItemType>* binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful);
    
    if (isSuccessful)
        return binaryNodePtr->getItem();
    else
        throw NotFoundException("Entry does not exist in tree.");
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
   inorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    preorder(visit, rootPtr);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    postorder(visit, rootPtr);
}

