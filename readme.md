James Avery
CSCI 532 Project


0. PROJECT SUMMARY
===============================================================================
      This project implements problem #3, a comparison of run-times for
insertion sort and merge sort. The merge sort implementation is based on code
in Deitel and Deitel, sorting C++ standard library vectors of integers. In
addition, I have also reimplemented a version of the project in Google's Go
programming language that uses goroutines to simultaneously process multiple
sorts.


1. PROJECT FOLDER CONTENTS
===============================================================================
/docs - Contains documents demonstrating the project
/src - Contains the source code for the project
   /cpp - Contains the project as assigned in C++
      - main.cpp - the project source code 
      - insertionsort.csv - example insertion sort output from a prior run
      - mergesort.csv - example merge sort output from a prior run
      - Demonstration-and-Analysis-Cpp.ipynb - a Jupyter notebook that builds
            the project automatically and demonstrates its features
   /go - Contains an alternate version of the project written in Go
      - main.go - the project source code
      - insertionsort.csv - example insertion sort output from a prior run
      - mergesort.csv - example merge sort output from a prior run
      - Demonstration-and-Analysis-Golang.ipynb - a Jupyter notebook that builds
            the project automatically and demonstrates its features


2. COMPILING THE PROJECT
===============================================================================
2.1 Compiling the C++ Version

 - Linux Instructions
      In a terminal emulator, navigate to 532-project/src/cpp
      Compile the project with with the following command:

            g++ -std="c++14" main.cpp -o main

 - Windows Instructions
      Click Start -> Programs -> Visual Studio -> Visual Studio Command Prompt
      In the Visual Studio Command Prompt, navigate to 532-project\src\cpp
      Compile the project with the following command:

            cl main.cpp

2.2 Compiling the Golang Version (recommended)

 - Linux Instructions (recommended)
      In a terminal emulator, navigate to 532-project/src/go
      Compile the project with the following command:
      
            go build -o gomain main.go
      
 - Windows Instructions
      Open Windows PowerShell and navigate to 532-project\src\go
      Compile the project with the following command:

            go build -o gomain.exe main.go

2.3 Running the demonstration notebooks
 - I have provided Jupyter notebooks that demonstrate the operation of the
      project, for both the C++ and Golang versions. If your computer has the
      Python scientific computing stack installed (at least numpy, pandas, 
      matplotlib, and Jupyter), then the demonstrations may be run by entering
      "Jupyter notebook" at the command line, navigating to the appropriate
      notebook, and clicking Kernel -> Restart & Run All. (Note that this
      erases all output from previous runs and re-runs the project, which can
      take an hour or longer.) If you do not have the Python scientific
      libraries installed, I have exported sample runs of both the C++ and Go
      versions in html and pdf format in the docs folder.


3. COMMAND LINE OPTIONS
===============================================================================
I have provided a number of command line arguments for various test runs:
 - insertion-only: Prevents merge sort from being run
 - merge-only: Prevents insertion sort from being run
 - equal-batches: Instead of running each sort floor(512/(p*p)) times, sorts
      are run in equal-sized batches
 - limit-n: Only tests small arrays that can be tested quickly
 - demo-sorters: Demonstrates that each sorting routine produces arrays that
      are correctly sorted in nondecreasing order
 - no-time: Skips the main portion of the assignment, the obtaining of
      run-times.
