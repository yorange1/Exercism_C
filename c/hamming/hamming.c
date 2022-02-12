#include "hamming.h"

#include <stddef.h>
#include <string.h>

int compute(const char *lhs, const char *rhs)
{
    if (NULL == lhs || NULL == rhs)
    {
        return -1;
    }

    size_t lhs_len = strlen(lhs);
    size_t rhs_len = strlen(rhs);

    if (lhs_len != rhs_len)
    {
        return -1;
    }

    int ham_dist = 0;

    for (size_t i = 0; i < lhs_len; i++)
    {
        if (lhs[i] != rhs[i])
        {
            ham_dist++;
        }
    }

    return ham_dist;
}