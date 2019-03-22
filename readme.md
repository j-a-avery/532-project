# CSCI 532 Algorithm Design Project
## Comparision of Run-Times for Insertion Sort and Merge Sort

### Project Summary

This project implements a comparison of run-times for insertion sort and merge sort. The merge sort implementation is based on code in Deitel and Deitel, sorting C++ standard library vectors of integers. In addition, I have also reimplemented a version of the project in Google's Go programming language that uses goroutines to simultaneously process multiple sorts.

### Project Folder Contents

* `/docs`: Documents demonstrating the project
* `/src`: The source code for the project
  - `main.cpp`: the project source code in C++
  - `insertionsort.csv`: example insertion sort output from a prior run
  - `mergesort.csv`: example merge sort output from a prior run
  - `Demonstration-and-Analysis-Cpp.ipynb`: a Jupyter notebook that builds the project, automatically demonstrates its features, and analyzes the results
* `/go`: The alternate version of the project written in Go
  - `main.go`: the project source code in Go
  - `insertionsort.csv`: example insertion sort output from a prior run
  - `mergesort.csv`: example merge sort output from a prior run
  - `Demonstration-and-Analysis-Golang.ipynb`: a Jupyter notebook that builds the project, automatically demonstrates its features, and analyzes the results
  
### Compiling the Project
#### Compiling the C++ Version
##### In Linux

In a terminal, navigate to `532-project/src/cpp`. Compile the project with the following command:

      g++ -std="c++14" main.cpp -o main

##### In Windows
Click `Start` &#8594; `Programs` &#8594; `Visual Studio` &#8594; `Visual Studio Command Prompt`. In the Visual Studio Command Prompt, navigate to `532-project\src\cpp`. Compile the project with the following command:

      cl main.cpp

#### Compiling the Golang Version (recommended)
##### Linux Instructions (recommended)

In a terminal, navigate to `532-project/src/go`. Compile the project with the following command:

      go build -o gomain main.go

##### Windows Instructions

Open Windows PowerShell and navigate to `532-project\src\go`. Compile the project with the following command:

      go build -o gomain.exe main.go

#### Running the Demonstration Notebooks

I have provided Jupyter notebooks that demonstrate the operation of the project, for both the C++ and Golang versions. If your computer has the Python scientific computing stack installed (minimally numpy, pandas, matplotlib, and Jupyter), then the demonstrations may be run by entering `jupyter notebook` at the command line, navigating the the appropriate notebook, and clicking `Kernel` &#8594; `Restart & Run All`. (Note that this erases all output from previous runs and re-runs the project, which can take an hour or longer.) If you do not have the Python scientific libraries installed, I have exported sample runs of both in the C++ and Go versions html and pdf format in the docs folder.

### Command Line Options

A number of command line arguments are provided for various test runs. These work in both the C++ and Golang versions.
* `insertion-only`: prevents merge sort from being run
* `merge-only`: prevents insertion sort from being run
* `equal-batches`: instead of running each sort $\left\lfloor\frac{512}{p^2}\right\rfloor$ times, sorts are run in equal-sized batches.
* `limit-n`: only tests small arrays that can be tested quickly
* `demo-sorters`: demonstrates that each sorting routine produces arrays that are correctly sorted in nondecreasing order
* `no-time`: skips the main portion of the assignment, the obtaining of run-times
