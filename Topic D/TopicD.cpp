//
//  main.cpp
//  Topic D
//
//  Created by user on 10/13/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//
// Status: Working in Xcode
// Note: May need VS Pragma. Do not include in the build: BinarySearchTree.cpp, BinaryNodeTree.cpp.
// Also note, that I again had issues in Xcode with windows /crlf endings. You may notice in soundtrack.cpp >> operator, that I used /r as delim instead of /n
// I dont know what consequences this has for Visual Studio, or if there are any.

#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include "Soundtrack.h"

template<class ItemType>
void display(ItemType& entries);

bool readInput(BinarySearchTree<int>  &obj, const string & filename);
bool readInputST(BinarySearchTree<soundtrack>  &obj, const string & filename);

int main() {
    
    cout << "Create default int tree bst1" << endl << endl;
    BinarySearchTree<int> bst1;
    cout << "Display bst1" << endl;
    cout << "Preorder:" << endl;
    bst1.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bst1.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bst1.postorderTraverse(display);
    
    cout << "Read values from input file" << endl;
    cout << "Put release year values into bst1" << endl;
    readInput(bst1,"Topic A Soundtrack.txt");
    
    cout << "Next, insert following values into bst1 in this order: 1 2 -10 15 -20 0 10" << endl;
    bst1.add(1);
    bst1.add(2);
    bst1.add(-10);
    bst1.add(15);
    bst1.add(-20);
    bst1.add(0);
    bst1.add(10);

    cout << "Display bst1" << endl;
    cout << "Preorder:" << endl;
    bst1.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bst1.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bst1.postorderTraverse(display);
    
    cout << "Height of bst1 is " << bst1.getHeight() << endl << endl;
    cout << "Number of nodes in bst1 is " << bst1.getNumberOfNodes() << endl << endl;
    
    
    cout << "Retrieve value using getEntry -10 from the tree:" << endl << endl;
    cout << "Found " << bst1.getEntry(-10) << " in tree bst1" << endl;
    
    
    cout << "Use contains to see if value 11 is in the tree:" << endl;
    cout << "11 " << (bst1.contains(11) ? "IS" : "NOT") << " found in bst1" << endl;
    
    
    cout << "Create bst2, a pointer to BinarySearchTree, from bst1" << endl;
    BinarySearchTree<int>* bst2 = new BinarySearchTree<int>(bst1);
    
    cout << "Display bst2" << endl;
    cout << "Preorder:" << endl;
    bst2->preorderTraverse(display);
    cout << "Inorder:" << endl;
    bst2->inorderTraverse(display);
    cout << "Postorder:" << endl;
    bst2->postorderTraverse(display);
    
    cout << "Height of bst2 is " << bst2->getHeight() << endl << endl;
    cout << "Number of nodes in bst2 is " << bst2->getNumberOfNodes() << endl << endl;
    
    cout << "Delete 2014 from bst2" << endl;
    cout << "2014 " << (bst2->remove(2014) ? "deleted" : "not deleted") << " from bst2" << endl;
    
    cout << "Delete 2014 from bst2" << endl;
    cout << "2014 " << (bst2->remove(2014) ? "deleted" : "not deleted") << " from bst2" << endl;
    
    cout << "Display bst2" << endl;
    cout << "Preorder:" << endl;
    bst2->preorderTraverse(display);
    cout << "Inorder:" << endl;
    bst2->inorderTraverse(display);
    cout << "Postorder:" << endl;
    bst2->postorderTraverse(display);
    
    cout << "Height of bst2 is " << bst2->getHeight() << endl << endl;
    cout << "Number of nodes in bst2 is " << bst2->getNumberOfNodes() << endl << endl;
    
    cout << "Create bst3 then assign bst2 to bst3" << endl << endl;
    BinarySearchTree<int> bst3;
    bst3 = *bst2;
    
    
    cout << "Display bst3" << endl;
    cout << "Preorder:" << endl;
    bst3.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bst3.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bst3.postorderTraverse(display);
    
    cout << "Height of bst3 is " << bst3.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bst3.getNumberOfNodes() << endl << endl;
    
    
    // Press enter to continue
    cout << "Press Enter to continue --> ";
    cin.ignore();cin.ignore(); //Once isnt enough?
    
    
    cout << "Create bstT1 which is a binary search tree of soundtrack objects" << endl;
    cout << "Put soundtrack records into bstST1" << endl;
    BinarySearchTree<soundtrack> bstST1;
    readInputST(bstST1,"Topic A Soundtrack.txt");
    
    
    cout << "Display bstST1" << endl;
    cout << "Preorder:" << endl;
    bstST1.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST1.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST1.postorderTraverse(display);
    
    cout << "Height of bstST1 is " << bstST1.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST1.getNumberOfNodes() << endl << endl;
    
    cout << "Create bstST2 from bstST1" << endl;
    BinarySearchTree<soundtrack> bstST2 = bstST1;
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    
    // Press enter to continue
    cout << "Press Enter to continue --> ";
    cin.ignore();cin.ignore(); //Once isnt enough?
    
    
    cout << "Search bstST2 using getEntry for the object that has Godzilla as a title" << endl << endl;
    
    soundtrack search;
    search.setTitle("Godzilla");
    
    try
    {
        bstST2.getEntry(search);
        cout << "Found.  The object consists of " << bstST2.getEntry(search);
    }
    catch (NotFoundException&  error)
    {
        cout << error.what() << endl;
    }
    
    cout << "Search bstST2 using getEntry for the object that has godzilla as a title" << endl << endl;
    
    search.setTitle("godzilla");
    
    try
    {
        bstST2.getEntry(search);
        cout << "Found.  The object consists of " << bstST2.getEntry(search);
    }
    catch (NotFoundException&  error)
    {
        cout << error.what() << endl;
    }
    
    
    cout << "Delete the object from bstST2 with the title Much Ado About Nothing, a leaf" << endl << endl;
    search.clear();
    search.setTitle("Much Ado About Nothing");
    cout << "\"Much Ado About Nothing\" " << (bstST2.remove(search) ? "deleted" : "not deleted") << " from bstST2" << endl;
    
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    cout << "Delete the object from bstST2 with the title Moonfleet, a tree with only a right subtree" << endl << endl;
    search.clear();
    search.setTitle("Moonfleet");
    cout << "\"Moonfleet\" " << (bstST2.remove(search) ? "deleted" : "not deleted") << " from bstST2" << endl;
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    cout << "Delete the object from bstST2 with title Godzilla, a tree with two subtrees whose right child is the inorder successor" << endl << endl;
    search.clear();
    search.setTitle("Godzilla");
    cout << "\"Godzilla\" " << (bstST2.remove(search) ? "deleted" : "not deleted") << " from bstST2" << endl;
    
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    
    cout << "Delete the object from bstST2 with the title King of Hearts, a tree with two children whose right child is NOT the inorder successor" << endl << endl;
    search.clear();
    search.setTitle("King of Hearts");
    cout << "\"King of Hearts\" " << (bstST2.remove(search) ? "deleted" : "not deleted") << " from bstST2" << endl;
    
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    
    
    cout << "Retrieve the object with title Psycho using contains" << endl << endl;
    search.clear();
    search.setTitle("Psycho");
    cout << "\"Psycho\" " << (bstST2.contains(search) ? "found" : "not found") << " in bstST2" << endl;
    
    
    cout << "Display bstST2" << endl;
    cout << "Preorder:" << endl;
    bstST2.preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST2.inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST2.postorderTraverse(display);
    
    cout << "Height of bstST2 is " << bstST2.getHeight() << endl << endl;
    cout << "Number of nodes in bst3 is " << bstST2.getNumberOfNodes() << endl << endl;
    
    
    // Press enter to continue
    cout << "Press Enter to continue --> ";
    cin.ignore();cin.ignore(); //Once isnt enough?
    
    cout << "Create bstST3, a pointer to BinarySearchTree, and then assign bstST2 to it" << endl << endl;
    BinarySearchTree<soundtrack>* bstST3 = new BinarySearchTree<soundtrack>;
    *bstST3 = bstST2;
    
    cout << "Display bstST3" << endl;
    cout << "Preorder:" << endl;
    bstST3->preorderTraverse(display);
    cout << "Inorder:" << endl;
    bstST3->inorderTraverse(display);
    cout << "Postorder:" << endl;
    bstST3->postorderTraverse(display);
    
    cout << "Height of bstST3 is " << bstST3->getHeight() << endl << endl;
    cout << "Number of nodes in bstST3 is " << bstST3->getNumberOfNodes() << endl << endl;
    
    
    
    cout << endl << endl << "Program Over" << endl << endl;
    cin.ignore();
    
    // Press enter to end
    cout << "Press Enter to end --> ";
    cin.ignore();cin.ignore(); //Once isnt enough?
    
    return 0;
}

template<class ItemType>
void display(ItemType& entries)
{
    cout << entries << endl;
}

bool readInput(BinarySearchTree<int> &obj, const string & filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "\nInput file" << filename << " cannot be found" << endl;
        return false;
    }
    
    soundtrack sound;
    string line;
    int year;
    while (!in.eof())
    {
        getline(in,line);
        year = std::stoi(line.substr(111,5));
        obj.add(year);
    }
    
    return true;
}

bool readInputST(BinarySearchTree<soundtrack> &obj, const string & filename)
{
    ifstream in(filename);
    if (!in)
    {
        cout << "\nInput file" << filename << " cannot be found" << endl;
        return false;
    }
    
    soundtrack sound;
    
    while (!in.eof())
    {
        in >> sound;
        obj.add(sound);
    }
    
    return true;
}
