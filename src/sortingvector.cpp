#include "./sortingvector.h"

// Constructor
SortingVector::SortingVector( int vector_size ) {
    data = RandomIntVector(vector_size).vector();
}

// Access a constant copy of the vector
std::vector<int> SortingVector::vector() const {
    return data;
}