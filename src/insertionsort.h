#include <vector>
#include "randomvector.h"
#include "sortingvector.h"

#ifndef SORTING_VECTOR
#define SORTING_VECTOR

class InsertionSort : SortingVector
{
    public:
        InsertionSort( int );
        virtual std::vector<int> sort();
        std::vector<int> contents() const;
    private:
        std::vector<int> data;
};
    
#endif