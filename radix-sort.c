/*
 * radix-sort.c
 * Author: Juan Diego Becerra
 *
 * Description: This program performs radix sort on a given file with
 * comma-separated values. Below are the general steps followed by said algorithm:
 *
 *  1. Determine the maximum number of digits in any number in the list.
 *  2. Starting from the least significant digit, use counting sort to sort
 *     the elements according to that digit.
 *  3. Repeat 2. until the maximum number of digits is reached.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000

void sort(int *, int, int);
int max(int *, int);
void copy(int *, int *, int);
void print_array(int *, int);

int main(int argc, char *argv[])
{
    FILE *fp;
    int r, arr[MAX_SIZE];
    int n = 0;

    if (argc != 2)
    {
        printf("Usage: ./radix-sort filename\n");
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

    r = 10;
    sort(arr, n, r);
    print_array(arr, n);
    
    return 0;
}

/**
 * Sorts a list of integers using radix sort algorithm.
 *
 * @param arr Array to be sorted
 * @param n Number of elements in the array
 * @param r Base of the number system (e.g. decimal, r = 10)
 */
void sort(int arr[], int n, int r)
{
    int m, l, i, d, count[r], tmp[n];
    m = max(arr, n);

    for (l = 1; m / l > 0; l *= r)
    {
        memset(count, 0, sizeof(count)); // Set counts to zero

        // Count occurrences of symbol
        for (i = 0; i < n; i++)
        {
            d = (arr[i] / l) % r;
            count[d]++;
        }

        // Calculate number of integers less than or equal to ith integer
        for (i = 1; i < r; i++)
        {
            count[i] += count[i - 1];
        }

        // Place numbers in stable sorted order based on current digit
        for (i = n - 1; i >= 0; i--)
        {
            d = (arr[i] / l) % r;
            if (count[d] - 1 >= 0)
            {
                tmp[count[d] - 1] = arr[i];
                count[d]--;
            }
        }
        copy(tmp, arr, n);
    }
}

/**
 * Returns the largest integer in an array.
 *
 * @param arr The array to be searched
 * @param n Size of the array
 *
 * @return The maximum value in the array.
 */
int max(int arr[], int n)
{
    if (n == 0)
    {
        return INT_MIN;
    }

    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

/**
 * It prints an array of integers.
 *
 * @param arr Array to be printed
 * @param n Lenght of the array
 */
void print_array(int arr[], int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * Copy the first n elements of src into dst.
 *
 * @param src Source array
 * @param dst Destination array.
 * @param n Number of elements to copy
 */
void copy(int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dst[i] = src[i];
    }
}