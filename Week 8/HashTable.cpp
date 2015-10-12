#include "HashTable.h"
template <typename DataType, typename KeyType>
unsigned int HashTable<DataType, KeyType>::hash(const KeyType& str) const
   {
     unsigned int val = 0;
     for (int i = 0; i < str.length(); ++i) 
       {
	 val += str[i];
       }
     return val;
   }

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
   {
    tableSize = initTableSize;
    dataTable = new BSTree<DataType, KeyType>[initTableSize]; 
   }

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
   {
    *dataTable = new BSTree<DataType, KeyType>[other.tableSize]; 
    for(int i = 0; i<other.tableSize; i++) //might need changing from <
      {
       dataTable->BSTree(other.dataTable);
       dataTable++;
       other.dataTable++; 
      }
   }

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
   {
     if(this != &other) 
      {
       delete dataTable;  
       *dataTable = new BSTree<DataType, KeyType>[other.tableSize]; 
       for(int i = 0; i<other.tableSize; i++) //might need changing from <
        {
         dataTable->BSTree(other.dataTable);
         dataTable++;
         other.dataTable++; 
        }
       } 
     return this;
   }

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
   {
    for(int i = 0; i<tableSize; i++)
      {
       dataTable[i].clear();
      }
    delete dataTable; 
    dataTable = NULL; 
   }

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
   {
    KeyType key = newDataItem.getKey(); 
    unsigned int index = hash(key) % tableSize; 
    dataTable[index].insert(newDataItem); 
   }

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey) 
   {
    unsigned int index = hash(deleteKey) % tableSize;
    return dataTable[index].remove(deleteKey);
   }

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
   {
     unsigned int index = hash(searchKey) % tableSize;
     return dataTable[index].retrieve(searchKey, returnItem); 
   }


template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
   {
     if(!isEmpty())
      {
       for(int i = 0; i<tableSize; i++)
        {
         dataTable[i].clear();
        }
      }
   }

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
   {
     for(int i = 0; i<tableSize; i++)
       {
         if(dataTable[i].isEmpty() == false)
           return false; 
       }
     return true; 
   }

// show10.cpp: contains implementation of the HashTable showStructure function
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}




