#include "largest_series_product.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

static bool input_handle(char *digits, int64_t *nums, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(digits[i]))
        {
            return false;
        }

        nums[i] = digits[i] - '0';
    }

    return true;
}

int64_t largest_series_product(char *digits, size_t span)
{
    assert(digits != NULL);

    size_t len = strlen(digits);
    int64_t nums[len];

    if (span == 0)
    {
        return 1;
    }
    else if ((len == 0 && span > 0) || span > len || !input_handle(digits, nums, len))
    {
        return -1;
    }

    int64_t max = 0;
    size_t i = 0;

    do
    {
        int64_t temp = 1;
        for (size_t j = 0; j < span; j++)
        {
            temp *= nums[i + j];
        }

        max = temp > max ? temp : max;
    } while (i++ < len - span);

    return max;
}
