#include <stdio.h>
#include "menger.h"

/**
 * ipow3 - compute 3^level using integers
 * @level: non-negative exponent
 *
 * Return: 3 raised to @level
 */
static int ipow3(int level)
{
	int n = 1;

	while (level-- > 0)
		n *= 3;
	return (n);
}

/**
 * cell_filled - decide if a cell (x, y) is filled in the Menger sponge
 * @x: x coordinate (column)
 * @y: y coordinate (row)
 *
 * Return: 1 if filled ('#'), 0 if empty (' ')
 */
static int cell_filled(int x, int y)
{
	while (x > 0 || y > 0)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (0);
		x /= 3;
		y /= 3;
	}
	return (1);
}

/**
 * menger - draw a 2D Menger sponge of a given level
 * @level: level of the Menger sponge; if < 0, do nothing
 *
 * Description: A level N sponge is a 3x3 grid of level N-1 sponges,
 *              with the center cell empty. Level 0 is a single '#'.
 */
void menger(int level)
{
	int size, y, x;

	if (level < 0)
		return;

	size = ipow3(level);

	for (y = 0; y < size; y++)
	{
		for (x = 0; x < size; x++)
			putchar(cell_filled(x, y) ? '#' : ' ');
		putchar('\n');
	}
}
