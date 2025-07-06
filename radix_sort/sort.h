#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

/**
 * print_array - Prints an array of integers
 * @array: The array to be printed
 * @size: Number of elements in @array
 */
void print_array(const int *array, size_t size);

/**
 * radix_sort - sorts an array of integers in ascending order using Radix sort
 * @array: array to sort
 * @size: size of array
 */
void radix_sort(int *array, size_t size);

#endif /* SORT_H */
