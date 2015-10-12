#include "ListLinked.h"

// List Constructor: 
// creates an empty list. The parameter is left to match a possible array implementation of the class 
template <typename DataType>
List<DataType>::List(int ignored)
   {
    cursor = head = NULL; 
   }

// List Copy Constructor: 
//  Creates a new list, identical to the "other" list 
template <typename DataType>
List<DataType>::List(const List<DataType>& other)
   {
    ListNode *cursorTemp;
    bool first = true;
    cursorTemp = other.head;
    while(cursorTemp -> next != NULL)
       { 
        if(first){
          head = new ListNode (cursorTemp -> dataItem, NULL);
          first = false; 
          cursor = head;
          cursorTemp = cursorTemp -> next;
         }
        else{
        cursor -> next = new ListNode   (cursorTemp-> dataItem, NULL);       
        cursorTemp = cursorTemp -> next;
        cursor = cursor-> next;
        }             
       }
     cursor -> next =  new ListNode  (cursorTemp-> dataItem, NULL);      
     cursor = cursor-> next;
   }

// Overloaded assingment operator: 
// Sets the list to match the "other" list
template <typename DataType>
List<DataType>& List<DataType>:: operator=(const List<DataType>& other) 
   {
    ListNode *cursorTemp = other.head; 
    clear();  
    if(other.isEmpty())
     { 
      return *this; 
     }
    else 
     {
      head = cursor = new ListNode (cursorTemp->dataItem, NULL);
      cursorTemp = cursorTemp->next; 
     while(cursorTemp != NULL)
        {
         cursor->next = new ListNode  (cursorTemp->dataItem, NULL); 
         cursorTemp = cursorTemp ->next; 
         cursor = cursor->next; 
        }   
     cursor = head; 
     }
    return *this; 
   }

// List Destructor: 
// Deallocates all of the list's memory 
template <typename DataType>
List<DataType>:: ~List()
   {
    clear(); 
   }

// insert: 
// if not empty then this function inserts data after cursor 
template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
   {
    if(!isEmpty()) 
      {
       cursor = cursor->next = new ListNode (newDataItem, cursor->next);
      }
    else 
     {
      head = cursor = new ListNode  (newDataItem, NULL);  
     }
   }

// remove: 
// if not empty, removes data at cursor. Then moves the cursor to the next available node. 
// if at end, cursor is set to head 
template <typename DataType> 
void List <DataType>::remove() throw (logic_error)
   {
    if(!isEmpty())
      {
        if(head == cursor) 
         {
         cursor = cursor-> next; 
         delete head; 
         head = cursor;  
         }
        else
         { 
         ListNode *temp = cursor; 
         gotoPrior();
         cursor-> next = temp->next; 
          if(cursor->next == NULL)
            { 
             cursor = head; 
            }
          else 
            {
             cursor = cursor->next;
            }
          delete temp;
          temp = NULL;
         }
      }
 } 

// replace: 
// if not empty, then this function relpaces the data at cursorwith newDataItem
template <typename DataType> 
void List <DataType>:: replace(const DataType& newDataItem) throw (logic_error)
   {
    if(!isEmpty())
      {
       DataType temp  = cursor->dataItem; 
       cursor->dataItem = newDataItem; 
      }
   }

// clear: 
// if not empty then this function deallocates all memory node by node 
template <typename DataType>
void List <DataType>:: clear()
   {
     if(!isEmpty())
      {
       while(head->next != NULL)
          {
           cursor = head->next;
           delete head; 
           head = cursor; 
          }
      delete head;
      cursor = head = NULL;
      }
   }

// isEmpty:
// if head and cursor both equal NULL this function return true, else it returns false 
template <typename DataType> 
bool List<DataType>::isEmpty() const
   {
     if(cursor == NULL && head  == NULL)
       {
        return true; 
       }
    else 
       {
        return false;
       }
   }

// isFull:
// returns false always (due to dynamic memory allocation) 
template <typename DataType>
bool List<DataType>:: isFull() const
   {
    return false;
   }

// gotoBeginning:
// sets cursor equal to head 
template <typename DataType>
void List<DataType>:: gotoBeginning() throw (logic_error)
   {
    if(!isEmpty())
     {
      cursor = head;
     }
   }

// gotoEnd:
// if not empty, while the next node after cursor is not null, the function 
// advances down the list
template <typename DataType>
void List <DataType>::gotoEnd () throw (logic_error)
   {
    if(!isEmpty())
     {
      while(cursor->next != NULL)
         {
          cursor = cursor->next; 
         }
     }
   }

// gotoNext:
// if not empty and not at the end of the list, the functino advances 
// one position down the list
template <typename DataType>
bool List<DataType>::gotoNext() throw(logic_error)
   {
    if(!isEmpty())
      {
       if(cursor->next != NULL)
         {
          cursor = cursor->next;
          return true; 
         }
       else 
        {
         return false; 
        }
      }
   }

// gotoPrior:
// if not empty and if the list has more than one item, the function sets 
// cursor to head; and advances through until cursor->next = 
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
   {
    if(!isEmpty() && cursor != head)
     {
      ListNode *temp = cursor; 
      cursor = head; 
      while(cursor->next != temp)
        {
         cursor = cursor->next;
        }
      return true; 
     }
    return false; 
   } 
template <typename DataType>
DataType List<DataType>:: getCursor() const throw (logic_error)
   {
    if(!isEmpty())
     {
      return cursor->dataItem; 
     }
  }

template <typename DataType> 
void List<DataType>::moveToBeginning() throw (logic_error)
   {
     if(!isEmpty() && cursor != head)
       {
        ListNode *temp = cursor;
        gotoPrior(); 
        cursor->next = temp->next; 
        temp->next = head; 
        cursor = head = temp; 
       }
   }

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
   {
    if(!isFull())
      {
       ListNode *temp = cursor; 
       if(cursor != head)
        {
         gotoPrior(); 
         cursor->next = new ListNode(newDataItem,temp);
         gotoNext();
        }
       else
        {
         cursor = head = new ListNode(newDataItem,cursor);
        } 
      }
   }

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}

// ListNode Constructor: 

template <typename DataType>
List<DataType>::ListNode:: ListNode(const DataType& nodeData, ListNode* nextPtr)
   {
    dataItem = nodeData;
    next = nextPtr;
   }















