//--------------------------------------------------------------------
//
//  Laboratory 12                                         show12.cpp
//
//  Adjacency matrix implementations of the showStructure operation
//  for the Weighted Graph ADT
//
//--------------------------------------------------------------------

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
}
