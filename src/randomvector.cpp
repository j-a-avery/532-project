#include "randomvector.h"
#include <ostream>


// Default Constructor
RandomIntVector::RandomIntVector( void )
{
    RandomIntVector(10);
}


// Constructor
RandomIntVector::RandomIntVector( int vect_size )
{
    data = std::vector<int>( vect_size );

    for ( int i; i < data.size(); i++ )
    {
        data[i] = dist(mt);
    }
}


// Return the vector data
std::vector<int> RandomIntVector::vector( void )
{
    return this->data;
}


// cout the vector
std::ostream &operator<<(std::ostream &out, RandomIntVector &rv )
{
    for ( auto element : rv.vector() )
    {
        out << element << ' ';
    }
}