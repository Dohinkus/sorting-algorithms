#include "C++SortingAlgorithms.h"
#include <chrono>
#include <iostream>
#include <iomanip>

// Benchmarks each algorithm's performance
void benchmarkSortingAlgorithms(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE);

// Manipulates an array's elements to be in order, reverse order, or random order
void setAscendingArray(int arr[], int size);
void setDescendingArray(int arr[], int size);
void randomizeArray(int arr[], int size);

// Sets all values to 0 in sortResults[]
void resetSortResults(sortResults sortResults[], const int SORT_RESULTS_SIZE);

// Prints results of the benchmark's tests
void printResults(sortResults sortResults[]);
// Prints the best performing sort for each metric
void printResultsAnalysis(sortResults sortResults[], const int SORT_RESULTS_SIZE);

// Converts sort int into a string for printing
std::string sortTypeToString(int sort);

// Sets fewestComparisonSort, fewestMovementsSort, and fastestSort to the correct sort based on sortResults[]
void compareComparisons(int& fewestComparisonSort, sortResults sortResults[], const int SORT_RESULTS_SIZE);
void compareMovements(int& fewestMovementsSort, sortResults sortResults[], const int SORT_RESULTS_SIZE);
void compareDuration(int& fastestSort, sortResults sortResults[], const int SORT_RESULTS_SIZE);

// Tests each sorting algorithm on an in order array
void testInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
// Tests each sorting algorithm on a reverse order array
void testReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
// Tests each sorting algorithm on a random order array
void testRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);

// Each algorithm's testing function and respective array order:
void testInsertionSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testQuickSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testMergeSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testHeapSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);

void testInsertionSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testQuickSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testMergeSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testHeapSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);

void testInsertionSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testQuickSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testMergeSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);
void testHeapSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS);

// An enumeration for each sorting algorithm used in this program
enum sortType {
    insertion,
    quick,
    merge,
    heap
};

// Creates a 50k element array, creates an array for algorithm performance metrics to be stored, and runs the benchmark to test, analyze, and print results
int main() {
    // Holds the performance metrics of the sorting algorithms
    constexpr int SORT_RESULTS_SIZE = 4;
    sortResults sortResults[SORT_RESULTS_SIZE];
    // Sets all values to 0
    resetSortResults(sortResults, SORT_RESULTS_SIZE);

    // Array for testing the sorting algorithms
    constexpr int TEST_ARRAY_SIZE = 50000;
    int testArray[TEST_ARRAY_SIZE];
    // Populates the array with values
    setAscendingArray(testArray, TEST_ARRAY_SIZE);

    benchmarkSortingAlgorithms(testArray, TEST_ARRAY_SIZE, sortResults, SORT_RESULTS_SIZE);
}

void benchmarkSortingAlgorithms(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    // Test iterations affects how many times a test is re-run for the averaged results to be more accurate
    constexpr int TEST_ITERATIONS = 3;

    std::cout << "The following values are the average results over " << TEST_ITERATIONS << " simulation(s)\n\n";
    std::cout << "Experimental Results - Input List: Array Size = " << TEST_ARRAY_SIZE << "\n\n\n";

    // Print In Order test results
    testInOrder(testArray, TEST_ARRAY_SIZE, sortResults, SORT_RESULTS_SIZE, TEST_ITERATIONS);
    std::cout << "IN ORDER (ASCENDING):\n\n";
    printResults(sortResults);
    printResultsAnalysis(sortResults, SORT_RESULTS_SIZE);

    resetSortResults(sortResults, SORT_RESULTS_SIZE);

    // Print Reverse Order test results
    testReverseOrder(testArray, TEST_ARRAY_SIZE, sortResults, SORT_RESULTS_SIZE, TEST_ITERATIONS);
    std::cout << "\nREVERSE ORDER (DESCENDING):\n\n";
    printResults(sortResults);
    printResultsAnalysis(sortResults, SORT_RESULTS_SIZE);

    resetSortResults(sortResults, SORT_RESULTS_SIZE);

    // Print Random Order test results
    testRandomOrder(testArray, TEST_ARRAY_SIZE, sortResults, SORT_RESULTS_SIZE, TEST_ITERATIONS);
    std::cout << "\nRANDOMIZED ORDER:\n\n";
    printResults(sortResults);
    printResultsAnalysis(sortResults, SORT_RESULTS_SIZE);
}

// Set array to be in order
void setAscendingArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

