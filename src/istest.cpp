#include "insertionsort.h"
#include <iostream>

using namespace std;


int main() {
    InsertionSort is(13);

    for ( int i; i < is.vector().size(); i++ )
    {
        cout << is.vector()[ i ] << endl;
    }

    return 0;
}