#include <vector>
#include "randomvector.h"
#include "sortingvector.h"

#ifndef INSERTION_SORT
#define INSERTION_SORT

class InsertionSort : SortingVector
{
public:
    InsertionSort( int );
    virtual std::vector<int> sort();
    std::vector<int> contents() const;
private:
    std::vector<int> data;
};

std::ostream &operator<<(std::ostream &, const InsertionSort & );

#endif