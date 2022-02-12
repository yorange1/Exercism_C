#include "luhn.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

bool luhn(const char *num)
{
    size_t len = strlen(num);
    if (len <= 1)
    {
        return false;
    }

    int sum = 0;
    bool need_double = false;
    size_t digit_count = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        if (isdigit(num[i]))
        {
            int digit = num[i] - '0';
            if (need_double)
            {
                digit <<= 1;
                if (digit > 9)
                {
                    digit -= 9;
                }
            }
            sum += digit;
            need_double = !need_double;
            digit_count++;
        }
        else if (num[i] == ' ')
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return (sum % 10 == 0 && digit_count > 1);
}
