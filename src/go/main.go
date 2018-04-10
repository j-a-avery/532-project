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

/**  References  **************************************************************
 * 
 *  Tour of Go
 *		https://tour.golang.org/
 *	Merge Sort in Go
 * 		https://austingwalters.com/merge-sort-in-go-golang/
 * 
******************************************************************************/

package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
	"os"
	"strings"
	"unicode"
	"encoding/csv"
	"strconv"
	"sync"
)


/* 
By default, the program runs a decreasing number of trials, such that for an
    array of size n=2^p, the number of trials is floor(512/(p*p)), (per the
    project instructions).
I would like a more scientific approach (i.e. a more) uniform number of 
    trials), so I have included a command line option to run the same number of
    trials for each vector size. On my computer, a slice of n = 2^20 = 1048567
	can be sorted with insertion sort in around four minutes, and the entire
	project, with 24-element slices, can run in under an hour.
*/
const StandardBatchSize int = 24

/*
If, instead, the program is being run as assigned, then calculate the batch
	size based on the formula floor(512/p^2)
This function is defined inline in the C++ version; my understanding is that Go
	lacks an "inline" keyword, but the Go compiler would likely build this as
	an inline function.
*/
func assignedBatchSize( p int ) int {
	return int( math.Floor( 512 / ( float64(p) * float64(p) ) ) )
}


/*
Arrays of size n = 20 take several minutes to run. Limiting the length of
	arrays to those that can be sorted quickly speeds testing of other issues.
*/
const MaxN int = 1000000

/*
A global WaitGroup to hold all the various tests
*/
var wg sync.WaitGroup



// Struct to allow passing a function along with its name
type NamedFunction struct {
	name string
	function func([]int) []int
}



func main() {
	// Put the command line arguments into an array for easier access
	args := os.Args

	// Flags to determine run-time behavior
	// Default values are the problem as assigned
	// Changing these through command line options results in shorter or more interesting tests
	runInsertionSort := true
	runMergeSort := true
	limitN := false
	demo := false
	time := true;

    // p determines both the array size and the number of tests per array
    // Arrays of size 2^p will be tested either floor(512/(p*p)) times or 32 times
	// Having a vector of ps will make things easier later
	ps := []int{ 4, 8, 12, 16, 20 }

	// Determine the sizes of the test runs
	// If false, then each vector of size 2^p will be tested floor(152/(p*p)) times
	// If true, each vector will be tested the same number of times (set above)
	equalBatchSizes := false


	// Adjust run-time flags according to command line arguments
	for _, flag := range args {
		if flag == "merge-only" { runInsertionSort = false; }
		if flag == "insertion-only" { runMergeSort = false; }
		if flag == "equal-batches" { equalBatchSizes = true; }
		if flag == "limit-n" { limitN = true; }
		if flag == "demo-sorters" { demo = true; }
		if flag == "no-time" { time = false; }
	}

	// Create a slice of functions to test, based on command line options
	//	Default is both Insertion Sort and Merge Sort,
	//	but these can be stopped by command line options above
	var sorters []NamedFunction
	if runInsertionSort {
		sorters = append(sorters, NamedFunction{"Insertion Sort", InsertionSort})
	}
	if runMergeSort {
		sorters = append(sorters, NamedFunction{"Merge Sort", MergeSort})
	}

	// Demonstrate that the sort functions sort correctly (disabled by default)
	if demo {
		for _, sorter := range sorters {
			demoSorter(sorter)
		}
	}

	// The heart of the project
	// Time the run-time of each sort function as assigned (enabled by default)
	if time {
		for _, sorter := range sorters {
			testSorter(sorter, ps, equalBatchSizes, limitN)
		}
	}

	return
}



// Sort a slice in place using insertion sort and return the slice
func InsertionSort(v []int) []int {
	// Loop through the elements of the array
	for j := 1; j < len(v); j++ {
		key := v[j]
		i := j - 1;

		for i >= 0 && v[i] > key {
			v[i + 1] = v[i]
			i -= 1;
		}

		v[i+1] = key
	}

	return v
}



