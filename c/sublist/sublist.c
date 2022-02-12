#include "sublist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static comparison_result_t check_equal(int *list_a, int *list_b, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (list_a[i] != list_b[i])
        {
            return UNEQUAL;
        }
    }

    return EQUAL;
}

static void build_next(int *next, int *list, size_t len)
{
    next[0] = 0;

    for (size_t i = 1, j = 0; i < len;)
    {
        if (list[i] == list[j])
        {
            j++;
            next[i] = j;
            i++;
        }
        else if (j != 0)
        {
            j = next[j - 1];
        }
        else
        {
            i++;
            next[i] = 0;
        }
    }
}

static comparison_result_t check_sublist(int *list_a, int *list_b, size_t len_a, size_t len_b)
{
    int next[len_a] = {0};

    build_next(next, list_a, len_a);

    size_t idx_a = 0;
    size_t idx_b = 0;

    while (idx_b < len_b)
    {
        if (list_a[idx_a] == list_b[idx_b])
        {
            idx_a++;
            idx_b++;
        }
        else if (idx_a != 0)
        {
            idx_a = next[idx_a - 1];
        }
        else
        {
            idx_b++;
        }

        if (idx_a == len_a)
        {
            return SUBLIST;
        }
    }

    return UNEQUAL;
}

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count)
{
    if (list_to_compare == NULL)
    {
        return base_list == NULL ? EQUAL : SUBLIST;
    }
    else if (base_list == NULL)
    {
        return SUPERLIST;
    }

    if (list_to_compare_element_count == base_list_element_count)
    {
        return check_equal(list_to_compare, base_list, list_to_compare_element_count);
    }
    else if (list_to_compare_element_count < base_list_element_count)
    {
        return check_sublist(list_to_compare, base_list, list_to_compare_element_count, base_list_element_count);
    }
    else
    {
        comparison_result_t result = 
        check_sublist(base_list, list_to_compare, base_list_element_count, list_to_compare_element_count);
    }
    
}