#include "sort.h"

/**
 * get_max - Returns the maximum integer in an array
 * @array: Array to search
 * @size: Number of elements in array
 *
 * Return: Maximum value found
 */
static int get_max(const int *array, size_t size)
{
    int max = array[0];
    for (size_t i = 1; i < size; i++)
        if (array[i] > max)
            max = array[i];
    return (max);
}

/**
 * counting_sort - Performs a counting sort on array according to digit represented by exp
 * @array: Array to sort
 * @size: Number of elements in array
 * @exp: Exponent representing current digit place (1, 10, 100, etc)
 */
static void counting_sort(int *array, size_t size, int exp)
{
    int *output = malloc(size * sizeof(int));
    int count[10] = {0};
    if (!output)
        return;

    /* Count occurrences */
    for (size_t i = 0; i < size; i++)
        count[(array[i] / exp) % 10]++;

    /* Accumulate counts */
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* Build output array */
    for (size_t i = size; i > 0; i--)
    {
        int digit = (array[i - 1] / exp) % 10;
        output[count[digit] - 1] = array[i - 1];
        count[digit]--;
    }

    /* Copy back and print */
    for (size_t i = 0; i < size; i++)
        array[i] = output[i];
    print_array(array, size);

    free(output);
}

void radix_sort(int *array, size_t size)
{
    if (!array || size < 2)
        return;

    int max = get_max(array, size);
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort(array, size, exp);
}

