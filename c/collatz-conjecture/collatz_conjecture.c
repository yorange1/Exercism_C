#include "collatz_conjecture.h"

#define is_even(n) ((n & 1) == 0)

int steps(int start)
{
    if (start <= 0)
    {
        return ERROR_VALUE;
    }

    int count = 0;

    for (; start != 1; count++)
    {
        if (is_even(start))
        {
            start >>= 1;
        }
        else
        {
            start = start * 3 + 1;
        }
    }

    return count;
}
