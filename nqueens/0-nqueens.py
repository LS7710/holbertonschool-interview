#!/usr/bin/python3
"""
Solve the N-Queens problem and print all solutions.

Usage: nqueens N
- N must be an integer >= 4
- Prints one solution per line, format: [[r0, c0], [r1, c1], ...]
"""
import sys


def solve_nqueens(n):
    """Return a list of all solutions; each solution is a list of [row, col]."""
    solutions = []
    cols = set()      # occupied columns
    diag1 = set()     # r - c (main diagonals)
    diag2 = set()     # r + c (anti-diagonals)
    board = [-1] * n  # board[r] = c

    def backtrack(r):
        if r == n:
            solutions.append([[i, board[i]] for i in range(n)])
            return
        for c in range(n):
            if c in cols or (r - c) in diag1 or (r + c) in diag2:
                continue
            # place queen
            board[r] = c
            cols.add(c)
            diag1.add(r - c)
            diag2.add(r + c)

            backtrack(r + 1)

            # remove queen
            cols.remove(c)
            diag1.remove(r - c)
            diag2.remove(r + c)
            board[r] = -1

    backtrack(0)
    return solutions


def main():
    argv = sys.argv
    if len(argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    s = argv[1]
    if not s.isdigit():
        print("N must be a number")
        sys.exit(1)

    n = int(s)
    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    for sol in solve_nqueens(n):
        print(sol)


if __name__ == "__main__":
    main()
