#include "sum_of_multiples.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static void set_bit(int *bitmap, size_t index)
{
    bitmap[index / 32] |= 1 << (index % 32);
}

static bool is_set(int *bitmap, size_t index)
{
    return ((bitmap[index / 32] & (1 << (index % 32))) != 0);
}

unsigned int sum(const unsigned int *factors, const size_t number_of_factors,
                 const unsigned int limit)
{
    int *bitmap = (int *)calloc(1, ((limit / 32) + 1) * sizeof(int));

    unsigned int result = 0;

    for (size_t i = 0; i < number_of_factors; i++)
    {
        if (factors[i] != 0)
        {
            unsigned int factor = factors[i];
            while (factor < limit)
            {
                if (!is_set(bitmap, factor))
                {
                    result += factor;
                    set_bit(bitmap, factor);
                }

                factor += factors[i];
            }
        }
    }

    free(bitmap);

    return result;
}
