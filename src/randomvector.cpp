#include "randomvector.h"
#include <ostream>


// Default Constructor
RandomIntVector::RandomIntVector( void )
{
    data = std::vector<int>(10);
    randomize();
}


// Constructor
RandomIntVector::RandomIntVector( int vect_size )
{
    data = std::vector<int>( vect_size );
    randomize();
}


// Set vector items to random values
void RandomIntVector::randomize( void )
{
    for (int i = 0; i < data.size(); i++ ) {
        data[i] = dist(mt);
    }
}


// Return the vector data
std::vector<int> RandomIntVector::vector( void ) const
{
    return this->data;
}



std::ostream& operator<<(std::ostream &out, const RandomIntVector &rv )
{
    for ( int i = 0; i < rv.vector().size(); i++ )
    {
        out << rv.vector()[ i ] << ' ';
    }

    return out;
}