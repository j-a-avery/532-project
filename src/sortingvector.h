#include <vector>
#include "randomvector.h"

#ifndef SORTING_VECTOR
#define SORTING_VECTOR

class SortingVector
{
    public:
        SortingVector( int );
        virtual std::vector<int> sort();
        std::vector<int> contents() const;
    private:
        std::vector<int> data;
};
    
#endif