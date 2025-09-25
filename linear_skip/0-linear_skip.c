#include "search.h"

/**
 * linear_skip - search for a value in a sorted skip list (with express lane)
 * @list: pointer to the head of the skip list
 * @value: value to search for
 *
 * Return: pointer to the first node where value is located, or NULL
 *
 * Printing rules (must match checker):
 * - Each comparison prints: "Value checked at index [i] = [n]"
 * - When the search range is determined, print:
 *   "Value found between indexes [a] and [b]"
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *prev, *cur, *end;

	if (list == NULL)
		return (NULL);

	/* Use express lane to find the block that may contain value */
	prev = list;
	cur = list->express;

	while (cur)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       cur->index, cur->n);

		if (cur->n >= value)
			break;

		prev = cur;
		cur = cur->express;
	}

	/*
	 * Determine end of the block:
	 * - If we stopped on an express node cur where cur->n >= value,
	 *   search between prev and cur (inclusive).
	 * - If cur == NULL, go to the tail of the list and search between
	 *   prev and tail (inclusive).
	 */
	if (cur == NULL)
	{
		end = prev;
		while (end->next)
			end = end->next;
		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev->index, end->index);
	}
	else
	{
		printf("Value found between indexes [%lu] and [%lu]\n",
		       prev->index, cur->index);
		end = cur;
	}

	/* Linear search within [prev, end] inclusive */
	while (prev && prev->index <= end->index)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       prev->index, prev->n);

		if (prev->n == value)
			return (prev);
		prev = prev->next;
	}

	return (NULL);
}
