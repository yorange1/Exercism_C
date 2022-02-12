#include "pangram.h"

#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define FLAGS_EXCEPT (0x03FFFFFF)

bool is_pangram(const char *sentence)
{
    if (NULL == sentence)
        return false;

    uint32_t flags = 0;

    for (size_t i = 0; i < strlen(sentence); i++)
    {
        if (isalpha(sentence[i]))
        {
            flags |= 1 << (tolower(sentence[i]) - 'a');
        }
    }

    return (flags == FLAGS_EXCEPT);
}
