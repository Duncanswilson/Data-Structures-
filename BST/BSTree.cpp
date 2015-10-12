#include "BSTree.h"
/**
The Node constructor takes in parameterized data and sets it to the appropriate
data members.   
 
@param a template value of data, a node left pointer, and a node right pointer  
@pre none 
@post a node is created with the parametrized data  
@return none 
*/
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
 {
   dataItem = nodeDataItem; 
   left = leftPtr; 
   right = rightPtr; 
 }
/**
The binary search tree constructor sets its root pointer to NULL. 
 
@param none
@pre  none 
@post the root pointer is set to NULL  
@return none  
*/
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTree()
  {
   root = NULL; 
  }


/**
The binary search tree copy constructor checks if the source tree's root is 
equal to NULL. If not it assigns the return value of the copyhelper function
to the value of root.  
 
@param a source tree for copying 
@pre  if the source tree isn't empty 
@post a copy of the source tree  (made using the copy helper) is set assigned to root  
@return none  
*/
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>::BSTree(const BSTree <DataType, KeyType>& src)
     {
      if(src.root != NULL)
       {
        BSTreeNode *temp = NULL; 
        root = copyHelper(src.root, temp); 
       }
     }
/**
The overloaded assignment operator checks the addresses of source and this, and if not equal it clears any data left in this and calls assigns the return value from copy helper to root.  
 
@param a source tree for copying 
@pre  if the addresses of the source and this don't match  
@post a copy of the source tree  (made using the copy helper) is set assigned to root  
@return this binary search tree is returned (for chaining) 
*/
template < typename DataType, class KeyType > 
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>:: operator=(const 				BSTree<DataType,KeyType>& src)
   {
     if(&src != this)
       {
        clear(); 
        BSTreeNode* temp; 
        root = copyHelper(src, temp); 
       }
     return *this; 
   }
/**
The binary search tree destructor calls the destructor helper function and then sets the root pointer to NULL. 
 
@param none
@pre   none   
@post  the tree is destructed and the root pointer is set equal to NULL
@return  none 
*/
template < typename DataType, class KeyType >
 BSTree<DataType,KeyType>:: ~BSTree()
  {
     dHelper(root); 
  }
/**
The binary seach tree destructor helper loops while the current node being evaluated is an operator, if so it recursively calls itself in both the left and right direction.

If the current node left or right pointers equal  NULL, it deletes the node and then sets the pointer to NULL. 

@param a pointer to the current node in a tree to be destructed 
@pre   none 
@post  the tree is destructed recursively 
@return  none 
*/ 
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>:: dHelper(BSTreeNode*& current)
  {
   if(current == NULL)
     {return;}
   else{
     dHelper(current->left); 
     dHelper(current->right);     
     delete current; 
     current = NULL; 
  } 
 }
/**
The inser function calls the insert helper and passes in the root pointer. 
 
@param data to be inserted 
@pre   none 
@post  the root is passed in by reference and assigned when insert helper is finished
@return none  
*/
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>::insert(const DataType& newdataItem)
  {
    iHelper(root, newdataItem); 
  }
/**
The binary search tree recursively loops through the tree until it has correctly gone to the correct null pointer in the tree by doing comparisons between the passed in data and the data at the pointer. Once the pointer is null, it is assigned to a node with the parameterized data. 

@param the current node pointer in the expression tree being inserted 
@pre   none
@post  the pointer passed into the final instance of the function is assigned the leaf of the new data 
@return none  
*/
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>::iHelper (BSTreeNode*& current,const DataType data) 
  {
    if(current == NULL) 
       current = new BSTreeNode(data, NULL, NULL); 
   else if(current->dataItem.getKey() > data.getKey())
     {
      iHelper(current->left, data);
     }
   else if(current->dataItem.getKey() < data.getKey())
     {
       iHelper(current->right, data); 
     }
  }
/**
The retreive function calls the reteive helper and passes in the root pointer. 
 
@param data to be retrieved, and a variable to assign the data to
@pre   if root not equal to null  
@post  the root and the two data variables is passed into the helper by reference and assigned when retireve helper is finished
@return boolean statement on whether retrived  
*/
template < typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::retrieve ( const KeyType& searchKey, 
                                        DataType& searchdataItem) const
 {
  if(root != NULL)
    {
     return retHelper(root,searchKey, searchdataItem);
    }
  else{
   return false; 
  }
 }
/*
The binary search tree function retHelper recursively loops through the tree until it has correctly gone to the pointer matching the paramterized data until it finds the equal data or it as gone too far. Sets searchData equal to the value aand then returns a true if found false otherwise 

@param the current node pointer in the expression tree being retreived 
@pre   if root was not null in the calling function 
@post  search data is set to the data found 
@return boolean of wheter data was found or not   
*/
template < typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::retHelper(BSTreeNode* const& current, 
				       const KeyType& searchKey,DataType& searchData ) const
 {
  if (current->dataItem.getKey() == searchKey)
     {
      searchData = current->dataItem; 
      return true; 
     }
  else if(current->dataItem.getKey() > searchKey && current->left != NULL)
     {
      retHelper(current->left, searchKey, searchData);
     }
   else if(current->dataItem.getKey() < searchKey && current->right != NULL)
     {
      retHelper(current->right, searchKey, searchData);
     }
   else if(current->right == NULL && current->left == NULL)
     {
      return false;  
     }
 }
