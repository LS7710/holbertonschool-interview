#include "slide_line.h"

/**
 * compress_line - Helper to compress non-zero values to the left
 * @line: Array of integers
 * @size: Size of the array
 * Return: void
 */
void compress_line(int *line, size_t size)
{
	size_t i, pos = 0;
	int temp[32] = {0};

	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
		{
			temp[pos++] = line[i];
		}
	}

	for (i = 0; i < size; i++)
		line[i] = temp[i];
}

/**
 * reverse_array - Reverse an array in place
 * @line: Array of integers
 * @size: Size of the array
 */
void reverse_array(int *line, size_t size)
{
	size_t i;
	int temp;

	for (i = 0; i < size / 2; i++)
	{
		temp = line[i];
		line[i] = line[size - 1 - i];
		line[size - 1 - i] = temp;
	}
}

/**
 * merge_line - Merge same numbers to the left
 * @line: Array of integers
 * @size: Size of the array
 */
void merge_line(int *line, size_t size)
{
	size_t i;

	for (i = 0; i < size - 1; i++)
	{
		if (line[i] != 0 && line[i] == line[i + 1])
		{
			line[i] *= 2;
			line[i + 1] = 0;
			i++; /* Skip next */
		}
	}
}

/**
 * slide_line - Slide & merge line like 2048
 * @line: Pointer to array of ints
 * @size: Number of elements in array
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 * Return: 1 on success, 0 on failure
 */
int slide_line(int *line, size_t size, int direction)
{
	if (!line || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
		return (0);

	if (direction == SLIDE_RIGHT)
		reverse_array(line, size);

	compress_line(line, size);
	merge_line(line, size);
	compress_line(line, size);

	if (direction == SLIDE_RIGHT)
		reverse_array(line, size);

	return (1);
}
