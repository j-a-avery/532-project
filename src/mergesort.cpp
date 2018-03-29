#include <iostream>
#include <vector>
#include "randomvector.h"
#include "mergesort.h"


// Constructor
MergeSort::MergeSort( int vector_size ) 
    : SortingVector ( vector_size ) {}

//  Sort the vector
std::vector< int > MergeSort::sort( void )
{
    sort_sub_vector( 0, data.size()-1 );

    return data;
} // end MergeSort::sort


// Recursive function to sort sub-vectors
void MergeSort::sort_sub_vector( int low, int high )
{
    // Test against base case where size of vector is 1
    if ( ( high - low ) >= 1 ) {    // if NOT base case then
        
        // Calculate midpoint of the vector,
        //  and the next element to the right.
        int mid1 = ( low + high ) / 2;
        int mid2 = mid1 + 1;

        // Split vector in half and sort each half recursively
        sort_sub_vector( low, mid1 );   // left half
        sort_sub_vector( mid2, high );  // right half

        // Merge the two sorted vectors
        merge( low, mid1, mid2, high );
    } // end if not base case
} // end MergeSort::sort_sub_vector


// Merge two sorted subvectors into one sorted subvector
void MergeSort::merge( int left, int middle1, int middle2, int right )
{
    int left_idx = left;
    int right_idx = middle2;
    int combined_idx = left;
    std::vector<int> combined( data.size() );

    // Merge vectors until reaching end of either
    while ( left_idx <= middle1 && right_idx <= right ) {
        // place smaller of two current elements into result
        //  and move to next space in vector
        if ( data[ left_idx ] <= data[ right_idx ] ) {
            combined[ combined_idx++ ] = data[ left_idx++ ];
        } else {
            combined[ combined_idx++ ] = data[ right_idx++ ];
        } // end if
    } // end while

    if ( left_idx == middle2 ) { // if at end of left vector
        while ( right_idx <= right ) {   // copy rest of right vector
            combined[ combined_idx++ ] = data[ right_idx++ ];
        }
    } else {                  // if at end of right vector
        while ( left_idx <= middle1 ) {    // copy rest of left vector
            combined[ combined_idx++ ] = data[ left_idx++ ];
        }
    } // end if

    // copy values back into original vector
    for ( int i = left; i <= right; i++ ) {
        data[ i ] = combined[ i ];
    }
} // end function merge


// cout the vector
std::ostream &operator<<(std::ostream &out, const MergeSort &v )
{
    for ( auto element : v.contents )
    {
        out << element << ' ';
    }
}