/**
The remove function calls the remove helper and passes in the root pointer and deleteKey. 
 
@param data to be removed
@pre   none
@post  data will be removed
@return boolean statement on whether removed  
*/
template < typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::remove(const KeyType& deleteKey )
 {  
  return rHelper(root, deleteKey);
 }  
/*
The binary search tree function rHelper recursively loops through the tree until it has correctly gone to the pointer matching the paramterized data until it finds the equal data. Removes data equal to the value and then returns a true if found false otherwise 

@param the current node pointer in the expression tree being removed 
@pre   if root was not null in the calling function 
@post  data was deleted if found
@return boolean of wheter data was found or not   
*/
template < typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::rHelper(BSTreeNode*& current, 
                                       const KeyType& deleteKey) 
 { 
  if(current == NULL)
   {   
    return false; 
   } 
  else if(current->dataItem.getKey() > deleteKey)
    {
    return rHelper(current->left, deleteKey);
    }
  else if(current->dataItem.getKey() < deleteKey)
    {
    return rHelper(current->right, deleteKey); 
    }
  if(current-> dataItem.getKey() == deleteKey) 
    {
      //case 1 0 children
      if(current->left == NULL && current-> right == NULL)
       {
        delete current; 
        current = NULL;
        return true;
       }
      //case 2 1 children on left
       else if(current->left != NULL && current->right == NULL)
       {
        BSTreeNode *temp = current;
        current = current->left; 
        delete temp; 
        return true;  
       } 
      //case 2 1 children on right
      else if(current->right != NULL && current->left == NULL)
      {
       BSTreeNode *temp = current;
       current = current->right; 
       delete temp; 
       return true; 
      }
      //case 3 2 children
      else
      {
       BSTreeNode *temp = current;
       temp = current->left; 
       while(temp->right != NULL) 
         temp = temp->right;
       current->dataItem = temp->dataItem;
       rHelper(current->left, current->dataItem.getKey()); 
       return true; 
      }  
    } 
 }
/**
The writeKey function calls the writeKey helper and passes in the root pointer. 
 
@param none
@pre   none
@post  helper function called with a endl after 
@return none 
*/
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>::writeKeys () const
 {
  wHelper(root); 
    cout <<endl;
 }
/*
The binary search tree function wHelper recursively loops through the tree until it has correctly outpu all of the data return when the pointer is null 

@param the current node pointer in the expression tree being written 
@pre   if current not null
@post  data is output in order
@return none
*/
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>::wHelper(BSTreeNode* current) const 
 {
  if (current == NULL)
   {
    return;
   }
  else if(current->left == NULL && current->right == NULL) 
   cout << current-> dataItem.getKey() <<" "; 
  else{
   wHelper(current->left); 
   cout << current->dataItem.getKey() <<" "; 
   wHelper(current->right); 
  }
 }
/**
The clear function calls the destructor helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the destructor helper
@return none  
*/
template < typename DataType, class KeyType>
void BSTree<DataType,KeyType>::clear ()
 {
   if(!isEmpty())
    {
       dHelper(root); 
    }
 }
/**
The isEmpty function returns true if empty false if not. 
 
@param none
@pre   none 
@post  none
@return boolean value of if true of not  
*/
template < typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::isEmpty () const
 {
   if(root == NULL)
     return true; 
  else 
    return false; 
 }
/**
Outputs the keys in a binary search tree. The tree is output
rotated counterclockwise 90 degrees from its conventional
orientation using a "reverse" inorder traversal. This operation is
intended for testing and debugging purposes only.

@param none
@pre   if not empty
@post  the root is passed into the show helper & outputs an endl
@return none 
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const
{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}
/**
Recursive helper for showStructure. 
Outputs the subtree whose root node is pointed to by p. 
Parameter level is the level of this node within the tree.

@param pointer to the current node and a level int 
@pre   p not equal to 0 
@post  the tree is output 
@return void
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const
{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}
/**
The getCount function calls the counter helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the counter helper
@return none  
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getCount() const
  {
    return countHelper(root); 
  }
 /**
Recursive helper for getCount. 
Returns the total number of nodes in the tree. 

@param pointer to the current node 
@pre   current is equal to NULL 
@post  total number of nodes is counted
@return returns the number of items in the tree 
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::countHelper(BSTreeNode* current) const
 {
   if(current == NULL)
    return 0; 
   else{
     return(1+countHelper(current->left)+countHelper(current->right));  
   }
 }
/**
The getHeight function calls the height helper and passes in the root pointer. 
 
@param none
@pre   none 
@post  the root is passed into the height helper
@return none  
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::getHeight() const
 {
  return hHelper(root); 
 }
 /**
Recursive helper for getHeight. 
Returns the longest height found in the tree. 

@param pointer to the current node 
@pre   current is equal to NULL 
@post  total number of nodes is counted per side from the root  
@return returns the height of the tree 
*/
template < typename DataType, typename KeyType >
int BSTree<DataType,KeyType>::hHelper(BSTreeNode* current) const
 {
  if(current == NULL)
    return 0; 
  else{
   int hLeft = hHelper(current->left); 
   int hRight = hHelper(current->right);
   if(hLeft >= hRight) 
    return (hLeft+1);
   else 
    return (hRight+1);
  }
 }









