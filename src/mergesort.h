#include <vector>
#include "sortingvector.h"
#include "randomvector.h"

#ifndef MERGE_SORT
#define MERGE_SORT

class MergeSort : SortingVector
{
    public:
        MergeSort( int vector_size );
        virtual std::vector< int > sort();
        std::vector< int > contents();
    private:
        std::vector<int> data;
        void sort_sub_vector( int, int );
        void merge( int, int, int, int );
};
    
#endif