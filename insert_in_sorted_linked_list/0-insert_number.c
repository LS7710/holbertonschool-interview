#include <stdlib.h>
#include "lists.h"

/**
 * insert_node - Inserts a number into a sorted singly linked list.
 * @head: Double pointer to the head of the linked list.
 * @number: The number to insert into the list.
 *
 * Return: The address of the new node, or NULL if it failed.
 */
listint_t *insert_node(listint_t **head, int number)
{
    listint_t *new_node, *current, *prev;

    /* Allocate memory for the new node */
    new_node = malloc(sizeof(listint_t));
    if (new_node == NULL)
        return (NULL);

    new_node->n = number;
    new_node->next = NULL;

    /* Handle the case where the list is empty or new node goes at the head */
    if (*head == NULL || (*head)->n >= number)
    {
        new_node->next = *head;
        *head = new_node;
        return (new_node);
    }

    /* Traverse the list to find the proper insertion point */
    current = *head;
    prev = NULL;
    while (current != NULL && current->n < number)
    {
        prev = current;
        current = current->next;
    }

    /* Insert the new node in the middle or end */
    new_node->next = current;
    if (prev != NULL)
        prev->next = new_node;

    return (new_node);
}
