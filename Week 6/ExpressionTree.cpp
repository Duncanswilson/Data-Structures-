#include "ExpressionTree.h"
#include <cstdlib>
#include "show8.cpp"
#include <sstream>
/**
The Node constructor takes in parameterized data and sets it to the appropriate
data members.   
 
@param a char value of data, a node left pointer, and a node right pointer  
@pre none 
@post a node is created with the parametrized data  
@return none 
*/
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
  {
    right = rightPtr; 
    left = leftPtr;
    dataItem = elem;
  }
/**
The expression tree constructor sets its root pointer to NULL. 
 
@param none
@pre  none 
@post the root pointer is set to NULL  
@return none  
*/
template <typename DataType>
ExprTree<DataType>::ExprTree()
  {
   root = NULL;
  }

/**
The expression tree copy constructor checks if the source tree's root is 
equal to NULL. If not it assigns the return value of the copyhelper function
to the value of root.  
 
@param a source tree for copying 
@pre  if the source tree isn't empty 
@post a copy of the source tree  (made using the copy helper) is set assigned to root  
@return none  
*/
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& src)
  {
   if(src.root != NULL) 
   root = copyHelper(src.root);
  }
/**
The overloaded assignment operator checks the addresses of source and this, and if not equal it clears any data left in this and calls assigns the return value from copy helper to root.  
 
@param a source tree for copying 
@pre  if the addresses of the source and this don't match  
@post a copy of the source tree  (made using the copy helper) is set assigned to root  
@return this expression tree is returned (for chaining) 
*/
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>:: operator=(const ExprTree& src)
  {
  if(this != &src)
    {
     clear(); 
     root = copyHelper(src->root); 
    }
   return *this; 
  }
/**
The expression tree destructor calls the destructor helper function and then sets the root pointer to NULL. 
 
@param none
@pre   none   
@post  the tree is destructed and the root pointer is set equal to NULL
@return  none 
*/
template <typename DataType>
ExprTree<DataType>::~ExprTree()
  {
    dHelper(root);
    root = NULL; 
  }
/**
The expression tree destructor helper loops while the current node being evaluated is an operator, if so it recursively calls itself in both the left and right direction.

If the current node left or right pointers equal  NULL, it deletes the node and then sets the pointer to NULL. 

@param a pointer to the current node in a tree to be destructed 
@pre   none 
@post  the tree is destructed recursively 
@return  none 
*/ 
template <typename DataType>
void ExprTree<DataType>::dHelper(ExprTreeNode*& current)
  {
   while(current != NULL && current->left != NULL && current->right != NULL)
    {
     dHelper(current -> left); 
     dHelper(current->right); 
    }
   if(current != NULL)
     {
     delete current; 
     current = NULL; 
     }
  }

/**
The build function calls the build helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed in by reference when build helper is finished, root points to the built tree   
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::build()
  {
    bHelper(root); 
  } 
/**
The expression tree build helper reads in a char value from the keyboard and checks if it is a digit or an operator. If it is a digit it creates the new node and returns, else if it is an operator then the operator node is created and then the build helper is recursively called on both the left pointer and the right pointer 

@param the current node pointer in the expression tree being built 
@pre   the data must be either a digit or operator 
@post  the original pointer passed into the function is assigned the root of the built tree 
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::bHelper(ExprTreeNode*& current) 
  {
   char data; 
   cin >> data; 
   if(isdigit(data))
    {
     current = new ExprTreeNode(data, NULL, NULL); 
    }
   else if(data =='+' || data == '-' || data =='/' || data == '*')
    {
      current = new ExprTreeNode(data, NULL, NULL); 
      //build left 
      bHelper(current-> left); 
      //build right 
      bHelper(current -> right); 
    }
   return; 
  }
/**
The expression function calls the expression helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the expression helper
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::expression() const
  {
    eHelper(root); 
  }

/**
The expression helper traverses the tree in order and prints the statement to the screen in-order with parentheses showing the traditional order of operations.  

@param the current node pointer in the expression tree being expressed 
@pre   the data at the current pointer must be either an operator or digit 
@post  the expression tree is output to the screen with parentheses  
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::eHelper(ExprTreeNode* current) const
  {
   if(isdigit(current->dataItem))
     {
       cout << current->dataItem; 
     }
   else if(current->dataItem =='+' || current->dataItem == '-' ||
           current->dataItem =='/' || current->dataItem == '*')
     {
      cout<< "(";
      eHelper(current->left); 
      cout << current->dataItem; 
      eHelper(current->right); 
      cout<<')'; 
     }
  }
/**
The evaluate function calls the evaluate helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the evaluate helper
@return none  
*/
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
  {
     return evalHelper(root); 
  } 
