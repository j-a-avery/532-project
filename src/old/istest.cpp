#include "insertionsort.h"
#include <iostream>

using namespace std;

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec )
{
    for ( auto element : vec ) {
        out << element << ' ';
    }

    return out;
}

int main() {
    InsertionSort is(13);

    vector<int> v = is.sort();

    cout << v << endl;

    return 0;
}