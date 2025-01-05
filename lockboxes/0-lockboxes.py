#!/usr/bin/python3
"""
Lockboxes Problem: Determine if all boxes can be unlocked.
"""

def canUnlockAll(boxes):
    """
    Determines if all boxes can be unlocked.

    Parameters:
        boxes (list of lists): A list where each sublist contains keys for other boxes.

    Returns:
        bool: True if all boxes can be unlocked, False otherwise.
    """
    n = len(boxes)  # Total number of boxes
    unlocked = set([0])  # The first box is unlocked by default
    keys = set(boxes[0])  # Keys in the first box

    while keys:
        key = keys.pop()  # Get a key from the set
        if key not in unlocked and 0 <= key < n:  # Valid key not already unlocked
            unlocked.add(key)  # Mark box as unlocked
            keys.update(boxes[key])  # Add new keys from this box

    # Return True if all boxes are unlocked
    return len(unlocked) == n


if __name__ == "__main__":
    # Test cases
    boxes = [[1], [2], [3], [4], []]
    print(canUnlockAll(boxes))  # True

    boxes = [[1, 4, 6], [2], [0, 4, 1], [5, 6, 2], [3], [4, 1], [6]]
    print(canUnlockAll(boxes))  # True

    boxes = [[1, 4], [2], [0, 4, 1], [3], [4, 1], [5, 6]]
    print(canUnlockAll(boxes))  # False