// Set array to be reverse order
void setDescendingArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (size - 1) - i;
    }
}

// Set array to be random order
void randomizeArray(int arr[], int size) {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(0)));

    // Fisher-Yates shuffle algorithm
    for (int i = size - 1; i > 0; i--) {
        // Generate a random index from 0 to i
        int j = std::rand() % (i + 1);

        // Swap arr[i] with arr[j]
        std::swap(arr[i], arr[j]);
    }
}

void resetSortResults(sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    // Reset every variable
    for (int i = 0; i < SORT_RESULTS_SIZE; i++) {
        sortResults[i].comparisons = 0;
        sortResults[i].movements = 0;
        sortResults[i].duration = 0;
    }
}

void printResults(sortResults sortResults[]) {
    // Set column widths
    constexpr int nameWidth = 20;
    constexpr int numWidth = 30;
    constexpr int barWidth = 110;

    // Print a bar
    std::cout << std::string(barWidth, '-') << "\n";

    // Print header with aligned columns
    std::cout << std::left << std::setw(nameWidth) << "Sort Type"
        << std::right << std::setw(numWidth) << "Comparisons"
        << std::setw(numWidth) << "Movements"
        << std::setw(numWidth) << "Total Time (ns)" << "\n";

    // Print a bar
    std::cout << std::string(barWidth, '-') << "\n";

    // Print results for each sorting algorithm
    std::cout << std::left << std::setw(nameWidth) << "Insertion Sort"
        << std::right << std::setw(numWidth) << sortResults[sortType::insertion].comparisons
        << std::setw(numWidth) << sortResults[sortType::insertion].movements
        << std::setw(numWidth) << sortResults[sortType::insertion].duration << "\n";

    std::cout << std::left << std::setw(nameWidth) << "Quick Sort"
        << std::right << std::setw(numWidth) << sortResults[sortType::quick].comparisons
        << std::setw(numWidth) << sortResults[sortType::quick].movements
        << std::setw(numWidth) << sortResults[sortType::quick].duration << "\n";

    std::cout << std::left << std::setw(nameWidth) << "Merge Sort"
        << std::right << std::setw(numWidth) << sortResults[sortType::merge].comparisons
        << std::setw(numWidth) << sortResults[sortType::merge].movements
        << std::setw(numWidth) << sortResults[sortType::merge].duration << "\n";

    std::cout << std::left << std::setw(nameWidth) << "Heap Sort"
        << std::right << std::setw(numWidth) << sortResults[sortType::heap].comparisons
        << std::setw(numWidth) << sortResults[sortType::heap].movements
        << std::setw(numWidth) << sortResults[sortType::heap].duration << "\n\n";

    // Print a bar
    std::cout << std::string(barWidth, '-') << "\n";
}

void printResultsAnalysis(sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    // Calculate and set which sorts are performing best
    int fewestComparisonSort, fewestMovementsSort, fastestSort;
    compareComparisons(fewestComparisonSort, sortResults, SORT_RESULTS_SIZE);
    compareMovements(fewestMovementsSort, sortResults, SORT_RESULTS_SIZE);
    compareDuration(fastestSort, sortResults, SORT_RESULTS_SIZE);

    // Converting from the sort int to std::string for printing
    std::string fewestComparisonSortName = sortTypeToString(fewestComparisonSort);
    std::string fewestMovementsSortName = sortTypeToString(fewestMovementsSort);
    std::string fastestSortName = sortTypeToString(fastestSort);

    // Formatting
    constexpr int nameWidth = 20;
    constexpr int numWidth = 10;
    constexpr int barWidth = 110;

    // Print the best performing sorts
    std::cout << std::left << std::setw(nameWidth) << "Fewest Comparisons:"
        << std::left << std::setw(nameWidth) << fewestComparisonSortName
        << std::right << std::setw(numWidth) << sortResults[fewestComparisonSort].comparisons
        << " Comparisons\n";

    std::cout << std::left << std::setw(nameWidth) << "Fewest Movements:"
        << std::left << std::setw(nameWidth) << fewestMovementsSortName
        << std::right << std::setw(numWidth) << sortResults[fewestMovementsSort].movements
        << " Movements\n";

    std::cout << std::left << std::setw(nameWidth) << "Fastest Runtime:"
        << std::left << std::setw(nameWidth) << fastestSortName
        << std::right << std::setw(numWidth) << sortResults[fastestSort].duration
        << " Total Time (ns)\n";

    // Print a bar
    std::cout << std::string(barWidth, '-') << "\n\n";
}

