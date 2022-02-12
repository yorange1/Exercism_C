#include "armstrong_numbers.h"

#include <stdio.h>
#include <stdint.h>
#include <math.h>

bool is_armstrong_number(int candidate)
{
    if (candidate == 0)
    {
        return true;
    }

    int exponent = floor(log10(candidate) + 1);
    int sum = 0;
    int temp = candidate;

    do
    {
        int digit = temp % 10;
        sum += pow(digit, exponent);
        temp /= 10;

        if (sum > candidate)
        {
            return false;
        }

    } while (temp > 0);

    return (sum == candidate);
}