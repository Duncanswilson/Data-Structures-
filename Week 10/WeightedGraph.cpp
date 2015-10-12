#include "WeightedGraph.h" 

WeightedGraph::WeightedGraph(int maxNumber)
   {
    vertexList = new Vertex[maxNumber]; 
    adjMatrix = new int[maxNumber*maxNumber]; 
    for(int i = 0; i < maxNumber*maxNumber; i++)
     {
      adjMatrix[i] = INFINITE_EDGE_WT;
     }
    size = 0; 
    maxSize = maxNumber; 
   }

WeightedGraph::WeightedGraph(const WeightedGraph& other)
   {
    vertexList = new Vertex[other.maxSize]; 
    adjMatrix = new int[other.maxSize*other.maxSize]; 
    size = other.size; 
    maxSize = other.maxSize; 
    for(int i = 0; i<size; i++)
      {
       vertexList[i] = other.vertexList[i]; 
      }          
    for(int j = 0; j < maxSize*maxSize; j++)
      {
       adjMatrix[j] = other.adjMatrix[j]; 
      }          
   }
 

WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
   {
    if(this != &other) 
     {
      delete vertexList; 
      delete adjMatrix; 
      vertexList = new Vertex[other.maxSize]; 
      adjMatrix = new int[other.maxSize*other.maxSize]; 
      size = other.size; 
      maxSize = other.maxSize; 
      for(int i = 0; i<size; i++)
        {
         vertexList[i] = other.vertexList[i]; 
        }          
     for(int j = 0; j < maxSize*maxSize; j++)
       {
        adjMatrix[j] = other.adjMatrix[j]; 
       }                
     }
    return *this; 
   }
WeightedGraph::~WeightedGraph()
   {
    delete[] vertexList; 
    delete[] adjMatrix; 
    delete[] pathMatrix; 
    vertexList = NULL;
    pathMatrix = adjMatrix = NULL; 
   }
void WeightedGraph::insertVertex ( const Vertex& newVertex ) throw ( logic_error )
   {
    if(isFull())
       throw logic_error ("Vertex list is full"); 
    else
    {
     vertexList[size] = newVertex;
     size++;
     }
   }

void WeightedGraph::insertEdge( const string& v1, const string& v2, int wt ) throw ( logic_error )
   {
    int k;
    int j = k = -1; 
    for(int i = 0; i < size; i++)
      {
        if(vertexList[i].getLabel() == v1)
          j = i; 
        if(vertexList[i].getLabel() == v2)
          k = i;           
      }
    if( j == -1 || k == -1)
       throw logic_error ("One vertex or both vertex not found in the vertex list");  
//   cout <<"this is K: " <<k <<endl; 
//   cin >> k; 
     setEdge(j,k,wt);
     setEdge(k, j, wt);   

   }

void WeightedGraph::setEdge(int j, int k, int wt)
   {
     int i = j *maxSize + k; //maybe k*maxSize + j 
     adjMatrix[i] = wt; 
   }
bool WeightedGraph::retrieveVertex (const string& v, Vertex& vData ) const
   {
    int j = -1; 
    for(int i = 0; i < size; i++)
      {
        if(vertexList[i].getLabel() == v)
          j = i;       
      }
    if(j == -1)
     return false; 
    else 
     {
      vData = vertexList[j]; 
      return true; 
     }
   }
bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error )
   {
    int k;
    int j = k = -1; 
    for(int i = 0; i < size; i++)
      {
        if(vertexList[i].getLabel() == v1)
          j = i; 
        if(vertexList[i].getLabel() == v2)
          k = i;           
      }
    if( j == -1 || k == -1)
       throw logic_error ("One vertex or both vertex not found in the vertex list"); 
    wt = (getEdge(j,k));
    if(wt != INFINITE_EDGE_WT)
     return true; 
   else {
      return false;
    }        
   }
int WeightedGraph::getEdge(int row, int col) const
   {
     int index = row * maxSize + col;
     return adjMatrix[index]; 
   }
