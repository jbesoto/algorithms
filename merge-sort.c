/**
 * merge-sort.c
 * Author: Juan Diego Becerra
 *
 * Description: This program performs merge sort on a given file with
 * comma-separated integers. Below are the general steps followed by said
 * algorithm:
 * 
 * 1. Divide the unsorted array into two halves.
 * 2. Sort the left sub-array, recursively.
 * 3. Sort the right sub-array, recursively.
 * 4. Merge both sorted sub-arrays.
 * 
 * This process is repeated until the sub-arrays can no longer be divided. When
 * this happens, we have reached the base case of the recursion, and the
 * sub-arrays are trivially sorted. 
 */

#include <stdio.h>

#define MAX_NUMBERS 1000

void sort(int *, int);
void merge(int *, int *, int *, int, int);
void print_array(int *, int);

int main(int argc, char *argv[])
{
    FILE *fp;
    int arr[MAX_NUMBERS];
    int n = 0;

    if (argc != 2)
    {
        printf("Usage: ./merge-sort filename\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error: Unable to read file \"%s\"\n", argv[1]);
        return 1;
    }

    while (n < MAX_NUMBERS && fscanf(fp, "%d,", &arr[n]) == 1)
    {
        n++;
    }

    sort(arr, n);

    print_array(arr, n);

    return 0;
}

/**
 * Sorts a given array of size n using the merge sort algorithm.
 *
 * @param arr Array to be sorted
 * @param n Size of the array
 */
void sort(int arr[], int n)
{
    if (n < 2)
    {
        return;
    }

    int mid = n / 2;

    int left[mid];
    int right[n - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int j = 0; j < n - mid; j++)
    {
        right[j] = arr[mid + j];
    }

    sort(left, mid);
    sort(right, n - mid);
    merge(arr, left, right, mid, n - mid);
}

/**
 * It merges two sorted arrays into one sorted array.
 *
 * @param arr Array to be sorted
 * @param left Left half of the array
 * @param right Right half of the array
 * @param size_left Size of the left half
 * @param size_right Size of the right half
 */
void merge(int arr[], int left[], int right[], int size_left, int size_right)
{
    int i = 0, j = 0, k = 0;

    while (i < size_left && j < size_right)
    {
        arr[k++] = left[i] < right[j] ? left[i++] : right[j++];
    }

    while (i < size_left)
    {
        arr[k++] = left[i++];
    }

    while (j < size_right)
    {
        arr[k++] = right[j++];
    }
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