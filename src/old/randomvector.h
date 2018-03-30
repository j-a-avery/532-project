#include <vector>
#include <random>
#include <chrono>

#ifndef RANDOM_INT_VECTOR
#define RANDOM_INT_VECTOR

class RandomIntVector
{
private:
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<int> dist{1, 1024};

    std::vector<int> data;
    
public:
    RandomIntVector();
    RandomIntVector( int );
    std::vector<int> vector() const;
    void randomize();
};

// cout the vector
std::ostream& operator<<(std::ostream &, const RandomIntVector & );


#endif