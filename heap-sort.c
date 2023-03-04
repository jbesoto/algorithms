/*
 * heap-sort.c
 * Author: Juan Diego Becerra
 *
 * Description: This program performs heap sort on a given file with
 * comma-separated values. Below are the general steps followed by said algorithm:
 *
 * 1. Build a valid max heap from input array
 * 2. Repeat until array is sorted (i.e. n is equal to 0):
 *  2.1. Swap root (max) with rightmost node in lowest level
 *  2.2. Inactivate bound n = n-1
 *  2.3. Recursively restore the heap (aka. heapify)
 */

#include <stdio.h>

#define MAX_SIZE 1000

#define LEFT(i) (2 * (i + 1)) - 1
#define RIGHT(i) (LEFT(i) + 1)
#define PARENT(i) (i >> 1)
#define MAX(a, b) (a >= b ? a : b)

void print_array(int *, int);
void build_heap(int *, int);
void swap(int *, int, int);
void sort(int *, int);
void heapify(int *, int, int);

int main(int argc, char *argv[])
{
    FILE *fp;
    int arr[MAX_SIZE];
    int n = 0;

    if (argc != 2)
    {
        printf("Usage: ./heap-sort filename\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error: Unable to read file \"%s\"\n", argv[1]);
        return 1;
    }

    while (n < MAX_SIZE && fscanf(fp, "%d,", &arr[n]) == 1)
    {
        n++;
    }

    sort(arr, n);

    print_array(arr, n);
}

/**
 * Build a heap array, then recursively sort it using heap sort.
 *
 * @param arr The array to be sorted
 * @param n Size of the array
 */
void sort(int arr[], int n)
{
    build_heap(arr, n);

    // Recursively sort the heap
    const int root = 0;
    int k = n;
    while (k > 0)
    {
        swap(arr, root, k - 1);
        heapify(arr, root, --k);
    }
}

/**
 * Restores the heap structure from ith node downwards by swapping parent node
 * with largest child node, recursively.
 *
 * @param arr Array to be heapified
 * @param i Index of the node to be heapified
 * @param n Size of the array
 */
void heapify(int arr[], int i, int n)
{
    int largest = i;

    if (LEFT(i) < n && arr[LEFT(i)] > arr[largest])
    {
        largest = LEFT(i);
    }

    if (RIGHT(i) < n && arr[RIGHT(i)] > arr[largest])
    {
        largest = RIGHT(i);
    }

    if (largest != i)
    {
        swap(arr, i, largest);
        heapify(arr, largest, n);
    }
}

/**
 * Organizes a given array of integers into a heap.
 *
 * By definition, a heap fulfills the following conditions:
 *  1. Its internal nodes have 1-2 children
 *  2. Parent node is greater than its children
 *  3. All levels (except for the leaf level) are filled
 *
 * @param arr Array to build the heap from
 * @param n Size of the array
 */
void build_heap(int arr[], int n)
{
    for (int i = (n >> 1) - 1; i >= 0; i--)
    {
        if (arr[i] < MAX(arr[LEFT(i)], arr[RIGHT(i)]))
        {
            heapify(arr, i, n);
        }
    }
}

/**
 * It swaps two elements in an array.
 *
 * @param arr Array of integers
 * @param i Index of the first element to swap
 * @param j Index of the second element to swap
 */
void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/**
 * It prints an array of integers.
 *
 * @param arr Array to be printed
 * @param n Lenght of the array
 */
void print_array(int arr[], int n)
{
    int i;
    printf("[");
    for (i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[i++]);
}