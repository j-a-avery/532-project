#include "randomvector.h"
#include <iostream>

using namespace std;

int main() {
    RandomIntVector r(13);

    cout << r << endl;

    for ( int i = 0; i < r.vector().size(); i++ ) {
        cout << i << ": " << r.vector()[i] << ' ';
    }
    cout << endl;
    

    return 0;
}