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
	size_t i;

	for (i = 1; i < size; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}

	return (max);
}

/**
 * counting_sort - Performs a counting sort on array according to digit
 * @array: Array to sort
 * @size: Number of elements in array
 * @exp: Exponent for current digit (1, 10, 100, etc)
 */
static void counting_sort(int *array, size_t size, int exp)
{
	int *output;
	int count[10] = {0};
	size_t i;
	int digit;

	output = malloc(size * sizeof(int));
	if (!output)
	{
		return;
	}

	for (i = 0; i < size; i++)
	{
		digit = (array[i] / exp) % 10;
		count[digit]++;
	}

	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}

	for (i = size; i > 0; i--)
	{
		digit = (array[i - 1] / exp) % 10;
		output[count[digit] - 1] = array[i - 1];
		count[digit]--;
	}

	for (i = 0; i < size; i++)
	{
		array[i] = output[i];
	}

	print_array(array, size);

	free(output);
}

/**
 * radix_sort - Sorts an array of integers in ascending order
 * @array: Array to sort
 * @size: Number of elements in array
 */
void radix_sort(int *array, size_t size)
{
	int max;
	int exp;

	if (!array || size < 2)
	{
		return;
	}

	max = get_max(array, size);

	for (exp = 1; max / exp > 0; exp *= 10)
	{
		counting_sort(array, size, exp);
	}
}
