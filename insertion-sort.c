/*
 * insertion-sort.c
 * Author: Juan Diego Becerra
 *
 * Description: This program performs insertion sort on a given file with
 * comma-separated values.
 */

#include <stdio.h>

#define MAX_NUMBERS 1000

void sort(int arr[], int n);
void swap(int arr[], int i, int j);

int main(int argc, char *argv[])
{
    FILE *fp;
    int arr[MAX_NUMBERS];
    int n = 0;

    if (argc != 2)
    {
        printf("Usage: ./insertion-sort filename\n");
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

    int i;
    printf("[");
    for (i = 0; i < n - 1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[i++]);
}

/**
 * Sorts the array using the insertion sort algorithm.
 *
 * @param arr The array to be sorted
 * @param n the length of the array
 */
void sort(int arr[], int n)
{
    int j;
    for (int i = 1; i < n; i++)
    {
        j = i - 1;
        while (j >= 0 && arr[j + 1] < arr[j])
        {
            swap(arr, j, j + 1);
            j--;
        }
    }
}

/**
 * It swaps two elements in an array.
 *
 * @param arr The array to be sorted
 * @param i the index of the first element to swap
 * @param j the index of the second element to swap
 */
void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}