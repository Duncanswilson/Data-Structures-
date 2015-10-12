#include "Heap.h" 
/**
The Heap constructor allocates the memory to dataItems pointer and sets maxSize and size accordingly. 
 
@param an int representing the maximum number of items in an array  
@pre none 
@post the heap is allocated and sizes are set 
@return none 
*/
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap(int maxNumber)
   {
    dataItems = new DataType[maxNumber];
    maxSize = maxNumber; 
    size = 0; 
   }
/**
The Heap copy constructor takes a parameterized heap and allocates the appropriate memory to match the copy.    
 
@param a const heap by reference (to save memory) 
@pre none
@post a copy heap is created with the parametrized data  
@return none 
*/
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::Heap(const Heap<DataType,KeyType,Comparator>& other)
   {
    dataItems = new DataType[other.maxSize];
    for(int i = 0; i < other.size; i++)
      {
       dataItems[0] = other.dataItems[i];
      }
   }
/**
The overloaded assignment operator is the copy constructor with an added check to see if the addresses are already matching. If so it returns a dereferenced this pointer. Else it copies the data by the algorithm outlined via the copy constructor and then returns a dereferenced this pointer. 
 
@param a const heap by reference (memory conservation)
@pre if the calling address is not equal to the address of the parameterized heap 
@post a copy heap is allocated 
@return the copied heap is returned 
*/
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>& Heap<DataType,KeyType,Comparator>::operator=(const Heap& other)
   {
    if(this != &other)
      {
       clear(); 
       dataItems = new DataType[other.maxSize];
       for(int i = 0; i < other.size; i++)
        {
         dataItems[0] = other.dataItems[i];
        }
      }
    return *this; 
   }
/**
The destructor deallocates all memory asscociated with the heap. 
 
@param none
@pre none
@post the heap has no memory further allocated to it  
@return none
*/
template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType,KeyType,Comparator>::~Heap()
   {
    delete dataItems;
   }
/**
The insert function if the heap is not full then it inserts the parameterized data into the last spot of the array and then sorts it accordingly. 
 
@param a datatype variable that is to be inserted 
@pre if not full  
@post the data is inserted and sorted accordingly  
@return none 
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::insert(const DataType& newDataItem) throw ( logic_error )
   {
    if(isFull())
      throw logic_error ("Heap is full!"); 
    else
     {
      dataItems[size++] = newDataItem; 
      heapHelper(size-1);  
     }
   }
/**
The heap helper function compares the data at the index passed into it with the data at the index of the parent which is retrieved through the getParent function. Then if the templeted comparator function dictates it swaps the data and calls itself. 
 
@param an index of the current data to be compared 
@pre if comparator returns true
@post swaps data and calls itself 
@return none
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::heapHelper(int me)
   {
    int parent = getParent(me);  
    if(compare(dataItems[me].getPriority(), dataItems[parent].getPriority())) 
     {
      swap(parent, me); 
      heapHelper(parent); 
     }
   }
/**
The remove functions pops removes the first data item in the heap if it is not empty. Then it places the last data item at the index of the removed data and calls the reheapify function. It also returns the removed data
 
@param none
@pre if not empty 
@post removes the top data item and resorts the heap 
@return the past top data item of the heap 
*/
template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType,KeyType,Comparator>::remove() throw (logic_error)
   {
    DataType d;
    if(isEmpty())
      throw logic_error ("Heap is empty!"); 
    else
     { 
      d = dataItems[0];
      dataItems[0] = dataItems[--size];  
      reHeapify(0); 
     }
    return d; 
   }
/**
The reheapify takes in an index as a parameter, it then get the left and right child off of this index. It has three cases, if left child is out of bounds, if right child is out of bounds and if both are in bounds. It makes necessary swaps and self calls. 
 
@param the index of the current item 
@pre none
@post the heap is sorted back into the order dictated by the comparator funciton
@return none
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::reHeapify(int current)
   {
    int lChild = getLeftChild(current); 
    int rChild = getRightChild(current); 
    if(lChild >= size)
     {
      return;
     }
    else if (rChild >= size)
     {
      if(compare(dataItems[lChild].getPriority(), dataItems[current].getPriority()))
        {
         swap(current, lChild); 
         return; 
        }
     }
    else 
     {
      int maxChild = lChild; 
      if(compare(dataItems[rChild].getPriority(), dataItems[maxChild].getPriority()))
        maxChild = rChild; 
      if(compare(dataItems[maxChild].getPriority(), dataItems[current].getPriority()))
        {
         swap(current, maxChild); 
         reHeapify(maxChild); 
        } 
     }
   }
/**
Swaps the data items using a temp variable. 
 
@param the two items to be swapped
@pre none
@post the data items are swapped 
@return none
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::swap(int parent, int child)
   {
    DataType temp = dataItems[parent]; 
    dataItems[parent] = dataItems[child]; 
    dataItems[child] = temp; 
   }
/**
Clears the heap by setting size to 0 

@param none
@pre none
@post heap's size is set to 0  
@return none
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::clear()
   {
    size = 0; 
   }
/**
isEmpty returns if the size is equal to 0 or not
 
@param none
@pre none
@post if the size is 0 return true else return false  
@return a truth statemnt representing whether or not the heap is empty
*/
template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isEmpty() const
   {
    return(size == 0);
   }
/**
isFull checks if the size equals maxSize
 
@param none
@pre none
@post returns if the heap is full or not
@return a truth statemnt representing whether or not the heap is full
*/
template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType,KeyType,Comparator>::isFull() const
   {
    return(size == maxSize); 
   }
/**
getParent returns the value of the parameterized index minus one and then divided by two

@param the index to get the parent of
@pre none
@post calulates the index of the parent
@return the index of the parent is returned
*/
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType,KeyType,Comparator>::getParent(int me) const
   {
    return ((me-1)/2); 
   }
/**
getLeftChild returns the value of the parameterized index multiplied by two with one added to it

@param the index to get the leftChild of
@pre none
@post calulates the index of the leftChild
@return the index of the leftChild is returned
*/
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType,KeyType,Comparator>::getLeftChild(int me) const
   {
    return((2*me)+1); 
   }
/**
getRightChild returns the value of the parameterized index multiplied by two with two added to it 

@param the index to get the rightChild of
@pre none
@post calulates the index of the rightChild
@return the index of the rightChild is returned
*/
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType,KeyType,Comparator>::getRightChild(int me) const
   {
    return((2*me)+2); 
   }

/**
Outputs the priorities of the data items in a heap in both array and tree form. If the heap is empty, outputs "Empty heap". This operation is intended for testing/debugging purposes only.

@param none
@pre none
@post prints the heap 
@return none 
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const
{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

/**
Helper function for the showStructure() function. Outputs the subtree (subheap) whose root is stored in dataItems[index]. Argument level is the level of this dataItems within the tree.

@param the current level and current index 
@pre if index is less than size 
@post the heap is displayed as a tree 
@return none 
*/

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const
{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}
/**
The write levels function outputs the data in the heap with a newline between each level if not empty. 

@param the current level and current index 
@pre if not empty 
@post the heap is output by level  
@return none 
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: writeLevels () const
  {
   if(isEmpty())
    {
     return;
    } 
   else
   { 
    int leveladj = 1; 
    for(int i = 0; i <size;)
      {
       for(int j=1; j<= leveladj && i <size; j++, i++) 
         {
          cout << dataItems[i].getPriority() <<' ';
         } 
          cout << endl; 
          leveladj = leveladj*2; 
       }
   }
}


