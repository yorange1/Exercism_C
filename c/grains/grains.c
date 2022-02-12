#include "grains.h"

uint64_t square(uint8_t index)
{
    if (index == 0 || index > 64)
    {
        return 0;
    }

    uint64_t base = 2;
    uint64_t grains_num = 1;
    uint8_t exp = index - 1;

    while (1)
    {
        if ((exp & 1) != 0)
        {
            grains_num *= base;
        }

        exp >>= 1;
        if (!exp)
        {
            break;
        }

        base *= base;
    }

    return grains_num;
}

uint64_t total(void)
{
    uint64_t total_num = 0;
    uint64_t grain_num = 1;

    for (int i = 0; i < 64; i++)
    {
        total_num += grain_num;
        grain_num *= 2;
    }

    return total_num;
}