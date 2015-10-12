template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::writeLessThan(const KeyType& searchKey) const
 {
  wLTHelper(root, searchKey); 
 }

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::wLTHelper(BSTreeNode* current, const KeyType& searchKey)const 
 {
  if(current == NULL)
   {
     cout <<endl;
     return; 
   }
  else{
     if(current->dataItem.getKey() >= searchKey)
      {wLTHelper(current->left, searchKey);} 
     else if (current->dataItem.getKey() <= searchKey)
      {
       if(current->left == NULL && current->right == NULL) 
       { cout << current-> dataItem.getKey() <<" ";} 
       else{
       wHelper(current->left); 
       cout << current->dataItem.getKey() <<" "; 
       wHelper(current->right); 

       } 
     }
   }
 }

