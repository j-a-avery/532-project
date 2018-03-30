#include <iostream>
#include <vector>
#include "randomvector.h"
#include "insertionsort.h"


// Constructor
InsertionSort::InsertionSort( int vector_size ) 
    : SortingVector ( vector_size ) {}

//  Sort the vector
std::vector< int > InsertionSort::sort( void )
{
    for ( int j = 1; j < this->vector().size(); j++ ) {
        int key = this->vector()[j];
        std::cout << "vector[" << j << "] = " << key << std::endl;

        int i = j - 1;
        std::cout << "i = " << i << std::endl;

        while ( i > 0 && this->vector()[i] > key ) {
            this->vector()[ i + 1 ] = this->vector()[ i ];
            i -= 1;
        }
        this->vector()[ i + 1 ] = key;

        for ( int z = 0; z <= this->vector().size(); z++ ) {
            std::cout << this->vector()[z] << ' ';
        }
        std::cout << std::endl;
    }

    return this->vector();
} // end InsertionSort::sort