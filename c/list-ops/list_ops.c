#include "list_ops.h"

#include <stdlib.h>
#include <string.h>

list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *list = (list_t *)calloc(1, sizeof(list_t) + length * sizeof(list_element_t));
    if (NULL == list)
    {
        return NULL;
    }

    if (length != 0)
    {
        memcpy(list->elements, elements, length * sizeof(list_element_t));
    }

    list->length = length;

    return list;
}

list_t *append_list(list_t *list1, list_t *list2)
{
    list_t *new_list = (list_t *)calloc(1, sizeof(list_t) + (list1->length + list2->length) * sizeof(list_element_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    if (list1->length != 0)
    {
        memcpy(new_list->elements, list1->elements, (list1->length) * sizeof(list_element_t));
    }

    if (list2->length != 0)
    {
        memcpy(&new_list->elements[list1->length], list2->elements, (list2->length) * sizeof(list_element_t));
    }

    new_list->length = list1->length + list2->length;

    return new_list;
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    size_t filter_index[list->length];
    size_t filter_count = 0;

    for (size_t i = 0; i < list->length; i++)
    {
        if (filter(list->elements[i]))
        {
            filter_index[filter_count] = i;
            filter_count++;
        }
    }

    list_t *new_list = (list_t *)calloc(1, sizeof(list_t) + filter_count * sizeof(list_element_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    for (size_t i = 0; i < filter_count; i++)
    {
        new_list->elements[i] = list->elements[filter_index[i]];
    }

    new_list->length = filter_count;

    return new_list;
}

size_t length_list(list_t *list)
{
    return list->length;
}

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    list_t *new_list = (list_t *)calloc(1, sizeof(list_t) + list->length * sizeof(list_element_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    for (size_t i = 0; i < list->length; i++)
    {
        new_list->elements[i] = map(list->elements[i]);
    }

    new_list->length = list->length;

    return new_list;
}

list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t))
{
    list_element_t accumulator = initial;

    for (size_t i = 0; i < list->length; i++)
    {
        accumulator = foldl(accumulator, list->elements[i]);
    }

    return accumulator;
}

list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t))
{
    list_element_t accumulator = initial;

    for (int i = list->length - 1; i >= 0; i--)
    {
        accumulator = foldr(list->elements[i], accumulator);
    }

    return accumulator;
}

list_t *reverse_list(list_t *list)
{
    list_t *new_list = (list_t *)calloc(1, sizeof(list_t) + list->length * sizeof(list_element_t));
    if (NULL == new_list)
    {
        return NULL;
    }

    for (size_t i = 0; i < list->length; i++)
    {
        new_list->elements[i] = list->elements[list->length - 1 - i];
    }

    new_list->length = list->length;

    return new_list;
}

void delete_list(list_t *list)
{
    free(list);
}
