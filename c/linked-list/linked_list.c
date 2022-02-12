#include "linked_list.h"

#include <stdlib.h>

struct list_node
{
    struct list_node *prev, *next;
    ll_data_t data;
};

struct list
{
    struct list_node *first, *last;
};

// constructs a new (empty) list
struct list *list_create(void)
{
    struct list *new_list = (struct list *)malloc(sizeof(struct list));
    if (NULL == new_list)
    {
        return NULL;
    }

    new_list->first = NULL;
    new_list->last = NULL;

    return new_list;
}

// counts the items on a list
size_t list_count(const struct list *list)
{
    struct list_node *temp = list->first;
    if (NULL == temp)
    {
        return 0;
    }

    size_t count = 1;

    while (temp->next != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)calloc(1, sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    new_node->data = item_data;

    if (list_count(list) == 0)
    {
        list->first = new_node;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        new_node->prev = list->last;
        list->last->next = new_node;
        new_node->next = NULL;
    }

    list->last = new_node;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    struct list_node *prev_node = list->last->prev;
    ll_data_t data = list->last->data;

    free(list->last);

    if (NULL == prev_node)
    {
        list->first = NULL;
        list->last = NULL;
    }
    else
    {
        prev_node->next = NULL;
        list->last = prev_node;
    }

    return data;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = (struct list_node *)calloc(1, sizeof(struct list_node));
    if (NULL == new_node)
    {
        return;
    }

    if (list_count(list) == 0)
    {
        list_push(list, item_data);
    }
    else
    {
        struct list_node *front_node = list->first;
        front_node->prev = new_node;

        new_node->data = item_data;
        new_node->next = front_node;
        new_node->prev = NULL;

        list->first = new_node;
    }
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    struct list_node *next_node = list->first->next;
    ll_data_t data = list->first->data;

    free(list->first);

    if (NULL == next_node)
    {
        list->last = NULL;
        list->first = NULL;
    }
    else
    {
        next_node->prev = NULL;
        list->first = next_node;
    }

    return data;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *temp = list->first;

    while (temp != NULL)
    {
        if (temp->data == data)
        {
            if (temp == list->first)
            {
                list_shift(list);
            }
            else if (temp == list->last)
            {
                list_pop(list);
            }
            else if (temp != list->first && temp != list->last)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(temp);
            }

            break;
        }

        temp = temp->next;
    }
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list)
{
    while (list->first != NULL)
    {
        struct list_node *temp = list->first;
        list->first = list->first->next;
        free(temp);
    }
}