/**
The evaluate helper traverses the tree pre-order and enacts the mathematical operations and returns the value of the evaluated tree. 

@param the current node pointer in the expression tree being evaluated 
@pre   the data at the current pointer must be either an operator or digit 
@post  the expression tree is evaluated
@return the value of the evaluated function 
*/    
template <typename DataType>
float ExprTree<DataType>::evalHelper(ExprTreeNode* current) const throw (logic_error)
  {
    if(isdigit(current->dataItem))
     {
      // use of stringstream opperations waas found and applied from cplusplus.com 
      float x = current->dataItem - '0';
      return x;
     }
    else if(current->dataItem == '*')
     {
      return(evalHelper(current->left) * evalHelper(current->right)); 
     }
    else if(current->dataItem == '/')
     {
      return(evalHelper(current->left) / evalHelper(current->right));
     }
    else if(current->dataItem == '+')
     { 
      return(evalHelper(current->left) + evalHelper(current->right));
     }
    else if(current->dataItem == '-')
     { 
      return(evalHelper(current->left) - evalHelper(current->right));
     }
  }
/**
The clear function calls the destructor helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the destructor helper
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::clear()
  {
    dHelper(root);
 
  }
/**
The commute function calls the commute helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the commute helper
@return none  
*/
template <typename DataType>
void ExprTree<DataType>::commute()
  {
   cHelper(root);   
  }
/**
The commute helper traverses the tree in post-order, recursively, and swaps the left and right data item as long as the current dataItem is a digit. 

@param the current node pointer in the expression tree being commuted 
@pre   the data at the current pointer must be a digit 
@post  the expression tree is commuted
@return none
*/    
template <typename DataType>
void ExprTree<DataType>::cHelper(ExprTreeNode*& current)
  {
   if(!isdigit(current->dataItem))
    {
     cHelper(current->left);
     cHelper(current->right);
     ExprTreeNode *temp = current->left; 
     current->left = current->right;
     current->right = temp; 
    }
   else 
    {
     return; 
    }
  }
 /**
The isEquivalent function calls the equal helper and passes in a temp expression tree node pointer that equals the root pointer (due to the function being constant). 
 
@param the tree which is compared to the tree which called the function 
@pre   none 
@post  the equal helper returns a boolean of the result 
@return a boolean value representing whether the trees were equal 
*/ 
template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
  {
   ExprTreeNode* temp = root; 
    return equalHelper(temp, source.root);
  }
/**
The equal helper traverses the tree pre-order and compares values at the current data item of both parameterized trees, returning a boolean value representing the result of the total comparison. 

@param two node pointers to the current expression tree nodes being compared 
@pre   none 
@post  the two trees are compared with the result in boolean returned 
@return the boolean result value of the comparison 
*/  
template <typename DataType>
bool ExprTree<DataType>::equalHelper(ExprTreeNode* first, ExprTreeNode* second) const
  { 
    if(first == NULL && second == NULL)
      return true;  
 
    else if(first == NULL && second != NULL || first == NULL && second != NULL)
       return false;

    if(first->dataItem == second->dataItem && 
      (first->dataItem == '+' || first->dataItem == '*'))
     {
      return((equalHelper(first->left, second->left) && equalHelper(first->right, second->right))|| (equalHelper(first->left, second->right) && equalHelper(first->right, second->left)) );
     }
    if(first->dataItem == second->dataItem && 
      (first->dataItem == '/' || first->dataItem == '-'))
     {
      return(equalHelper(first->left, second->left) && equalHelper(first->right, second->right));
     }
    else if(first->dataItem == second->dataItem && isdigit(first->dataItem))
    {
     return true;
    } 
     return false; 
  }





