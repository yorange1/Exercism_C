#include "perfect_numbers.h"

kind classify_number(int number)
{
    if (number <= 0)
    {
        return ERROR;
    }

    int sum = 0;

    for (int candidate = 1, max_candidate = number; candidate < max_candidate; candidate++)
    {
        if (number % candidate == 0)
        {
            max_candidate = number / candidate;
            sum += candidate;

            if (max_candidate != candidate && max_candidate != number)
            {
                sum += max_candidate;
            }
        }
    }

    if (sum == number)
    {
        return PERFECT_NUMBER;
    }
    else if (sum > number)
    {
        return ABUNDANT_NUMBER;
    }
    else
    {
        return DEFICIENT_NUMBER;
    }
}