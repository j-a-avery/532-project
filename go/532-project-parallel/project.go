package main

// From https://austingwalters.com/merge-sort-in-go-golang/

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



var StandardBatchSize int = 24
const MaxN int = 1000000
var wg sync.WaitGroup


type NamedFunction struct {
	name string
	function func([]int) []int
}


func TimeRun(f func([]int) []int, c chan int64, v []int) {
	defer wg.Done()
	start := time.Now()
	f(v)
	duration := time.Now().Sub(start)
	fmt.Printf("%v ", duration)	
	c <- duration.Nanoseconds()
}



// InsertionSort - runs insertion sort algorithm on a slice
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

// MergeSort - runs MergeSort algorithm on a single slice
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



func RandomFill(v []int) {
	for i := 0; i < len(v); i++ {
		v[i] = rand.Intn(1024)
	}
}



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

	for _, p := range ps {
		n := int(math.Pow(2, float64(p)))

		if limitN && n > MaxN {
			continue
		}

		var batchSize int

		if equalBatchSizes {
			batchSize = StandardBatchSize
		} else {
			batchSize = int(math.Floor(512 / (float64(p)*float64(p))))
		}

		fmt.Printf("\n%v:\n", n)

		var results []string
		results = append(results, strconv.Itoa(n))

		ch := make(chan int64, batchSize)

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
			results = append(results, strconv.FormatInt(duration, 10))
		}

		fmt.Println()
		err = writer.Write(results)
		if err != nil {
			panic(err)
		}

		writer.Flush()
	}
}




func main() {
	// Put the command line arguments into a vector for easier access
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
		if flag == "-insertion" { runInsertionSort = false; }
		if flag == "-merge" { runMergeSort = false; }
		if flag == "equal-batches" { equalBatchSizes = true; }
		if flag == "limit-n" { limitN = true; }
		if flag == "demo" { demo = true; }
		if flag == "-time" { time = false; }
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

	// Time the sort functions, as assigned (enabled by default)
	if time {
		for _, sorter := range sorters {
			testSorter(sorter, ps, equalBatchSizes, limitN)
		}
	}

	return
}



func head(v []int) {
	var length int

	if (len(v) > 10) {
		length = 10
	} else {
		length = len(v)
	}

	for i := 0; i < length; i++ {
		fmt.Printf("%v ", v[i])
	}
	fmt.Println()
}



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