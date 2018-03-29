#include <iostream>
#include <vector>
#include "randomvector.h"
#include "./insertionsort.h"


// Constructor
InsertionSort::InsertionSort( int vector_size ) 
    : SortingVector ( vector_size ) {}

//  Sort the vector
std::vector< int > InsertionSort::sort( void )
{
    for ( int j = 1; j < data.size(); j++ ) {
        int key = data[j];
        int i = j - 1;

        while ( i > 0 && data[i] > key ) {
            data[ i + 1 ] = data[ i ];
            i -= 1;
        }
        data[ i + 1 ] = key;
    }

    return data;
} // end InsertionSort::sort

// cout the vector
std::ostream &operator<<(std::ostream &out, const InsertionSort &v )
{
    for ( auto element : v.contents )
    {
        out << element << ' ';
    }
}