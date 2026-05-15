/**************************************************************************************************
 * 
 * Atharv Ravindra Sonawane
 * BE-B - 46 
 * 
 * Problem statement : Write a program to implement Parallel Merge Sort. Use existing algorithms and 
 * measure the performance of sequential and parallel algorithms.
 * 
 * **************************************************************************************************/

#include <iostream>
#include <omp.h>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void mergeSortSeq(int arr[], int l, int r) {
    if(l >= r) return;

    int m = (l + r) / 2;

    mergeSortSeq(arr, l, m);
    mergeSortSeq(arr, m + 1, r);

    merge(arr, l, m, r);
}

void mergeSortPar(int arr[], int l, int r) {
    if(l >= r) return;

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortPar(arr, l, m);

        #pragma omp section
        mergeSortPar(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr1[] = {10, 3, 5, 8, 6, 2, 7, 4, 1, 9};
    int n = sizeof(arr1)/sizeof(arr1[0]);
    int arr2[n];

    for(int i = 0; i < n; i++)
        arr2[i] = arr1[i];

    double start = omp_get_wtime();
    mergeSortSeq(arr1, 0, n-1);
    double end = omp_get_wtime();

    cout << "Sequential Sorted: ";
    printArray(arr1, n);
    cout << "Sequential Time: " << (end - start) << " sec\n";

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSortPar(arr2, 0, n-1);
    }
    end = omp_get_wtime();

    cout << "\nParallel Sorted: ";
    printArray(arr2, n);
    cout << "Parallel Time: " << (end - start) << " sec\n";

    return 0;
}
