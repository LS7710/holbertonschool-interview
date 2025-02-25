#include <stdio.h>
#include "sandpiles.h"

/**
 * print_grid - Prints a 3x3 grid
 * @grid: 3x3 grid to be printed
 */
void print_grid(int grid[3][3])
{
    int i, j;

    printf("=\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j)
                printf(" ");
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * is_stable - Checks if a sandpile is stable
 * @grid: 3x3 grid to be checked
 * Return: 1 if stable, 0 if unstable
 */
int is_stable(int grid[3][3])
{
    int i, j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i][j] > 3)
                return (0);
        }
    }
    return (1);
}

/**
 * topple - Topples a 3x3 grid until stable
 * @grid: 3x3 grid to be toppled
 */
void topple(int grid[3][3])
{
    int i, j;
    int temp[3][3] = {0};

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i][j] > 3)
            {
                temp[i][j] -= 4;
                if (i > 0) temp[i - 1][j] += 1; // Top
                if (i < 2) temp[i + 1][j] += 1; // Bottom
                if (j > 0) temp[i][j - 1] += 1; // Left
                if (j < 2) temp[i][j + 1] += 1; // Right
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            grid[i][j] += temp[i][j];
        }
    }
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles and stabilizes the result
 * @grid1: First 3x3 grid
 * @grid2: Second 3x3 grid
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
    int i, j;

    /* Step 1: Sum grid1 and grid2 */
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            grid1[i][j] += grid2[i][j];
        }
    }

    /* Step 2 & 3: Check stability and topple */
    while (!is_stable(grid1))
    {
        print_grid(grid1);
        topple(grid1);
    }
}
