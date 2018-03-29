#include <vector>
#include "randomvector.h"
#include "sortingvector.h"

class InsertionSort : SortingVector
{
    public:
        InsertionSort( int );
        virtual std::vector<int> sort();
        std::vector<int> contents() const;
    private:
        std::vector<int> data;
};