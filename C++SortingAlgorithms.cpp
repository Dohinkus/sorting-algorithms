#include "C++SortingAlgorithms.h"
#include <iostream>
using namespace std;

// Movement: Any time an element in the array is written/modified
// Comparison: Evaluation between two elements to determine their order

void insertionSort(int arr[], int n, sortResults& sortResult) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        bool madeComparison = false;

        while (j >= 0 && arr[j] > key) {
            sortResult.comparisons++; // arr[j] > key is a comparison
            madeComparison = true;
            arr[j + 1] = arr[j]; // Movement
            sortResult.movements++;
            j--;
        }

        if (madeComparison || j >= 0) {
            sortResult.comparisons++; // Final comparison to break the loop
        }

        if (arr[j + 1] != key) {
            arr[j + 1] = key; // Movement
            sortResult.movements++;
        }
    }
}

int partition(int arr[], int low, int high, sortResults& sortResult) {
    int pivot = arr[(high + low) / 2];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        sortResult.comparisons++; // arr[j] < pivot is a comparison
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // Swap counts as 2 movements
            sortResult.movements += 2;
        }
    }

    swap(arr[i + 1], arr[high]); // Swap counts as 2 movements
    sortResult.movements += 2;
    return i + 1;
}

void quickSort(int arr[], int low, int high, sortResults& sortResult) {
    if (low < high) {
        int pi = partition(arr, low, high, sortResult);
        quickSort(arr, low, pi - 1, sortResult);
        quickSort(arr, pi + 1, high, sortResult);
    }
}

void heapify(int arr[], int n, int i, sortResults& sortResult) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        sortResult.comparisons++; // Comparison between left and largest
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        sortResult.comparisons++; // Comparison between right and largest
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(arr[i], arr[largest]); // Swap counts as 2 movements
        sortResult.movements += 2;
        heapify(arr, n, largest, sortResult); // Recursively heapify the affected subtree
    }
}

void heapSort(int arr[], int n, sortResults& sortResult) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, sortResult);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Swap counts as 2 movements
        sortResult.movements += 2;
        heapify(arr, i, 0, sortResult);
    }
}

void merge(int arr[], int left, int mid, int right, sortResults& sortResult) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i]; // Movement
        sortResult.movements++;
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j]; // Movement
        sortResult.movements++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        sortResult.comparisons++; // Compare L[i] and R[j]
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // Movement
            sortResult.movements++;
            i++;
        }
        else {
            arr[k] = R[j]; // Movement
            sortResult.movements++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i]; // Movement
        sortResult.movements++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j]; // Movement
        sortResult.movements++;
        j++;
        k++;
    }

    delete[] L;
    delete[] R; // Clean up dynamic memory
}

void mergeSort(int arr[], int left, int right, sortResults& sortResult) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, sortResult);
        mergeSort(arr, mid + 1, right, sortResult);
        merge(arr, left, mid, right, sortResult);
    }
}
