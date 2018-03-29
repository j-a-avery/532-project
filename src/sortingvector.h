#include <vector>
#include "randomvector.h"

#ifndef SORTING_VECTOR
#define SORTING_VECTOR

class SortingVector
{
public:
    SortingVector( int );
    virtual std::vector<int> sort() = 0;
    std::vector<int> vector() const;
private:
    std::vector<int> data;
};
    
#endif