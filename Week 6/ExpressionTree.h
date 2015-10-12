//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
/**
@file ExpressionTree.h
@author Duncan Wilson 
*/
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class ExprTree {
//////////////////////////////////////////////////////////////////////////////////////
  private:
    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };
/**
A helper function used to make a copied version of the 
Expression Tree whose pointer is in the parameters. 
 
@param the current pointer in the source tree 
@pre if the current source pointer is not null 
@post a temp copy tree is created using the source data 
@return the address of the copied tree 
*/
ExprTreeNode* copyHelper(ExprTreeNode* current)
  {
    if(current == NULL)
       return NULL; 
     else{
     ExprTreeNode* temp = new ExprTreeNode(current->dataItem, NULL, NULL);
     temp->left = copyHelper(current->left);
     temp->right = copyHelper(current->right);
     return temp;
     } 
  }

void showHelper ( ExprTreeNode *p, int level ) const;
void dHelper(ExprTreeNode*& current); 
void bHelper(ExprTreeNode*& current);
void eHelper(ExprTreeNode* current) const; 
float evalHelper(ExprTreeNode* current) const throw (logic_error); 
void cHelper(ExprTreeNode*& current);
bool equalHelper(ExprTreeNode* first, ExprTreeNode* second) const;
    // Data member
    ExprTreeNode *root;   // Pointer to the root node

/////////////////////////////////////////////////////////////////////////////////////
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();
    bool isEquivalent(const ExprTree& source) const;

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

};
#endif		// #ifndef EXPRESSIONTREE_H