std::string sortTypeToString(int sort) {
    switch (sort) {
    case sortType::insertion:   return "Insertion Sort";
    case sortType::quick:       return "Quick Sort";
    case sortType::merge:       return "Merge Sort";
    case sortType::heap:        return "Heap Sort";
    default:                    return "Unknown Sort";
    }
}

// Sets fewestComparisonSort to the sort with the fewest comparisons found in sortResults[]
void compareComparisons(int& fewestComparisonSort, sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    fewestComparisonSort = 0;
    for (int i = 1; i < SORT_RESULTS_SIZE; i++) {
        if (sortResults[i].comparisons < sortResults[fewestComparisonSort].comparisons) {
            fewestComparisonSort = i;
        }
    }
}

// Sets fewestMovementsSort to the sort with the fewest movements found in sortResults[]
void compareMovements(int& fewestMovementsSort, sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    fewestMovementsSort = 0;
    for (int i = 1; i < SORT_RESULTS_SIZE; i++) {
        if (sortResults[i].movements < sortResults[fewestMovementsSort].movements) {
            fewestMovementsSort = i;
        }
    }
}

// Sets fastestSort to the fastest sort found in sortResults[]
void compareDuration(int& fastestSort, sortResults sortResults[], const int SORT_RESULTS_SIZE) {
    fastestSort = 0;
    for (int i = 1; i < SORT_RESULTS_SIZE; i++) {
        if (sortResults[i].duration < sortResults[fastestSort].duration) {
            fastestSort = i;
        }
    }
}

// Tests each sorting algorithm with an in order array
void testInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    testInsertionSortInOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::insertion], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testQuickSortInOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::quick], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testMergeSortInOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::merge], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testHeapSortInOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::heap], SORT_RESULTS_SIZE, TEST_ITERATIONS);
}

void testInsertionSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setAscendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        insertionSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testQuickSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setAscendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        quickSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testMergeSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setAscendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        mergeSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testHeapSortInOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setAscendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        heapSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

// Tests each sorting algorithm with a reverse order array
void testReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    testInsertionSortReverseOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::insertion], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testQuickSortReverseOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::quick], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testMergeSortReverseOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::merge], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testHeapSortReverseOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::heap], SORT_RESULTS_SIZE, TEST_ITERATIONS);
}

void testInsertionSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setDescendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        insertionSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testQuickSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setDescendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        quickSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testMergeSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setDescendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        mergeSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testHeapSortReverseOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        setDescendingArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        heapSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

// Tests each sorting algorithm with a random order array
void testRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults sortResults[], const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    testInsertionSortRandomOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::insertion], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testQuickSortRandomOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::quick], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testMergeSortRandomOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::merge], SORT_RESULTS_SIZE, TEST_ITERATIONS);
    testHeapSortRandomOrder(testArray, TEST_ARRAY_SIZE, sortResults[sortType::heap], SORT_RESULTS_SIZE, TEST_ITERATIONS);
}

void testInsertionSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        randomizeArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        insertionSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testQuickSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        randomizeArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        quickSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testMergeSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        randomizeArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        mergeSort(testArray, 0, TEST_ARRAY_SIZE - 1, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}

void testHeapSortRandomOrder(int testArray[], const int TEST_ARRAY_SIZE, sortResults& sortResult, const int SORT_RESULTS_SIZE, const int TEST_ITERATIONS) {
    unsigned long long totalComparisons = 0, totalMovements = 0;
    unsigned long long totalDuration = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < TEST_ITERATIONS; i++) {
        randomizeArray(testArray, TEST_ARRAY_SIZE);

        startTime = std::chrono::high_resolution_clock::now();

        heapSort(testArray, TEST_ARRAY_SIZE, sortResult);

        endTime = std::chrono::high_resolution_clock::now();

        totalDuration += std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        totalComparisons += sortResult.comparisons;
        totalMovements += sortResult.movements;

        // Reset these to avoid multiple test iterations causing incorrect values
        sortResult.comparisons = 0;
        sortResult.movements = 0;
    }

    // Average result over every test
    sortResult.duration = totalDuration / TEST_ITERATIONS;
    sortResult.comparisons = totalComparisons / TEST_ITERATIONS;
    sortResult.movements = totalMovements / TEST_ITERATIONS;
}