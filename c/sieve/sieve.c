#include "sieve.h"

#include <stdbool.h>
#include <string.h>

uint32_t sieve(uint32_t limit, uint32_t *primes, size_t max_primes)
{
    if (limit <= 1)
    {
        return 0;
    }

    uint8_t primes_flags[limit + 1];
    memset(primes_flags, 1, (limit + 1) * sizeof(uint8_t));

    // 0 and 1 is not prime
    primes_flags[0] = 0;
    primes_flags[1] = 0;

    uint32_t count = 0;
    for (size_t i = 2; i < limit + 1; i++)
    {
        if (primes_flags[i] == 1)
        {
            primes[count++] = i;
            if (count >= max_primes)
            {
                break;
            }

            for (size_t j = 2 * i; j < limit + 1; j += i)
            {
                primes_flags[j] = 0;
            }
        }
    }

    return count;
}
