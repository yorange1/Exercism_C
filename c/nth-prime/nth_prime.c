#include "nth_prime.h"

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_prime(uint32_t n)
{
    if (n == 1)
    {
        return false;
    }

    for (size_t i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

uint32_t nth(uint32_t n)
{
    size_t count = 0;
    size_t candidate = 1;

    for (; count < n; candidate++)
    {
        if (is_prime(candidate))
        {
            count++;
        }
    }

    return candidate - 1;
}
