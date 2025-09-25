#!/usr/bin/python3
"""
Log parsing: read stdin and compute metrics.

- Input lines must match:
  <IP> - [<date>] "GET /projects/260 HTTP/1.1" <status> <file size>
- Print stats every 10 lines and on keyboard interruption (CTRL+C).
- Print total file size and counts for status codes (ascending), only if seen.
"""

import re
import sys


STATUS_CODES = (200, 301, 400, 401, 403, 404, 405, 500)

# Strict pattern for the required format
LINE_RE = re.compile(
    r'^(\S+) - \[([^\]]+)\] "GET /projects/260 HTTP/1\.1" (\d{3}) (\d+)$'
)


def print_stats(total_size, counts):
    """Print the metrics in the required format."""
    print("File size: {}".format(total_size))
    for code in STATUS_CODES:
        count = counts.get(code)
        if count:
            print("{}: {}".format(code, count))


def main():
    total_size = 0
    counts = {}
    line_counter = 0

    try:
        for line in sys.stdin:
            line_counter += 1
            line = line.strip()

            m = LINE_RE.match(line)
            if m:
                # groups: ip, date, status, size
                status_str = m.group(3)
                size_str = m.group(4)

                # Add to total size
                try:
                    total_size += int(size_str)
                except ValueError:
                    # If size isn't an int, treat line as malformed (skip)
                    pass
                else:
                    # Count status only if it's one we care about
                    try:
                        status = int(status_str)
                    except ValueError:
                        pass
                    else:
                        if status in STATUS_CODES:
                            counts[status] = counts.get(status, 0) + 1

            # Every 10 lines, print stats
            if line_counter % 10 == 0:
                print_stats(total_size, counts)

    except KeyboardInterrupt:
        # Print stats on CTRL+C, then exit gracefully
        print_stats(total_size, counts)
        raise
    finally:
        # Also print at normal EOF
        print_stats(total_size, counts)


if __name__ == "__main__":
    main()
