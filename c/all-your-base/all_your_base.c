#include "all_your_base.h"

#include <stdbool.h>
#include <string.h>

static bool valid_input(int8_t digits[], int16_t input_base, size_t input_length)
{
    if (input_length == 0)
    {
        return false;
    }

    for (size_t i = 0; i < input_length; i++)
    {
        if (digits[i] < 0 || digits[i] >= input_base)
        {
            return false;
        }
    }

    return true;
}

static int to_dicimal(int8_t digits[], int16_t input_base, size_t input_length)
{
    int decimal_num = 0;
    int base_power = 1;

    for (int i = input_length - 1; i >= 0; i--)
    {
        decimal_num += digits[i] * base_power;
        base_power *= input_base;
    }

    return decimal_num;
}

size_t rebase(int8_t digits[], int16_t input_base, int16_t output_base, size_t input_length)
{
    if (input_base < 2 || output_base < 2 || !valid_input(digits, input_base, input_length))
    {
        memset(digits, 0, input_length);
        return 0;
    }

    int decimal_num = to_dicimal(digits, input_base, input_length);
    memset(digits, 0, input_length);

    int8_t temp[DIGITS_ARRAY_SIZE] = {0};
    size_t output_length = 0;

    do
    {
        temp[output_length++] = decimal_num % output_base;
        decimal_num /= output_base;
    } while (decimal_num != 0);

    for (size_t i = 0; i < output_length; i++)
    {
        digits[i] = temp[output_length - 1 - i];
    }

    return output_length;
}
