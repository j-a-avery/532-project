#include <vector>
#include <random>

static std::random_device rd;
static std::default_random_engine eng(rd());
static std::uniform_int_distribution<> udist(0, 1024);

class RandomIntVector
{
    std::vector<int> data;
public:
    RandomIntVector();
    RandomIntVector( int );
    std::vector<int> vector();
};