void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error )
   {
    int j = -1;  
    for(int i = 0; i < size; i++)
      {
        if(vertexList[i].getLabel() == v)
          j = i; 
      }
    if( j == -1)
       throw logic_error ("Vertex is not found in the vertex list"); 
    for(int k = j; k < size; k++)
      {
       vertexList[k] = vertexList[k+1];
      }
    // row iterator 
     int t = j;
    for(int a = j; a< maxSize; a++)
     {
      for( int b = j; b <maxSize; b++)
        {
         adjMatrix[t] = adjMatrix[t+maxSize];
         t++;
        }
         t= a*maxSize; 
     }
    //col iterator 
     t = j; 
     for(int c = j; c < maxSize;)
       {
        for(int d = j; d<maxSize; d++)
          { 
           if(t == ((maxSize*j) +j)) 
            { 
            adjMatrix[t] = INFINITE_EDGE_WT; 
           }
           else
           {     
             adjMatrix[t] = adjMatrix[t+1];
           }
           t++;
          }
        c++;
        t = c*maxSize;
       }
    size--;  
   }
void WeightedGraph::removeEdge ( const string& v1, const string& v2 ) throw ( logic_error )
   {
    int k; 
    int j = k = -1;
    for(int i = 0; i < size; i++)
      {
       if(vertexList[i].getLabel() == v1)
         j = i; 
       if(vertexList[i].getLabel() == v2)
         k = i; 
      } 
    if(j == -1 || k == -1)
      throw logic_error ("Vertex not in list!");   
    else {
      int index = j*maxSize + k;  
      adjMatrix[index] = INFINITE_EDGE_WT;
      index =  k*maxSize + j;  
      adjMatrix[index] = INFINITE_EDGE_WT;
    }
   }
void WeightedGraph::clear ()  
   {
    size = 0;
    for(int i = 0; i <maxSize*maxSize; i++) 
      {
       adjMatrix[i] = INFINITE_EDGE_WT; 
      } 
   }
bool WeightedGraph::isEmpty() const
   {
    return(size == 0); 
   }
bool WeightedGraph::isFull() const 
   {
    return(size == maxSize); 
   }
void WeightedGraph:: showStructure () const
// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.
{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
#if LAB12_TEST2
		<< '\t' <<vertexList[row].getColor()
#endif
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}
void WeightedGraph::showShortestPaths() 
  {
    pathMatrix = new int [maxSize*maxSize];
    int j = 0, inc = 1;  
    for(int i = 0; i < maxSize*maxSize; i++)
      {
       pathMatrix[i] = adjMatrix[i];   
       if(i == j) 
        { 
         pathMatrix[i] = 0; 
         j = inc*maxSize + inc;
         inc++;
        }
      }
    for(int m = 0; m <size; m++)
     { 
       for(int j = 0; j <size; j++)
         {    
	  for(int k = 0; k <size; k++)
             {
              int indexOne = getEdge(j,m); 
              int indexTwo = getEdge(m,k); 
              int oldPath = getPath(j,k);
              int newPath = indexOne+indexTwo;
               if(j == 0 && k ==3)
                 cout <<"The value of the m, j , k is: " <<m <<", "<<j <<", "<<k <<endl
                       << "The value of the summed path is: " <<newPath <<endl; 
              if(indexOne != INFINITE_EDGE_WT &&
                 indexTwo != INFINITE_EDGE_WT && 
                 newPath < oldPath)
               {
                setPath(j,k,newPath); 
               }
	     }
         }
     }
    showStructurePM ();
   }
int WeightedGraph::getPath ( int row, int col ) const
   {
     return(pathMatrix[row*maxSize+col]);
   }
void WeightedGraph::setPath(int row,int col, int wt)
   {
    int index = row*maxSize+col;
    pathMatrix[index] = wt; 
   }
bool WeightedGraph::hasProperColoring() const  
   {
      int index, indexTwo; 
      for(int i = 0; i < size; i++)
       {
        for(int j = i*maxSize; j < i*maxSize; j++) 
          {
           if(adjMatrix[j] != INFINITE_EDGE_WT)
            {
             int colIndex = j-(maxSize*i);
             if(vertexList[i].getColor() != 
                vertexList[colIndex].getColor())
               return false;  
            }
          } 
       }
     return true;
   } 
int WeightedGraph::getIndex(const string& v) const 
   {
     for(int i = 0; i < size; i++)
      {
        if(vertexList[i].getLabel() == v)
         return(i);       
      }
   }
bool WeightedGraph::areAllEven () const
   {
     int j, index;
     int counter =0; 
     for(int i = 0; i < size; i++) 
      {
        index = getIndex(vertexList[i].getLabel()); 
        for(int j = index; j < maxSize; j++)
          {
           if (adjMatrix[j] != INFINITE_EDGE_WT)
              counter++; 
          }
         if(counter % 2 == 1)
           return false; 
      }  
     return true; 
   }

void WeightedGraph:: showStructurePM () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
       cout << endl << "Path matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getPath(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
}