// Sort a slice in place using Merge Sort, and return the slice
//	From https://austingwalters.com/merge-sort-in-go-golang/
func MergeSort(slice []int) []int {
	if len(slice) < 2 {
		return slice;
	}

	mid := (len(slice)) / 2
	return Merge(MergeSort(slice[ : mid]), MergeSort(slice[mid : ]))
}



// Merge - merges left and right slices into newly created slice
func Merge(left, right []int) []int {
	size := len(left) + len(right)
	i, j := 0, 0

	slice := make([]int, size, size)

	for k := 0; k < size; k++ {
		if i > len(left) - 1 && j <= len(right) - 1 {
			slice[k] = right[j]
			j++
		} else if j > len(right) - 1 && i <= len(left) - 1 {
			slice[k] = left[i]
			i++
		} else if left[i] < right[j] {
			slice[k] = left[i]
			i++
		} else {
			slice[k] = right[j]
			j++
		}
	}

	return slice
}



// Fill a vector in place with random integers
func RandomFill(v []int) {
	for i := 0; i < len(v); i++ {
		v[i] = rand.Intn(1024)
	}
}



/* Given a NamedFunction, a slice of values for p, and booleans to determine
	whether or not to process equal batch sizes and whether or not to limit
	the size of the slice to slices that can be sorted quickly, calculate the
	execution time for each of the sort algorithms.
*/
func testSorter(f NamedFunction, ps []int, equalBatchSizes, limitN bool) {
	// Create a file to output the results
	fileName := strings.ToLower(strings.Map(
		func(r rune) rune {
			if unicode.IsSpace(r) {
				return -1
			}
			return r
		}, f.name)) + ".csv"
	
	file, err := os.Create(fileName)
	if err != nil {
		panic(err)
	}

	defer file.Close()	// Close the file when done

	writer := csv.NewWriter(file)
	fmt.Println("\n", f.name)

	// Iterate through each of the p values (p = 4, 8, 12, ...)
	for _, p := range ps {
		// Vector size
		n := int(math.Pow(2, float64(p)))

        // If n is being limited to certain fast-running small values,
        //  then skip this iteration
		if limitN && n > MaxN { continue }

		// Calculate batch size
		batchSize := StandardBatchSize
		if !equalBatchSizes { batchSize = assignedBatchSize( p ) }

		// First column of the output is the size of the slice
		fmt.Printf("\n%v:\t", n)

		var results []string
		results = append(results, strconv.Itoa(n))

		ch := make(chan uint64, batchSize)

		for trial := 0; trial < batchSize; trial++ {
			v := make([]int, n, n)
			RandomFill(v)

			wg.Add(1)
			go TimeRun(f.function, ch, v)
		}
		
		wg.Wait()
		close(ch)
		for range ch {
			duration := <-ch
			results = append(results, strconv.FormatUint(duration, 10))
		}

		fmt.Println()
		err = writer.Write(results)
		if err != nil {
			panic(err)
		}

		writer.Flush()
	}
}



// Find the length of time it takes to run a sort,
//	and push the time (in nanoseconds) to the channel, c
func TimeRun(f func([]int) []int, c chan uint64, v []int) {
	defer wg.Done()
	start := time.Now()
	f(v)
	duration := uint64(time.Now().Sub(start).Nanoseconds())
	fmt.Printf("%v ", duration)	
	c <- duration
}



// Demonstrate that the sorter actually does sort a slice properly
func demoSorter(sorter NamedFunction) {
	fmt.Printf("\n=====  Demonstrating %v  =====\n", sorter.name)
	for i := 0; i < 10; i++ {
		v := make([]int, 10, 10)
		RandomFill(v)
		fmt.Printf("\nBefore: %v\n", v)
		v = sorter.function(v)
		fmt.Printf("After:  %v\n", v)
	}
}