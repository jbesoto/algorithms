/**
 * deterministic-selection.c
 * Author: Juan Diego Becerra
 *
 * Description: This program selects the kth smallest element from a sequence
 * of integers. Below are the general steps followed by said algorithm:
 *
 *  1. Partition the array into subsets of m elements
 *  2. Recursively find the median of each subset, and store them
 *  3. Recursively find the median of medians (let it be x)
 *  4. Use x to partition the array
 *  5. If the rank of x is equal to k, return x
 *  6. Else, if the rank of x is less than k, recurse on the right partition
 *  7. Else, if the rank of x is greater than k, recurse on the left partition
 *
 * The recursion reaches its base case when the size of the array is less than
 * or equal to 10. The array is sorted and the kth element is returned.
 */

#include <stdio.h>

#define MAX_NUMBERS 1000

void print_array(int *, int);
void copy(int *, int *, int, int);
void swap(int *, int, int);
int partition(int *, int, int);
void sort(int *, int);
int select(int *, int, int);

int main(int argc, char *argv[])
{
    FILE *fp;
    int arr[MAX_NUMBERS];
    int n = 0;

    if (argc != 2)
    {
        printf("Usage: ./<algorithm>-sort filename\n");
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

    int kth = select(arr, 24, n);
    printf("%d\n", kth);
}

/**
 * It copies the elements of the array arr from index start to index end into
 * the destination array.
 *
 * @param arr Array to be sorted
 * @param new Destination array
 * @param start Starting index
 * @param end Ending index
 */
void copy(int arr[], int dest[], int start, int end)
{
    int i = 0;
    while (start <= end)
    {
        dest[i++] = arr[start++];
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
 * Partitions an array of numbers around a given pivot.
 *
 * @param arr Array to be partitioned
 * @param pivot Pivot value
 * @param n Size of the array
 *
 * @return The index of the pivot
 */
int partition(int arr[], int pivot, int n)
{
    int i;

    // Move pivot to first position
    for (i = 0; i < n; i++)
    {
        if (arr[i] == pivot)
        {
            break;
        }
    }
    swap(arr, 0, i);
    pivot = arr[0];

    int prefix = 1;
    int suffix = n - 1;

    // Partition array around the pivot
    while (prefix <= suffix)
    {
        if (arr[prefix] > pivot && arr[suffix] <= pivot)
        {
            swap(arr, prefix++, suffix--);
        }
        if (arr[prefix] <= pivot)
        {
            prefix++;
        }
        if (arr[suffix] > pivot)
        {
            suffix--;
        }
    }

    // Movie pivot to middle of subsets
    swap(arr, 0, prefix - 1);

    return prefix - 1;
}

/**
 * Sorts an array of numbers using insertion sort.
 *
 * @param arr Array to be sorted
 * @param n Size of the array
 */
void sort(int arr[], int n)
{
    int j;
    for (int i = 1; i < n; i++)
    {
        j = i - 1;
        while (j >= 0 && arr[j] > arr[j + 1])
        {
            swap(arr, j, j + 1);
            j--;
        }
    }
}

/**
 * Returns the kth smallest element in an array of numbers using the
 * deterministic selection algorithm.
 *
 * @param arr Array of integers
 * @param k Rank of the element we're looking for
 * @param n Size of the array
 *
 * @return The kth smallest element in the array
 */
int select(int arr[], int k, int n)
{
    const int m = 5; // Subset size for partitioning the array

    int S[n / m][m];
    int R[n / m];
    int i, j, x, r, x_i;

    if (n <= 10)
    {
        sort(arr, n);
        return arr[k - 1];
    }

    // Partition array into subsets of m
    for (i = 0; i < n / m; i++)
    {
        for (j = 0; j < m; j++)
        {
            S[i][j] = arr[i * m + j];
        }
    }

    // Copy representatives (medians) of each subset
    for (i = 0; i < n / m; i++)
    {
        R[i] = select(S[i], m / 2 + 1, m);
    }

    // Find median of medians
    x = select(R, (n / m) / 2, n / m);

    // Partition array with median of medians
    x_i = partition(arr, x, n);

    // Calculate rank
    r = x_i + 1;

    int left[x_i];
    int right[n - x_i - 1];

    // Copy subsets of partition into separate arrays
    copy(arr, left, 0, x_i - 1);
    copy(arr, right, r, n - 1);

    if (r == k)
    {
        return x;
    }
    else if (r > k)
    {
        return select(left, k, x_i);
    }
    else
    {
        return select(right, k - r, n - x_i - 1);
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