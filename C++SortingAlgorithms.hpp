#pragma once

/**
 * @struct sortResults
 * @brief Holds the performance metrics of sorting algorithms.
 *
 * @var comparisons  Number of element comparisons made during sorting.
 * @var movements    Number of element movements during sorting.
 * @var duration     Time taken to perform the sort (in unspecified units).
 */
struct sortResults {
    unsigned long long comparisons, movements;
    unsigned long long duration;
};

/**
 * @brief Sorts an array using the Insertion Sort algorithm.
 *
 * @param arr        The array to be sorted.
 * @param n          The number of elements in the array.
 * @param sortResult Struct to store the sorting performance metrics.
 */
void insertionSort(int arr[], int n, sortResults& sortResult);

/**
 * @brief Sorts an array using the Quick Sort algorithm.
 *
 * @param arr        The array to be sorted.
 * @param low        The starting index of the array segment to sort.
 * @param high       The ending index of the array segment to sort.
 * @param sortResult Struct to store the sorting performance metrics.
 */
void quickSort(int arr[], int low, int high, sortResults& sortResult);

/**
 * @brief Sorts an array using the Merge Sort algorithm.
 *
 * @param arr        The array to be sorted.
 * @param left       The starting index of the array segment to sort.
 * @param right      The ending index of the array segment to sort.
 * @param sortResult Struct to store the sorting performance metrics.
 */
void mergeSort(int arr[], int left, int right, sortResults& sortResult);

/**
 * @brief Sorts an array using the Heap Sort algorithm.
 *
 * @param arr        The array to be sorted.
 * @param n          The number of elements in the array.
 * @param sortResult Struct to store the sorting performance metrics.
 */
void heapSort(int arr[], int n, sortResults& sortResult);