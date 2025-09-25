#!/usr/bin/python3
"""
Log parsing: read stdin and compute metrics.

Prints after every 10 lines read and at EOF (and on CTRL+C):
- Total file size: sum of the last field when it's an int
- Counts of status codes among {200, 301, 400, 401, 403, 404, 405, 500}

Parsing is intentionally tolerant: it tries to read the last two
whitespace-separated tokens as <status> <size>. If those parse,
they’re counted; otherwise the line is ignored for that metric.
"""

import sys

STATUS_CODES = (200, 301, 400, 401, 403, 404, 405, 500)


def print_stats(total_size, counts):
    """Print the metrics in the required format."""
    print("File size: {}".format(total_size))
    for code in STATUS_CODES:
        if counts.get(code):
            print("{}: {}".format(code, counts[code]))


def main():
    total_size = 0
    counts = {}
    lines_read = 0

    try:
        for line in sys.stdin:
            lines_read += 1
            parts = line.strip().split()

            # Expect at least two trailing fields for <status> <size>
            if len(parts) >= 2:
                # Parse file size (last token)
                try:
                    size = int(parts[-1])
                except (ValueError, TypeError):
                    size = None

                if size is not None:
                    total_size += size

                # Parse status code (second-to-last token)
                try:
                    status = int(parts[-2])
                except (ValueError, TypeError):
                    status = None

                if status in STATUS_CODES:
                    counts[status] = counts.get(status, 0) + 1

            # Print every 10 lines read (valid or not)
            if lines_read % 10 == 0:
                print_stats(total_size, counts)

    except KeyboardInterrupt:
        # Print stats on CTRL+C, then re-raise to match sample behavior
        print_stats(total_size, counts)
        raise
    finally:
        # Also print at normal EOF
        print_stats(total_size, counts)


if __name__ == "__main__":
    main()
