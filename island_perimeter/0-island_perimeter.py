#!/usr/bin/python3
"""
Module 0-island_perimeter
Contains a function that calculates the perimeter of an island in a grid
"""


def island_perimeter(grid):
    """
    Calculates the perimeter of the island described in grid

    Args:
        grid (list of list of int): A 2D grid where 1 represents land and 0 water

    Returns:
        int: The perimeter of the island
    """
    perimeter = 0
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == 1:
                perimeter += 4
                if i > 0 and grid[i - 1][j] == 1:  # Check up
                    perimeter -= 2
                if j > 0 and grid[i][j - 1] == 1:  # Check left
                    perimeter -= 2
    return perimeter
