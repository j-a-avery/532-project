#include <vector>
#include <random>
#include <chrono>

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
    std::vector<int> vector();
};