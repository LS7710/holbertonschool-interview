#!/usr/bin/python3
"""
Validate UTF-8 encoding.

A character can be 1–4 bytes:
- 0xxxxxxx
- 110xxxxx 10xxxxxx
- 1110xxxx 10xxxxxx 10xxxxxx
- 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
"""


def validUTF8(data):
    """
    Determine if a list of integers encodes valid UTF-8.

    Args:
        data (List[int]): Sequence of integers (each represents 1 byte).
                          Only the 8 least significant bits are used.

    Returns:
        bool: True if data is a valid UTF-8 encoding, else False.
    """
    expected = 0  # number of continuation bytes expected

    for num in data:
        byte = num & 0xFF  # only consider 8 LSBs

        if expected == 0:
            # Count leading 1s to determine the total length
            if (byte >> 7) == 0:
                # 1-byte char: 0xxxxxxx
                continue

            cnt = 0
            mask = 0x80  # 1000 0000
            while byte & mask:
                cnt += 1
                mask >>= 1

            # cnt == 1 is invalid
            if cnt == 1 or cnt > 4:
                return False

            expected = cnt - 1
        else:
            # Continuation byte must be 10xxxxxx
            if not (byte & 0x80) or (byte & 0x40):
                return False
            expected -= 1

    return expected == 0
