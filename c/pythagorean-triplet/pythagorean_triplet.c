#include "pythagorean_triplet.h"

#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a < b ? a : b)

triplets_t *triplets_with_sum(uint16_t sum)
{
    triplet_t temp[sum];
    uint16_t count = 0;

    for (uint16_t a = 1; a < sum / 2; a++)
    {
        for (uint16_t b = a + 1; b < sum / 2; b++)
        {
            uint16_t c = sum - a - b;

            if (a * a + b * b == c * c)
            {
                temp[count].a = a;
                temp[count].b = b;
                temp[count].c = c;
                count++;
            }
        }
    }

    triplets_t *triplets = (triplets_t *)calloc(1, sizeof(triplets_t) + count * sizeof(triplet_t));
    if (NULL == triplets)
    {
        return NULL;
    }

    memcpy(triplets->triplets, temp, count * sizeof(triplet_t));

    triplets->count = count;

    return triplets;
}

void free_triplets(triplets_t *triplets)
{
    free(triplets);
}
