#include <vector>
#include "randomvector.h"
#include "sortingvector.h"

#ifndef INSERTION_SORT
#define INSERTION_SORT

class InsertionSort : SortingVector
{
public:
    InsertionSort( int );
    std::vector< int>  sort();
    std::vector< int > vector() const;
};

std::ostream &operator<<(std::ostream &, const InsertionSort & );

#endif