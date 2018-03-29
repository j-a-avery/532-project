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
        int i = j - 1;

        while ( i > 0 && this->vector()[i] > key ) {
            this->vector()[ i + 1 ] = this->vector()[ i ];
            i -= 1;
        }
        this->vector()[ i + 1 ] = key;
    }

    return this->vector();
} // end InsertionSort::sort

std::vector< int > InsertionSort::vector( void ) const
{
    return this->vector();
}