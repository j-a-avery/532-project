#include <vector>
#include "randomvector.h"

class SortingVector
{
    public:
        SortingVector( int );
        virtual std::vector<int> sort();
        std::vector<int> contents() const;
    private:
        std::vector<int> data;
};