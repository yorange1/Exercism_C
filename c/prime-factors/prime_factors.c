#include "prime_factors.h"

size_t find_factors(uint64_t n, uint64_t factors[static MAXFACTORS])
{
    size_t index = 0;

    for (uint64_t candidate = 2; n > 1; candidate++)
    {
        for (; n % candidate == 0; n /= candidate)
        {
            factors[index++] = candidate;
        }
    }
    
    return index;
}
