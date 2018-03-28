/******************************************************************************
 * 
 * James A. Avery
 * 50189091
 * CSCI 532 Semester Project
 * 
 * Problem #3 (expanded)
 * Write a C/C++/Matlab/Java program to compute insertion sort and merge sort.
 * (You can use the code from the textbooks by Deitel and Deitel or from the
 *  web.) 
 * Obtain the run time of both routines. 
 * The input data should be an int array containing random element values 
 *  (between, say, 0 and 1023). 
 * Obtain run time T with 1D (input) array size of n=16, 256, 4096, 65536, 
 *  1048576 (which equal 2^p, where p = 4, 8, 12, 16, 20).
 * The run time for each n should be average with about floor(512/(p*p)) runs.
 * Each run (for a given n) should use a different random input.
 * Plot (with Excel, Matlab, or other available tools) the run time for both
 *  routines on one plot, with the x axis in p values, and y axis in log(T).
 * Label on the plot which curve is for insertion sort and which is for merge
 *  sort.
 * Submit C/C++ programs and plot, with instructions in readme.txt on how to 
 *  build and run the program. (Include the Dev-C++ or MS Studio or Java
 *  NetBeans project file.)
 * 
 *****************************************************************************/

/******************************************************************************
 * References
 * Timing code in C++11: 
 *      https://solarianprogrammer.com/2012/10/14/cpp-11-timing-code-performance/
 * Time durations, and "using":
 *      http://en.cppreference.com/w/cpp/chrono/duration
 * Random numbers in C++11:
 *      http://en.cppreference.com/w/cpp/numeric/random
 * ***************************************************************************/

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <typeinfo>
//#include "./util.h"
#include "./mergesort/mergesort.h"

int main()
{
    // Set up the distribution of random integers for the vectors
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<> udist(0, 1024);

    // Define p values
    // For each i, each vector will hold 2^p[i] elements,
    //  and be tested for floor(512/(p[i]*p[i])) trials
    std::vector<int> ps {
        4, 8, 12, 16, 20
    };

    for ( int &p : ps ) {
        int n = std::pow( 2, p );

        int num_trials = std::floor( 512 / (p * p) );

        std::cout << std::endl << num_trials << " trials of " << n << "-element vectors:" << std::endl;

        for (int trial = 0; trial < num_trials; trial++ ) {
            std::vector<int> arr(n);
            for ( int i = 0; i < n; i++ ) {
                arr[i] = udist(eng);
            }

            auto begin = std::chrono::steady_clock::now();
            // Placeholder for the actual sorts
            //std::sort( arr.begin(), arr.end() );
            MergeSort( arr, true );
            auto end = std::chrono::steady_clock::now();

            auto diff = end - begin;
            std::cout << "Elapsed time: ";
            if ( std::chrono::duration_cast<std::chrono::hours>(diff).count()
                        >= std::chrono::hours(1).count() ) {
                std::cout 
                    << std::chrono::duration_cast<std::chrono::hours>(diff).count() 
                    << " hrs ";
                diff %= std::chrono::hours(1);
            }
            if ( std::chrono::duration_cast<std::chrono::minutes>(diff).count()
                        >= std::chrono::minutes(1).count() ) {
                std::cout
                    << std::chrono::duration_cast<std::chrono::minutes>(diff).count()
                    << " mins ";
                diff %= std::chrono::minutes(1);
            }
            if ( std::chrono::duration_cast<std::chrono::seconds>(diff).count()
                        >= std::chrono::seconds(1).count() ) {
                std::cout
                    << std::chrono::duration_cast<std::chrono::seconds>(diff).count()
                    << " s ";
                diff %= std::chrono::seconds(1);
            }
            if ( std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() 
                        >= std::chrono::milliseconds(1).count() ) {
                std::cout
                    << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
                    << " ms ";
                diff %= std::chrono::milliseconds(1);
            }
            if ( std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
                        >= std::chrono::microseconds(1).count() ) {
                std::cout
                    << std::chrono::duration_cast<std::chrono::microseconds>(diff).count()
                    << " us ";
                diff %= std::chrono::microseconds(1);
            }
            if ( std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()
                        >= std::chrono::nanoseconds(1).count() ) {
                std::cout
                    << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count()
                    << " ns ";
            }
            std::cout << std::endl;

        }
    }
    return 0;

}