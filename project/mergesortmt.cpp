#include <iostream>
#include <iomanip>
#include <vector>
#include <atomic>
#include "./mergesortmt.h"



MergeSortMt::MergeSortMt( std::vector<std::atomic<int>> original )
{
    MergeSortMt( original, false );
}



/*****  CONSTRUCTOR  *****************************************************
 * Accepts an unsorted vector and sorts it.
 *  Unlike the Deitel & Deitel implementation, I assume that any vector
 *  passed into a MergeSortMt object is intended to be sorted, so it is
 *  sorted immediately.
*************************************************************************/
MergeSortMt::MergeSortMt( std::vector< std::atomic< int > > original, 
                          bool verbose_output = false ) :
    data { original }, verbose { verbose_output }
{
    sort_sub_vector( 0, data.size()-1 );
} // end MergeSortMt::MergeSortMt constructor



// Recursive function to sort sub-vectors
void MergeSortMt::sort_sub_vector( int low, int high )
{
    // Test against base case where size of vector is 1
    if ( ( high - low ) >= 1 ) {    // if NOT base case then
        
        // Calculate midpoint of the vector,
        //  and the next element to the right.
        int mid1 = ( low + high ) / 2;
        int mid2 = mid1 + 1;

        // If verbose, output the split step.
        if (verbose) {
            std::cout << "Split:   ";
            display_sub_vector( low, high );
            std::cout << std::endl << std::setw(9) << ' ';
            display_sub_vector( low, mid1 );
            std::cout << std::endl << std::setw(9) << ' ';
            display_sub_vector( mid2, high );
            std::cout << std::endl << std::endl;
        } // end if verbose

        // Split vector in half and sort each half recursively
        sort_sub_vector( low, mid1 );   // left half
        sort_sub_vector( mid2, high );  // right half

        // Merge the two sorted vectors
        merge( low, mid1, mid2, high );
    } // end if not base case
} // end MergeSortMt::sort_sub_vector



// Merge two sorted subvectors into one sorted subvector
void MergeSortMt::merge( int left, int middle1, int middle2, int right )
{
    int left_idx = left;
    int right_idx = middle2;
    int combined_idx = left;
    std::vector<int> combined( data.size() );

    // Output two subvectors before merging
    if (verbose) {
        std::cout << "Merge:   ";
        display_sub_vector( left, middle1 );
        std::cout << std::endl << std::setw(9) << ' ';
        display_sub_vector( middle2, right );
        std::cout << std::endl;
    } // end if verbose

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

    // output merged vector
    if ( verbose ) {
        std::cout << std::setw(9) << ' ';
        display_sub_vector( left, right );
        std::cout << std::endl << std::endl;
    } // end if verbose
} // end function merge



// Display elements in vector
void MergeSortMt::display_elements() const
{
    display_sub_vector( 0, data.size() - 1 );
} // end function display_elements

// Display certain values in vector
void MergeSortMt::display_sub_vector( int low, int high ) const
{
    // output spaces for alignment
    for ( int i = 0; i < low; i++ ) {
        std::cout << "   ";
    }

    // output elements left in vector
    for ( int i = low; i <= high; i++ )
    {
        std::cout << " " << data[ i ];
    }
} // end function display_sub_vector
