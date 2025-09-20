#include "lists.h"

/* Reverse a singly linked list; return new head */
static listint_t *reverse_list(listint_t *head)
{
    listint_t *prev = NULL, *cur = head, *next;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: address of pointer to head node
 *
 * Return: 1 if palindrome, 0 otherwise
 * An empty list is considered a palindrome.
 *
 * This function runs in O(n) time and O(1) extra space.
 * It reverses the second half in place, compares, then restores the list.
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow, *fast, *prev_slow, *mid, *second, *second_rev_head;
    int is_pal = 1;

    if (head == NULL || *head == NULL || (*head)->next == NULL)
        return (1);

    slow = *head;
    fast = *head;
    prev_slow = NULL;

    /* Find middle (slow), with fast moving 2x */
    while (fast && fast->next)
    {
        fast = fast->next->next;
        prev_slow = slow;
        slow = slow->next;
    }

    /* For odd length, skip the middle node */
    mid = NULL;
    if (fast != NULL) /* odd number of nodes */
    {
        mid = slow;
        second = slow->next;
    }
    else /* even number of nodes */
    {
        second = slow;
    }

    /* Terminate first half */
    if (prev_slow)
        prev_slow->next = NULL;

    /* Reverse second half */
    second_rev_head = reverse_list(second);

    /* Compare first half and reversed second half */
    {
        listint_t *p1 = *head, *p2 = second_rev_head;

        while (p1 && p2)
        {
            if (p1->n != p2->n)
            {
                is_pal = 0;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    /* Restore the original list structure */
    second = reverse_list(second_rev_head);
    if (mid) /* odd length: first -> mid -> second */
    {
        if (prev_slow)
            prev_slow->next = mid;
        mid->next = second;
    }
    else /* even length: first -> second */
    {
        if (prev_slow)
            prev_slow->next = second;
    }

    return (is_pal);
}
