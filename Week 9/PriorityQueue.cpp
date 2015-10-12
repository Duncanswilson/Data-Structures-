#include "PriorityQueue.h" 
template < typename DataType, typename KeyType, typename Comparator >
PriorityQueue<DataType,KeyType,Comparator>::PriorityQueue(int maxNum)
   :Heap<DataType,KeyType,Comparator>::Heap(maxNum){}

template < typename DataType, typename KeyType, typename Comparator >
void PriorityQueue<DataType,KeyType,Comparator>::enqueue(const DataType& newDataItem)
  {
    Heap<DataType,KeyType,Comparator>::insert(newDataItem);  
  }
template < typename DataType, typename KeyType, typename Comparator >
DataType PriorityQueue<DataType,KeyType,Comparator>::dequeue()
  {
   return Heap<DataType,KeyType,Comparator>::remove(); 
  }
