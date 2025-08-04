#!/usr/bin/python3
"""Pascal's Triangle generator module"""

def pascal_triangle(n):


    """Returns list of lists of integers"""


    if n <= 0:
        return []

    triangle = [[1]]  # First row

    for i in range(1, n):
        row = [1]  # Start each row with 1
        for j in range(1, i):
            # Sum of the two values above
            row.append(triangle[i-1][j-1] + triangle[i-1][j])
        row.append(1)  # End each row with 1
        triangle.append(row)

    return triangle
