#include <vector>
#include <iostream>
#include "./src/sortingvector.h"
#include "./src/insertionsort.h"
#include "./src/randomvector.h"

int main() {
    InsertionSort iv{10};
    for ( int i : iv.contents ) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    iv.sort();
    
    return 0;
}