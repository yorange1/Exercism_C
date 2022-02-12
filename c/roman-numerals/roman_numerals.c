#include "roman_numerals.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN (20)

char *to_roman_numeral(unsigned int number)
{
    const char roman_table[][10][5] = {
        {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},   // digits
        {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},   // tens
        {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},   // hundreds
        {"", "M", "MM", "MMM"}                                          // thousands
    };

    char *roman = (char *)calloc(1, MAX_LEN);
    assert(roman != NULL);

    unsigned int base = 1000;
    for (int i = 3; i >= 0; i--)
    {
        int digit = number / base;
        if (digit != 0)
        {
            strcat(roman, roman_table[i][digit]);
        }

        number -= digit * base;
        base /= 10;
    }

    return roman;
}
