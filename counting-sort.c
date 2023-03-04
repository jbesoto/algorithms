/*
 * counting-sort.c
 * Author: Juan Diego Becerra
 *
 * Description: This program sorts a string passed as a command-line argument
 * in lexicographical order using counting sort. Below are the general steps
 * followed by said algorithm:
 *
 * 1. Create count array, C, to store count of ea. unique value
 *    (i = value, C[i] = count).
 * 2. Iterate through array and count unique characters.
 * 3. Add count to next count through every position in the count array
 *   * By doing this, C[i] - 1 becomes index position of character i in sorted
 *     array.
 * 4. Create new array and put characters in lexicographical order
 *  4.1. C[str[i]] = position in new array
 *  4.2. Decrement count
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

void print_array(int *, int);
char* sort(char *);

int main(int argc, char *argv[])
{
    char *s;

    if (argc != 2)
    {
        printf("Usage: ./counting-sort string\n");
        return 1;
    }

    s = argv[1];
    char *res = sort(s);

    printf("%s\n", res);

    free(res);
    return 0;
}

/**
 * Sorts a string in lexicographical order using counting sort algorithm.
 *
 * @param s The string to be sorted
 *
 * @return A pointer to the sorted string.
 */
char* sort(char *s)
{
    int i, j, n, count[ALPHABET_SIZE];
    char *new;

    n = strlen(s);
    new = (char *) malloc(n + 1);

    // Count unique characters
    memset(count, 0, sizeof(count)); // Set counts to zero
    for (i = 0; i < n; i++)
    {
        count[s[i] - 'a']++;
    }

    // Add counts to get corresponding index positions in sorted array
    for (i = 1; i < ALPHABET_SIZE; i++)
    {
        count[i] += count[i - 1];
    }

    // Put characters in sorted array of characters
    for (i = 0; i < n; i++)
    {
        j = count[s[i] - 'a'] - 1;
        if (j >= 0)
        {
            new[j] = s[i];
            count[s[i] - 'a']--;
        }
    }
    new[i] = '\0';

    return new;
}