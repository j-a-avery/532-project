#include "./sortingvector.h"

// Constructor
SortingVector::SortingVector( int vector_size ) {
    data = RandomIntVector(vector_size).vector();
}

// Access a constant copy of the vector
std::vector<int> SortingVector::contents() const {
    return data;
}

// cout the vector
std::ostream &operator<<(std::ostream &out, const SortingVector &v )
{
    for ( auto element : v.contents )
    {
        out << element << ' ';
    }
}