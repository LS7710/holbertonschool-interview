// sort.h
#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

void print_array(const int *array, size_t size);
void radix_sort(int *array, size_t size);

#endif /* SORT_H */

// 0-radix_sort.c
#include "sort.h"

/**
 * get_max - returns the maximum integer in an array
 * @array: the array to search
 * @size: size of the array
 *
 * Return: the maximum value found
 */
static int get_max(const int *array, size_t size)
{
    int max = array[0];
    size_t i;

    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return (max);
}

/**
 * counting_sort - performs a counting sort on array according to digit represented by exp
 * @array: array to sort
 * @size: size of array
 * @exp: exponent representing current digit place (1, 10, 100, etc)
 */
static void counting_sort(int *array, size_t size, int exp)
{
    int *output;
    int count[10] = {0};
    size_t i;
    int digit;

    output = malloc(size * sizeof(int));
    if (!output)
        return;

    /* Count occurrences of each digit */
    for (i = 0; i < size; i++)
    {
        digit = (array[i] / exp) % 10;
        count[digit]++;
    }

    /* Change count[i] so that count[i] contains actual position of this digit in output */
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* Build the output array */
    for (i = size; i > 0; i--)
    {
        digit = (array[i - 1] / exp) % 10;
        output[count[digit] - 1] = array[i - 1];
        count[digit]--;
    }

    /* Copy the output array back to array */
    for (i = 0; i < size; i++)
        array[i] = output[i];

    /* Print the array after this pass */
    print_array(array, size);

    free(output);
}

/**
 * radix_sort - sorts an array of integers in ascending order using Radix sort
 * @array: array to sort
 * @size: size of array
 */
void radix_sort(int *array, size_t size)
{
    int max, exp;

    if (!array || size < 2)
        return;

    max = get_max(array, size);

    /* Do counting sort for every digit. exp is 10^i */
    for (exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort(array, size, exp);
    }
}

